#pragma once

#include <cstdint>

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

	struct Node2
	{
		Node2(bool rock, Vector2 position);
	};

	int64_t get();
	int64_t get2();
};