#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace HotSprings
{
	struct ConditionEntry
	{
		ConditionEntry(std::string& string);

		std::vector<std::string> getAllPossibleValues(std::string string) const;

		bool isValidString(std::string& string) const;

		std::string conditionString;
		std::vector<int> springGroups;
	};

	static std::unordered_map <std::string, std::vector < std::string>> valuesMap;

	int get();
	int get2();
}