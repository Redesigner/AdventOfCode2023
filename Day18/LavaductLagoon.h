#pragma once

#include <cstdint>
#include <vector>

#include "../Common/Common.h"


namespace LavaductLagoon
{
	struct Tile
	{
		bool dug = false;
		int32_t color = 0;
		bool exterior = false;
	};

	// make this a templated class for reuse later?
	class ExpandingMap
	{
	public:
		ExpandingMap(int width, int height);

		Tile* get(Vector2 position);
		void placeTile(int32_t color, Vector2 position);

		void expandToPosition(int width, int height);

		void fill();

		std::string toString() const;

		int64_t sum() const;

	private:
		std::vector<std::vector<Tile> > tiles;

		int width;

		int height;

		int xOffset;

		int yOffset;

		void insertColumnLeft();
		void insertColumnRight();

		void insertRowTop();
		void insertRowBottom();
	};

	int64_t get();
	int64_t get2();

	Direction getDirectionFromHex(char c);

	Direction getDirection(char c);
}