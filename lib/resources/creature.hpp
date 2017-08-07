#pragma once

#include <vector>
#include <lib/resources/action.hpp>
#include <lib/resources/environment.hpp>

struct creature
{
private:
	std::vector < action > ordered_actions;
public:
	creature (std::vector < action > a = {})
	{
		this->ordered_actions = a;
	}

	std::vector < creature > evolution (environment ENV) const
	{
		std::vector < creature > ans;
		std::vector < action > curr_creature = this->ordered_actions;
		for (int i = 0 ; i < 2 ; i ++)
		{
			auto x = ENV.get_actions ()[rand () % ENV.get_actions ().size ()];
			{
				curr_creature.push_back (x);
				ans.push_back (curr_creature);
				curr_creature.pop_back ();
			}
		}
		return ans;
	}
	std::vector < action > get () const
	{
		return ordered_actions;
	}
	bool operator < (const creature& a) const
	{
		return a.ordered_actions > this->ordered_actions;
	}
};
