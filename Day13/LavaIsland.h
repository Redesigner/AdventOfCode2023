#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace LavaIsland
{
	struct Map
	{
		Map(std::vector<std::string> lines);

		std::string toString() const;

		std::vector<std::vector<bool>> map;

		bool findXReflection();
		bool findYReflection();

		bool validXReflection(int x) const;
		bool validYReflection(int y) const;

		std::vector<bool> getColumn(int x) const;

		int getValue();

		int getSmudgedValue();

		int reflectionX;
		int reflectionY;
	};
	int64_t get();
	int64_t get2();
}