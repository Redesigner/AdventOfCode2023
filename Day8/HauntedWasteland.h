#pragma once

#include <string>

namespace HauntedWasteland
{
	struct Location
	{
		Location(std::string string);

		bool operator ==(const Location& other) const;
		bool operator >(const Location& other) const;
		bool operator <(const Location& other) const;
		
		char a;
		char b;
		char c;
	};

	struct Node
	{
		Node(const std::string& left, const std::string& right);

		bool operator ==(const Node& other) const;

		Location left;
		Location right;
	};

	int get();
}