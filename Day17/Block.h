#pragma once

#include <map>
#include <vector>

#include "../Common/Common.h"
#include "ClumsyCrucible.h"

struct Block
{
	Block(char c, Vector2 position);

	void setDistance(int newDistance, Direction direction, int straight);

	std::vector<ClumsyCrucible::QueueEntry> getAdjacentBlocks(std::vector<std::vector<Block> >& map, Direction direction, int distance);

	int getDistance(Direction direction, int distance) const;

	int getShortestDistance() const;

	bool visited(int distance, Direction direction) const;
	void visit(int distance, Direction direction);

	int cost;
	Vector2 position;
private:
	std::map< std::pair<int, Direction>, int> distanceMap;
	std::map< std::pair<int, Direction>, bool> visitedMap;
};