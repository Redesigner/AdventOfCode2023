#include "ClumsyCrucible.h"

#include <fstream>
#include <string>
#include <queue>

using namespace std;

int64_t ClumsyCrucible::get()
{
    bool usingExample = true;

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


    queue<Block*> searchQueue;
    searchQueue.emplace(&heatLossMap[0][0]);
    heatLossMap[0][0].visited = true;
    heatLossMap[0][0].distance = 0;
    while (!searchQueue.empty())
    {
        Block* block = searchQueue.front();
        searchQueue.pop();
        for (Block* neighbor : block->getAdjacentBlocks(heatLossMap))
        {
            neighbor->setDistance(block->distance + neighbor->cost);
            if (!neighbor->visited)
            {
                searchQueue.emplace(neighbor);
                neighbor->visited = true;
            }
        }
    }

    printDistances(heatLossMap);

    int64_t distance = heatLossMap[heatLossMap.size() - 1][heatLossMap[0].size() - 1].distance;
    if (usingExample)
    {
        if (distance != 102)
        {
            printf("Unit test failed.\n");
        }
    }
    return distance;
}


ClumsyCrucible::Block::Block(char c, Vector2 position)
    :position(position)
{
    distance = -1;
    cost = c - 48;
}

void ClumsyCrucible::Block::setDistance(int newDistance)
{
    if (distance < 0)
    {
        distance = newDistance;
        return;
    }
    distance = min(newDistance, distance);
}

std::vector<ClumsyCrucible::Block*> ClumsyCrucible::Block::getAdjacentBlocks(std::vector<std::vector<Block>>& map)
{
    int width = map[0].size();
    int height = map.size();
    vector<Block*> result;
    vector<Vector2> adjacentPositions = { position + Vector2(1, 0), position + Vector2(-1, 0), position + Vector2(0, 1), position + Vector2(0, -1) };
    for (Vector2 adjacentPosition : adjacentPositions)
    {
        if (adjacentPosition.insideBounds(width, height))
        {
            result.push_back(&map[adjacentPosition.y][adjacentPosition.x]);
        }
    }
    return result;
}

void ClumsyCrucible::printDistances(vector<vector<Block>>& map)
{
    for (vector<Block>& line : map)
    {
        for (Block& block : line)
        {
            if (block.distance > 99)
            {
                printf("%i ", block.distance);
            }
            else if (block.distance > 9)
            {
                printf(" %i ", block.distance);
            }
            else
            {
                printf("  %i ", block.distance);
            }
        }
        printf("\n");
    }
}
