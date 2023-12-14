#pragma once

#include <vector>
#include <string>
#include <map>

namespace HotSprings
{
	struct ConditionEntry
	{
		ConditionEntry(std::string& string);

		std::vector<std::string> getAllPossibleValues(std::string string) const;

		bool isValidString(std::string& string) const;

		int getSum() const;
		bool canInsert(std::string& string, size_t startIndex) const;

		std::string conditionString;
		std::vector<int> springGroups;
	};

	static std::map <std::tuple<std::string, std::vector<int>, bool>, int64_t> valuesMap;

	int get();
	uint64_t get2();

	uint64_t count(std::string_view string, const std::vector<int>& values, bool valid);
}