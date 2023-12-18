#include "LavaductLagoon.h"

#include <fstream>
#include <string>
#include <queue>

using namespace std;

int64_t LavaductLagoon::get()
{
    bool useExample = false;
    fstream file = useExample ? fstream("Day18/test.txt", ios::in) : fstream("Day18/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    ExpandingMap map = ExpandingMap(1, 1);


    string line;
    Vector2 currentPosition = Vector2(0, 0);
    while (getline(file, line))
    {
        vector<string> data = Common::splitString(line, ' ');
        Direction direction = getDirection(data[0][0]);
        int movement = atoi(data[1].c_str()); // convert our 1-digit char to number quickly
        uint32_t color = Common::hexStringToInt(data[2].substr(2, 6));
        
        Vector2 movementVector = Vector2::fromDirection(direction);
        for (int i = 0; i <= movement; ++i)
        {
            map.placeTile(color, currentPosition);
            if (i != movement)
            {
                currentPosition = movementVector + currentPosition;
            }
        }
    }
    map.fill();
    return map.sum();
}

int64_t LavaductLagoon::get2()
{
    bool useExample = false;
    fstream file = useExample ? fstream("Day18/test.txt", ios::in) : fstream("Day18/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    vector<Vector2> positions;
    Vector2 currentPosition = Vector2(0, 0);
    string line;
    int64_t perimeter = 0;
    while (getline(file, line))
    {
        vector<string> data = Common::splitString(line, ' ');
        int movement = Common::hexStringToInt(data[2].substr(2, 5));
        // int movement = atoi(data[1].c_str());
        Direction direction = getDirectionFromHex(data[2][7]);
        // Direction direction = getDirection(data[0][0]);
        perimeter += movement;
        Vector2 movementVector = Vector2::fromDirection(direction) * movement;
        currentPosition = currentPosition + movementVector;
        positions.push_back(currentPosition);
    }

    int64_t sum = 0;
    for (int i = 0; i < positions.size(); ++i)
    {
        // printf("(%i, %i)\n", positions[i].x, positions[i].y);
        Vector2 topValue = positions[i];
        Vector2 bottomValue = i == positions.size() - 1 ? positions[0] : positions[i + 1];
        int64_t increase = topValue.cross(bottomValue);
        sum += increase;
    }
    return (sum + perimeter) / 2 + 1;
}

Direction LavaductLagoon::getDirectionFromHex(char c)
{
    switch (c)
    {
    case '3':
        return Up;
    case '1':
        return Down;
    case '0':
        return Right;
    case '2':
        return Left;
    default:
        return None;
    }
}


Direction LavaductLagoon::getDirection(char c)
{
    switch (c)
    {
    case 'U':
        return Up;
    case 'D':
        return Down;
    case 'R':
        return Right;
    case 'L':
        return Left;
    default:
        return None;
    }
}

LavaductLagoon::ExpandingMap::ExpandingMap(int width, int height)
    :width(width), height(height)
{
    vector<Tile> emptyTileRow;
    for (int x = 0; x < width; ++x)
    {
        emptyTileRow.emplace_back();
    }
    for (int y = 0; y < height; ++y)
    {
        tiles.emplace_back(emptyTileRow);
    }
    xOffset = 0;
    yOffset = 0;
}

LavaductLagoon::Tile* LavaductLagoon::ExpandingMap::get(Vector2 position)
{
    if (position.x < -xOffset || position.x >= width - xOffset)
    {
        return nullptr;
    }
    if (position.y < -yOffset || position.y >= height - yOffset)
    {
        return nullptr;
    }
    return &tiles[position.y - yOffset][position.x - xOffset];
}

void LavaductLagoon::ExpandingMap::placeTile(int32_t color, Vector2 position)
{
    expandToPosition(position.x, position.y);
    Tile& tile = tiles[position.y + yOffset][position.x + xOffset];
    tile.color = color;
    tile.dug = true;
}

void LavaductLagoon::ExpandingMap::expandToPosition(int x, int y)
{
    if (width - xOffset - 1 < x)
    {
        int expansion = x - width + xOffset + 1;
        for (int i = 0; i < expansion; ++i)
        {
            insertColumnRight();
        }
    }
    if (height - yOffset - 1 < y)
    {
        int expansion = y - height + yOffset + 1;
        for (int i = 0; i < expansion; ++i)
        {
            insertRowBottom();
        }
    }
    if (x < -xOffset)
    {
        int expansion = -x - xOffset;
        for (int i = 0; i < expansion; ++i)
        {
            insertColumnLeft();
        }
    }
    if (y < -yOffset)
    {
        int expansion = -y - yOffset;
        for (int i = 0; i < expansion; ++i)
        {
            insertRowTop();
        }
    }
}

void LavaductLagoon::ExpandingMap::fill()
{
    queue<Vector2> positionsToFill;
    for (int x = 0; x < tiles[0].size(); ++x)
    {
        positionsToFill.emplace(x, 0);
        positionsToFill.emplace(x, tiles.size() - 1);
    }
    for (int y = 0; y < tiles.size(); ++y)
    {
        positionsToFill.emplace(0, y);
        positionsToFill.emplace(tiles[0].size() - 1, y);
    }

    vector<Vector2> adjacentPositions = { Vector2::up(), Vector2::down(), Vector2::left(), Vector2::right() };

    while (!positionsToFill.empty())
    {
        Vector2 position = positionsToFill.front();
        positionsToFill.pop();
        Tile& tile = tiles[position.y][position.x];
        if (tile.dug || tile.exterior)
        {
            continue;
        }
        tile.exterior = true;
        for (Vector2 adjacentPosition : adjacentPositions)
        {
            Vector2 nextPosition = adjacentPosition + position;
            if (nextPosition.x < tiles[0].size() && nextPosition.x >= 0 && nextPosition.y < tiles.size() && nextPosition.y >= 0)
            {
                positionsToFill.push(nextPosition);
            }
        }
    }
}

string LavaductLagoon::ExpandingMap::toString() const
{
    string result;
    for (const vector<Tile>& row : tiles)
    {
        for (const Tile& tile : row)
        {
            result.push_back(tile.dug ? '#' : '.');
        }
        result.push_back('\n');
    }
    return result;
}

int64_t LavaductLagoon::ExpandingMap::sum() const
{
    int64_t result = 0;
    for (const vector<Tile>& row : tiles)
    {
        for (const Tile& tile : row)
        {
            if (!tile.exterior)
            {
                result++;
            }
        }
    }
    return result;
}

void LavaductLagoon::ExpandingMap::insertColumnLeft()
{
    for (int y = 0; y < height; ++y)
    {
        tiles[y].emplace(tiles[y].begin());
    }
    xOffset++;
    width++;
}

void LavaductLagoon::ExpandingMap::insertColumnRight()
{
    for (int y = 0; y < height; ++y)
    {
        tiles[y].emplace_back();
    }
    width++;
}

void LavaductLagoon::ExpandingMap::insertRowBottom()
{
    vector<Tile> tileRow;
    for (int x = 0; x < width; ++x)
    {
        tileRow.emplace_back();
    }
    tiles.emplace_back(tileRow);
    height++;
}

void LavaductLagoon::ExpandingMap::insertRowTop()
{
    vector<Tile> tileRow;
    for (int x = 0; x < width; ++x)
    {
        tileRow.emplace_back();
    }
    tiles.emplace(tiles.begin(), tileRow);
    height++;
    yOffset++;
}
