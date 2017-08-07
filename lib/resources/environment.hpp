#pragma once

#include <vector>
#include <lib/resources/resource.hpp>
#include <lib/resources/action.hpp>

struct environment
{
private:
	std::vector < resource > resources;
	std::vector < action > actions;
public:
	environment (std::vector < resource > r, std::vector < action > a)
	{
		this->actions = a;
		this->resources = r;
	}
	std::vector < resource > get_resources () const
	{
		return this->resources;
	}

	std::vector < action > get_actions () const
	{
		return this->actions;
	}
};
