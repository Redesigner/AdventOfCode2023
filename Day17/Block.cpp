#include "Block.h"

using namespace std;

Block::Block(char c, Vector2 position)
    :position(position)
{
    cost = c - 48;
}

void Block::setDistance(int newDistance, Direction direction, int straight)
{
    auto pair = make_pair(straight, direction);
    if (distanceMap.contains(pair))
    {
        distanceMap.at(pair) = min(distanceMap.at(pair), newDistance);
        return;
    }
    distanceMap.emplace(pair, newDistance);
}

vector<ClumsyCrucible::QueueEntry> Block::getAdjacentBlocks(std::vector<std::vector<Block> >& map, Direction direction, int distance)
{
    int width = map[0].size();
    int height = map.size();
    vector<ClumsyCrucible::QueueEntry> result;
    vector<pair<Vector2, Direction>> adjacentPositions;
    switch (direction)
    {
    case Up:
    case Down:
        adjacentPositions = { 
            make_pair(position + Vector2::right(), Right),
            make_pair(position + Vector2::left(), Left)
        };
        break;
    case Left:
    case Right:
        adjacentPositions = { 
            make_pair(position + Vector2::down(), Down),
            make_pair(position + Vector2::up(), Up)
        };
        break;
    case None:
        adjacentPositions = { 
            make_pair(position + Vector2::right(), Right),
            make_pair(position + Vector2::left(), Left),
            make_pair(position + Vector2::down(), Down),
            make_pair(position + Vector2::up(), Up)
        };
        break;
    }
    for (pair<Vector2, Direction> adjacentPosition : adjacentPositions)
    {
        if (adjacentPosition.first.insideBounds(width, height))
        {
            Block* neighbor = &map[adjacentPosition.first.y][adjacentPosition.first.x];
            result.emplace_back(neighbor, adjacentPosition.second, 0);
        }
    }
    Vector2 forwardPosition = position + Vector2::fromDirection(direction);
    if (direction != None && distance < 3 && forwardPosition.insideBounds(width, height))
    {
        Block* neighbor = &map[forwardPosition.y][forwardPosition.x];
        result.emplace_back(neighbor, direction, distance + 1);
    }
    return result;
}

int Block::getShortestDistance() const
{
    int shortestDistance = 1000000;
    for (auto distanceEntry : distanceMap)
    {
        shortestDistance = min(shortestDistance, distanceEntry.second);
    }
    return shortestDistance;
}

bool Block::visited(int distance, Direction direction) const
{
    return visitedMap.contains(make_pair(distance, direction));
}

void Block::visit(int distance, Direction direction)
{
    if (!visited(distance, direction))
    {
        visitedMap.emplace(make_pair(distance, direction), true);
    }
}

int Block::getDistance(Direction direction, int distance) const
{
    auto pair = make_pair(distance, direction);
    if (distanceMap.contains(pair))
    {
        return distanceMap.at(pair);
    }
    return 0;
}
