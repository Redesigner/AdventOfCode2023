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

		void findXReflection();
		void findYReflection();

		bool validXReflection(int x) const;
		bool validYReflection(int y) const;

		std::vector<bool> getColumn(int x) const;

		int reflectionX;
		int reflectionY;
	};
	int64_t get();
	int64_t get2();

	std::string getColumn(const std::vector<std::string>& map, int x);
	bool mirrorsColumns(const std::vector<std::string>& map, int x);
	int getMirroredX(const std::vector<std::string>& map);

	bool mirrorsRows(const std::vector<std::string>& map, int y);
	int getMirroredY(const std::vector<std::string>& map);

	void remap(std::pair<std::vector<std::string>, int>& mapValue);
}