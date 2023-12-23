#include "LongWalk.h"

#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int64_t LongWalk::get()
{
    bool useExample = false;
    fstream file = useExample ? fstream("Day23/test.txt", ios::in) : fstream("Day23/input.txt", ios::in);
    if (!file.is_open())
    {
        printf("Failed to open file.\n");
        return -1;
    }

    vector<vector<Tile>> map;
    Vector2 currentPosition = Vector2(0, 0);
    string line;
    while (getline(file, line))
    {
        currentPosition.x = 0;
        vector<Tile> row;
        for (char c : line)
        {
            row.emplace_back(currentPosition, c);
            currentPosition.x++;
        }
        map.push_back(row);
        currentPosition.y++;
    }

    queue<tuple<Direction, Tile*, int>> currentPaths;
    vector<int> distances;
    currentPaths.push(make_tuple(Down, &map[0][1], 0));

    while (!currentPaths.empty())
    {
        tuple<Direction, Tile*, int> currentPath = currentPaths.front();
        currentPaths.pop();
        vector<pair<Direction, Tile*>> availableTiles = get<1>(currentPath)->getAdjacentTiles(map, get<0>(currentPath));
        if (availableTiles.empty())
        {
            distances.push_back(get<2>(currentPath));
            continue;
        }
        for (pair<Direction, Tile*> availableTile : availableTiles)
        {
            currentPaths.push(make_tuple(availableTile.first, availableTile.second, get<2>(currentPath) + 1));
        }
    }
    int sum = 0;
    for (int distance : distances)
    {
        sum = max(sum, distance);
    }
    return sum;
}

LongWalk::Tile::Tile(Vector2 position, char c)
    :position(position)
{
    switch (c)
    {
    case '.':
        tileType = Path;
        slopeDirection = None;
        break;
    case '#':
        tileType = Forest;
        slopeDirection = None;
        break;
    case '^':
        tileType = Slope;
        slopeDirection = Up;
        break;
    case '<':
        tileType = Slope;
        slopeDirection = Left;
        break;
    case '>':
        tileType = Slope;
        slopeDirection = Right;
        break;
    case 'v':
        tileType = Slope;
        slopeDirection = Down;
        break;
    }
}

vector<pair<Direction, LongWalk::Tile*>> LongWalk::Tile::getAdjacentTiles(vector<vector<Tile>>& map, Direction direction) const
{
    vector<pair<Direction, Tile*>> result;
    size_t width = map[0].size();
    size_t height = map.size();

    vector<Vector2> adjacentPositions;
    vector<Direction> adjacentDirections = getAdjacentDirections(direction);
    for (Direction availableDirection : adjacentDirections)
    {
        adjacentPositions.push_back(position + Vector2::fromDirection(availableDirection));
    }
    for (int i = 0; i < adjacentPositions.size(); ++i)
    {
        Vector2 adjacentPosition = adjacentPositions[i];
        Direction adjacentDirection = adjacentDirections[i];
        if (adjacentPosition.x < 0 || adjacentPosition.x >= width || adjacentPosition.y < 0 || adjacentPosition.y >= height)
        {
            continue;
        }
        Tile* adjacentTile = &map[adjacentPosition.y][adjacentPosition.x];
        if (adjacentTile->tileType == Forest)
        {
            continue;
        }
        if (adjacentTile->tileType == Slope)
        {
            if (adjacentTile->slopeDirection != adjacentDirection)
            {
                continue;
            }
        }
        result.emplace_back(adjacentDirection, adjacentTile);
    }
    return result;
}

vector<Direction> LongWalk::Tile::getAdjacentDirections(Direction direction) const
{
    switch (tileType)
    {
    case Path:
    {
        switch (direction)
        {
        case Up:
            return { Up, Left, Right };
        case Down:
            return { Down, Left, Right };
        case Left:
            return { Left, Up, Down };
        case Right:
            return { Right, Up, Down };
        default:
            return { };
        }
    }
    case Forest:
        return { };
    case Slope:
        return { slopeDirection };
    default:
        return { };
    }
}
