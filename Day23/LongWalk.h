#pragma once

#include <cstdint>

#include "../Common/Common.h"

namespace LongWalk
{
	enum TileType
	{
		Path,
		Forest,
		Slope
	};
	struct Tile
	{
		Tile(Vector2 position, char c);
		Tile();

		std::vector<std::pair<Direction, Tile*>> getAdjacentTiles(std::vector<std::vector<Tile>>& map, Direction direction) const;
		std::vector<Direction> getAdjacentDirections(Direction direction) const;

		Vector2 position;
		TileType tileType;
		Direction slopeDirection;
	};
	int64_t get();
}