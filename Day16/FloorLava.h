#pragma once

#include <cstdint>

#include "../Common/Common.h"

namespace FloorLava
{
	enum TileType
	{
		Invalid,
		Empty,
		TopRightMirror,
		TopLeftMirror,
		VerticalSplitter,
		HorizontalSplitter
	};

	enum Direction
	{
		Up,
		Right,
		Left,
		Down
	};

	struct Tile
	{
		Tile(char c);

		TileType tileType;
		bool pathedHorizontally = false;
		bool pathedVertically = false;
		bool pathedSpecial = false;
	};

	int64_t get();
	int64_t get2();

	void shiftPosition(Vector2& position, Direction direction);
	void reflectTopLeft(Vector2& position, Direction& direction);
	void reflectTopRight(Vector2& position, Direction& direction);
}