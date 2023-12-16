#include "FloorLava.h"

#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int64_t FloorLava::get()
{
    fstream file = fstream("Day16/input.txt", ios::in);
    //fstream file = fstream("Day16/test.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }


    vector<vector<Tile>> map;
    string line;
    while (getline(file, line))
    {
        vector<Tile> tiles;
        for (char c : line)
        {
            tiles.emplace_back(c);
        }
        map.emplace_back(tiles);
    }

    int mapWidth = map[0].size();
    int mapHeight = map.size();

    queue<pair<Vector2, Direction>> activeBeams;
    activeBeams.emplace(Vector2(0, 0), Right);
    
    while (!activeBeams.empty())
    {
        pair<Vector2, Direction> currentBeam = activeBeams.front();
        activeBeams.pop();

        while (true)
        {
            Vector2& currentPosition = currentBeam.first;
            Direction& currentDirection = currentBeam.second;
            if (currentPosition.y < 0 || currentPosition.y >= mapHeight)
            {
                break;
            }
            if (currentPosition.x < 0 || currentPosition.x >= mapWidth)
            {
                break;
            }
            Tile& currentTile = map[currentPosition.y][currentPosition.x];
            if (currentTile.tileType == Empty)
            {
                shiftPosition(currentPosition, currentDirection);
                if (currentDirection == Left || currentDirection == Right)
                {
                    if (currentTile.pathedHorizontally)
                    {
                        break;
                    }
                    currentTile.pathedHorizontally = true;
                }
                else if (currentDirection == Up || currentDirection == Down)
                {
                    if (currentTile.pathedVertically)
                    {
                        break;
                    }
                    currentTile.pathedVertically = true;
                }
                continue;
            }
            currentTile.pathedSpecial = true;
            if (currentTile.tileType == TopLeftMirror)
            {
                reflectTopLeft(currentPosition, currentDirection);
            }
            else if (currentTile.tileType == TopRightMirror)
            {
                reflectTopRight(currentPosition, currentDirection);
            }
            else if (currentTile.tileType == VerticalSplitter)
            {
                if (currentDirection == Left || currentDirection == Right)
                {
                    activeBeams.emplace(Vector2(currentPosition.x, currentPosition.y - 1), Up);
                    activeBeams.emplace(Vector2(currentPosition.x, currentPosition.y + 1), Down);
                    break;
                }
                else
                {
                    shiftPosition(currentPosition, currentDirection);
                }
            }
            else if (currentTile.tileType == HorizontalSplitter)
            {
                if (currentDirection == Up || currentDirection == Down)
                {
                    activeBeams.emplace(Vector2(currentPosition.x + 1, currentPosition.y), Right);
                    activeBeams.emplace(Vector2(currentPosition.x - 1, currentPosition.y), Left);
                    break;
                }
                else
                {
                    shiftPosition(currentPosition, currentDirection);
                }
            }
        }
    }

    int64_t sum = 0;
    for (vector<Tile>& tiles : map)
    {
        for (Tile& tile : tiles)
        {
            if (tile.pathedHorizontally || tile.pathedVertically || tile.pathedSpecial)
            {
                sum++;
                printf("#");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }

    return sum;
}

int64_t FloorLava::get2()
{
    fstream file = fstream("Day16/input.txt", ios::in);
    // fstream file = fstream("Day16/test.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }


    vector<vector<Tile>> mapOriginal;
    string line;
    while (getline(file, line))
    {
        vector<Tile> tiles;
        for (char c : line)
        {
            tiles.emplace_back(c);
        }
        mapOriginal.emplace_back(tiles);
    }

    int mapWidth = mapOriginal[0].size();
    int mapHeight = mapOriginal.size();

    vector<pair<Vector2, Direction>> startingPositions;
    for (int i = 0; i < mapWidth; ++i)
    {
        startingPositions.emplace_back(Vector2(i, 0), Down);
        startingPositions.emplace_back(Vector2(i, mapHeight - 1), Up);
    }
    for (int i = 0; i < mapHeight; ++i)
    {
        startingPositions.emplace_back(Vector2(0, i), Right);
        startingPositions.emplace_back(Vector2(mapWidth - 1, i), Left);
    }

    int64_t maxSum = 0;
    for (pair<Vector2, Direction>& startingPosition : startingPositions)
    {
        int64_t sum = 0;
        vector<vector<Tile>> map(mapOriginal);

        queue<pair<Vector2, Direction>> activeBeams;
        activeBeams.emplace(startingPosition);

        while (!activeBeams.empty())
        {
            pair<Vector2, Direction> currentBeam = activeBeams.front();
            activeBeams.pop();

            while (true)
            {
                Vector2& currentPosition = currentBeam.first;
                Direction& currentDirection = currentBeam.second;
                if (currentPosition.y < 0 || currentPosition.y >= mapHeight)
                {
                    break;
                }
                if (currentPosition.x < 0 || currentPosition.x >= mapWidth)
                {
                    break;
                }
                Tile& currentTile = map[currentPosition.y][currentPosition.x];
                if (currentTile.tileType == Empty)
                {
                    shiftPosition(currentPosition, currentDirection);
                    if (currentDirection == Left || currentDirection == Right)
                    {
                        if (currentTile.pathedHorizontally)
                        {
                            break;
                        }
                        currentTile.pathedHorizontally = true;
                    }
                    else if (currentDirection == Up || currentDirection == Down)
                    {
                        if (currentTile.pathedVertically)
                        {
                            break;
                        }
                        currentTile.pathedVertically = true;
                    }
                    continue;
                }
                currentTile.pathedSpecial = true;
                if (currentTile.tileType == TopLeftMirror)
                {
                    reflectTopLeft(currentPosition, currentDirection);
                }
                else if (currentTile.tileType == TopRightMirror)
                {
                    reflectTopRight(currentPosition, currentDirection);
                }
                else if (currentTile.tileType == VerticalSplitter)
                {
                    if (currentDirection == Left || currentDirection == Right)
                    {
                        activeBeams.emplace(Vector2(currentPosition.x, currentPosition.y - 1), Up);
                        activeBeams.emplace(Vector2(currentPosition.x, currentPosition.y + 1), Down);
                        break;
                    }
                    else
                    {
                        shiftPosition(currentPosition, currentDirection);
                    }
                }
                else if (currentTile.tileType == HorizontalSplitter)
                {
                    if (currentDirection == Up || currentDirection == Down)
                    {
                        activeBeams.emplace(Vector2(currentPosition.x + 1, currentPosition.y), Right);
                        activeBeams.emplace(Vector2(currentPosition.x - 1, currentPosition.y), Left);
                        break;
                    }
                    else
                    {
                        shiftPosition(currentPosition, currentDirection);
                    }
                }
            }
        }
        for (vector<Tile>& tiles : map)
        {
            for (Tile& tile : tiles)
            {
                if (tile.pathedHorizontally || tile.pathedVertically || tile.pathedSpecial)
                {
                    sum++;
                }
            }
        }
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}

void FloorLava::shiftPosition(Vector2& position, Direction direction)
{
    switch (direction)
    {
    case Right:
        position.x++;
        break;
    case Left:
        position.x--;
        break;
    case Up:
        position.y--;
        break;
    case Down:
        position.y++;
        break;
    }
}

void FloorLava::reflectTopLeft(Vector2& position, Direction& direction)
{
    switch (direction)
    {
    case Right:
        direction = Down;
        break;
    case Left:
        direction = Up;
        break;
    case Up:
        direction = Left;
        break;
    case Down:
        direction = Right;
        break;
    }
    shiftPosition(position, direction);
}

void FloorLava::reflectTopRight(Vector2& position, Direction& direction)
{
    switch (direction)
    {
    case Right:
        direction = Up;
        break;
    case Left:
        direction = Down;
        break;
    case Up:
        direction = Right;
        break;
    case Down:
        direction = Left;
        break;
    }
    shiftPosition(position, direction);
}

FloorLava::Tile::Tile(char c)
{
    switch (c)
    {
    case '.':
        tileType = Empty;
        break;
    case '/':
        tileType = TopRightMirror;
        break;
    case '\\':
        tileType = TopLeftMirror;
        break;
    case '|':
        tileType = VerticalSplitter;
        break;
    case '-':
        tileType = HorizontalSplitter;
        break;
    default:
        tileType = Invalid;
        break;
    }
}
