#pragma once

#include <vector>

#include "../Common/Common.h"

namespace CosmicExpansion
{
	int get();
	int64_t get2();

	bool galaxiesInColumn(const std::vector<Vector2>& galaxies, int x);
	bool galaxiesInRow(const std::vector<Vector2>& galaxies, int y);
}