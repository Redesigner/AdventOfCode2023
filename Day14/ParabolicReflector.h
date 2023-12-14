#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <map>

namespace ParabolicReflector
{
	int64_t get();
	int64_t get2();

	void moveNorth(std::vector<std::string>& values);

	void moveSouth(std::vector<std::string>& values);

	void moveEast(std::vector<std::string>& values);

	void moveWest(std::vector<std::string>& values);

	bool moveCycle(std::vector<std::string>& values);

	static std::vector< std::pair<std::vector<std::string>, std::vector<std::string>> > valuesMap;
}