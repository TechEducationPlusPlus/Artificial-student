#pragma once

#include <lib/resources/resource.hpp>

struct action 
{ 
	std::string id;
	resource r;
	action (std::string i, resource require)
	{
		this->id = i;
		this->r = require;
	}
};

bool operator < (action a, action b)
{
	return a.r < b.r;
}
