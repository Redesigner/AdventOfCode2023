#pragma once

#include <cstdint>
#include <vector>

#include "../Common/Common.h"

namespace ClumsyCrucible
{
	struct Block
	{
		Block(char c, Vector2 position);

		void setDistance(int newDistance);

		std::vector<Block*> getAdjacentBlocks(std::vector<std::vector<Block>>& map);

		int distance;
		int cost;
		Vector2 position;
		bool visited = false;
		int numStraightMoves = 0;
	};

	int64_t get();

	void printDistances(std::vector<std::vector<Block>>& map);
}