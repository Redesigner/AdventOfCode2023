#pragma once

#include <cstdint>
#include <map>
#include <vector>

#include "../Common/Common.h"

namespace StepCounter
{
	struct Node
	{
		Node(bool rock, Vector2 position);

		Vector2 position;
		int distance = -1;
		bool visited = false;
		bool rock;
		bool valid = false;
	};

	int64_t get();
	int64_t get2();

	int64_t getPossiblePositions(std::vector<std::vector<Node>>* baseMap, Vector2 startLocation, int maxSteps);
	static std::map< std::tuple<std::vector<std::vector<Node>>*, Vector2, int>, int64_t> getPossiblePositionsCache;
};