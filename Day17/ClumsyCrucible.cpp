#include "ClumsyCrucible.h"

#include <fstream>
#include <string>
#include <queue>

#include "Block.h"

using namespace std;

int64_t ClumsyCrucible::get()
{
    bool usingExample = false;

    fstream file = usingExample ? fstream("Day17/test.txt", ios::in) : fstream("Day17/input.txt", ios::in);
    if (!file.is_open())
    {
        return -1;
    }

    Vector2 mapPosition = Vector2(0, 0);
    vector<vector<Block>> heatLossMap;
    string line;
    while (getline(file, line))
    {
        mapPosition.x = 0;
        vector<Block> heatLoss;
        for (char c : line)
        {
            heatLoss.emplace_back(c, mapPosition);
            mapPosition.x++;
        }
        heatLossMap.emplace_back(heatLoss);
        mapPosition.y++;
    }
    int height = heatLossMap.size();
    int width = heatLossMap[0].size();

    vector<QueueEntry> searchQueue;

    Block* startingBlock = &heatLossMap[0][0];
    startingBlock->setDistance(startingBlock->cost, None, 0);
    searchQueue.emplace_back(startingBlock, None, 0);

    while (!searchQueue.empty())
    {
        QueueEntry entry = searchQueue.front();
        searchQueue.erase(searchQueue.begin());

        Block* block = entry.block;
        Direction direction = entry.direction;
        int straight = entry.straight;
        // block->visit(straight, direction);
        vector<QueueEntry> neighbors = block->getAdjacentBlocks(heatLossMap, direction, straight);
        for (QueueEntry& neighbor : neighbors)
        {
            neighbor.block->setDistance(block->getDistance(direction, straight) + neighbor.block->cost, neighbor.direction, neighbor.straight);
            if (!neighbor.block->visited(neighbor.straight, neighbor.direction))
            {
                neighbor.block->visit(neighbor.straight, neighbor.direction);
                searchQueue.emplace_back(neighbor);
            }
        }
    }

    for (vector<Block>& line : heatLossMap)
    {
        for (Block& block : line)
        {
            int distance = block.getShortestDistance();
            if (distance > 99)
            {
                printf("%i ", distance);
            }
            else if (distance > 9)
            {
                printf(" %i ", distance);
            }
            else
            {
                printf("  %i ", distance);
            }
        }
        printf("\n");
    }

    int64_t distance = heatLossMap[heatLossMap.size() - 1][heatLossMap[0].size() - 1].getShortestDistance();
    if (usingExample)
    {
        if (distance != 102)
        {
            printf("Unit test failed.\n");
        }
    }
    return distance;
}

bool ClumsyCrucible::contains(std::vector<QueueEntry>& entries, QueueEntry& entry)
{
    for (QueueEntry& oldEntry : entries)
    {
        if (entry == oldEntry)
        {
            return true;
        }
    }
    return false;
}

ClumsyCrucible::QueueEntry::QueueEntry(Block* block, Direction direction, int straight)
    :block(block), direction(direction), straight(straight)
{
}

bool ClumsyCrucible::QueueEntry::operator==(const QueueEntry& other) const
{
    return (block == other.block) && (direction == other.direction) && (straight == other.straight);
}
