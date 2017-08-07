using namespace std;
#include <iostream>
#include <lib/init.hpp>
#include <lib/resources/environment.hpp>
#include <lib/resources/generation.hpp>
#include <map>
#include <set>
#include <lib/fcgi/base.hpp>
#include <lib/fcgi/params.hpp>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

MySQL::client_t Infocourse ("Infocourse");
	
void Throw (string a)
{
	cout << a << "\n";
}

std::vector < resource > resources;
std::vector < action > actions;

int videos, exams;

std::set < action > unique (std::vector < action > a)
{
	return std::set < action > (a.begin (), a.end ());
}

static const double INF = std::numeric_limits<double>::infinity ();

double f (int x)
{
	if (x == 0)
		return 0.5;
	else if (x == -2)
		return 0; 
	else
		return pow (2.0f, -(x - 1));
}

double diff (action a, action b)
{
	if (a.r.course == b.r.course)
		return pow(2.0f, -(atoi(Infocourse.result ("SELECT COUNT(*) FROM `Videos` WHERE `UniqueID`>=" + a.r.uniqueId() + " AND `UniqueID`<=" + b.r.uniqueId() + " AND `Course`=\"" + a.r.course + "\"", "", "")[0][0]) - 2));
	else
		return 1e-6;
}

double eval (creature a)
{
	double value = 0;
	action* ptr = nullptr;
	for (auto& x : unique (a.get ()))
	{
		if (ptr == nullptr)
		{
			ptr = new action (x);
		}
		else
		{
			value += diff (*ptr, x);
			(*ptr) = x;
		}
	}
	return ((double)value) * 100;
}

std::vector < creature > sort (std::vector < creature > a)
{
	sort (a.begin (), a.end (), [](creature a, creature b) -> bool { return eval (a.get ()) < eval (a.get ()); });
	return std::move (a);
}

int main ()
{
	for (auto& x : Infocourse.result ("SELECT `UniqueID`,`ExamLink`,`Course` FROM `Videos`", "", ""))
	{
		resource curr;
		if (x [1][0] == '#')
		{
			curr = resource ("1", x [0], x [2]);
			videos ++;
		}
		else
		{
			curr = resource ("2", x [0], x [2]);
			exams ++;
		}
		resources.push_back (curr);
		actions.push_back (action (curr.ID (), curr));
	}

	environment ENV (resources, actions);

	generation gen ({creature ()});

	for (int i = 0 ; i < 10 ; i ++)
	{

		for (auto& x : sort(gen.get ()))
		{
			cout << "(";
			for (auto& y : unique(x.get ()))
				cout << "[" << y.r.id << ", " << y.r.type << ", " << y.r.course << "] ";
			cout << ")[" << eval (x) << "]\n";
		}
		cout << "\n---------------------------------------------------- Size: " << gen.get ().size () << "\n";
		gen = generation (gen.filter (eval, 15)).evolution (ENV);
	}
}
