#pragma once

#include <vector>
#include <algorithm>
#include <lib/resources/environment.hpp>
#include <lib/resources/creature.hpp>

struct generation
{
private:
	std::vector < creature > creatures;
public:
	generation (std::vector < creature > creatures = {})
	{
		this->creatures = creatures;
	}
	
	generation evolution (environment ENV) const
	{
		std::vector < creature > ans;
		for (auto& x : this->creatures)
			for (auto& y : x.evolution (ENV))
				ans.push_back (y);
		return generation (ans);
	}

	generation pairing (environment ENV) const
	{
		throw ("Not implemented yet");
	}

	std::vector < creature > filter (double (&eval)(creature), size_t MAXN) const
	{
		std::vector < creature > ans = this->creatures;
		std::sort (ans.begin (), ans.end (), [&eval](creature a, creature b) -> bool
										{
											return eval (a) > eval (b);
										}
			 );
		std::vector < creature > filtered_ans;
		if (ans.size () <= 2 * MAXN)
			return ans;
		for (int i = 0 ; i < MAXN ; i ++)
		{
			filtered_ans.push_back (ans [i]);
			filtered_ans.push_back (ans [ans.size () - i - 1]);
		}
		return filtered_ans;
	}

	std::vector < creature > get () const
	{
		return this->creatures;
	}
};
