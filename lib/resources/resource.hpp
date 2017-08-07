#pragma once

#include <string>
#include <stdlib.h>
#include <sstream>

struct resource
{
	int type;
	int id;
	std::string course;

	resource (std::string type = "", std::string id = "", std::string course = "")
	{
		this->type = atoi (type.c_str ());
		this->id = atoi (id.c_str ());
		this->course = course;
	}

	std::string ID () const
	{
		std::stringstream ss;
		ss << type << id;
		return ss.str ();
	}

	std::string uniqueId () const
	{
		std::stringstream ss;
		ss << id;
		return ss.str ();
	}
};

bool operator < (resource a, resource b)
{
	if (a.course == b.course)
	{
		if (a.type == b.type)
			return a.id < b.id;
		return a.type < b.type;
	}
	return a.course < b.course;
}
