#pragma once

#include <lib/resources/resource.hpp>
#include <lib/database.hpp>
#include <vector>
#include <string>

struct person
{
	std::string id;

	person (std::string id = "")
	{
		this->id = id;
	}
	
	std::vector < resource > get_visitations ()
	{
		auto res = MySQL::client.result ("SELECT `Type`, `IdResource` FROM `Visits` WHERE `IdUser`='", this->id, "'");

		std::vector < resource > current; 

		for (auto& x : res)
			current.push_back (resource (x [0], x [1]));

		return std::move (current);
	}
};
