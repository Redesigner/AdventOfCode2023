#pragma once

#include <string>
#include <vector>
#include <map>

namespace HauntedWasteland
{
	struct Location
	{
		Location(const std::string& string);

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
	int64_t get2();

	int getShortestValue(const Location& startingLocation, const std::string directionString, const std::map<Location, Node>& map);

	int64_t GCD(const int& a, const int& b);
	int64_t GCD(const std::vector<int>& values);

	int64_t LCM(const std::vector<int>& values);
}