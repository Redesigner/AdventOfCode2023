#pragma once

#include <cstdint>
#include <vector>
#include <map>

#include "../Common/Common.h"

class Block;
namespace ClumsyCrucible
{
	struct QueueEntry
	{
		QueueEntry(Block* block, Direction direction, int straight);

		Direction direction;
		int straight;
		Block* block;

		bool operator==(const QueueEntry& other) const;
	};

	int64_t get();

	bool contains(std::vector<QueueEntry>& entries, QueueEntry& entry);
}