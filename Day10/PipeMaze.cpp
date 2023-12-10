#include "PipeMaze.h"

#include <fstream>
#include <string>
#include <iostream>

int PipeMaze::get()
{
    std::fstream file = std::fstream("Day10/input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }
    std::string line;
    std::vector<std::vector<Tile>> map;

    Vector2 currentPosition = Vector2(0, 0);
    Vector2 startPosition = Vector2(0, 0);
    while (std::getline(file, line))
    {
        std::vector<Tile> tiles;
        for (char c : line)
        {
            if (c == 'S')
            {
                startPosition = currentPosition;
            }
            tiles.emplace_back(c);
            currentPosition.x++;
        }
        map.emplace_back(tiles);
        tiles.clear();
        currentPosition.x = 0;
        currentPosition.y++;
    }
    
    std::vector<Vector2> startingPositions = {
        startPosition + Vector2::north(),
        // startPosition + Vector2::east(),
        startPosition + Vector2::south(),
        startPosition + Vector2::west()
    };

    for (Vector2 position : startingPositions)
    {
        if (position.isNegative())
        {
            continue;
        }
        traversePipe(map, position, startPosition);
    }
    int distance = 0;
    for (std::vector<Tile>& tiles : map)
    {
        for (Tile& tile : tiles)
        {
            if (!tile.isPipe())
            {
                //printf("    .");
            }
            else if (!tile.distanceSet())
            {
                //printf("    x");
            }
            else
            {
                int tileDistance = tile.getDistance();

                if (tileDistance > 999)
                {
                    //printf(" %i", tileDistance);
                }
                else if (tileDistance > 99)
                {
                    //printf("  %i", tileDistance);
                }
                else if (tileDistance > 9)
                {
                    //printf("   %i", tileDistance);
                }
                else
                {
                    //printf("    %i", tileDistance);
                }
                distance = std::max(distance, tileDistance);
            }
        }
        //printf("\n");
    }

    return distance;
}

int PipeMaze::get2()
{
    std::fstream file = std::fstream("Day10/input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }
    std::string line;
    std::vector<std::vector<Tile>> map;

    Vector2 currentPosition = Vector2(0, 0);
    Vector2 startPosition = Vector2(0, 0);
    while (std::getline(file, line))
    {
        std::vector<Tile> tiles;
        for (char c : line)
        {
            if (c == 'S')
            {
                startPosition = currentPosition;
            }
            tiles.emplace_back(c);
            currentPosition.x++;
        }
        map.emplace_back(tiles);
        tiles.clear();
        currentPosition.x = 0;
        currentPosition.y++;
    }

    std::vector<Vector2> startingPositions = {
        startPosition + Vector2::north(),
        // startPosition + Vector2::east(),
        startPosition + Vector2::south(),
        startPosition + Vector2::west()
    };

    for (Vector2 position : startingPositions)
    {
        if (position.isNegative())
        {
            continue;
        }
        traversePipe(map, position, startPosition);
    }

    int sum = 0;
    for (std::vector<Tile>& tiles : map)
    {
        sum += sumLine(tiles);
    }
    return sum;
}

int PipeMaze::traversePipe(std::vector<std::vector<Tile>>& map, Vector2 location, Vector2 startLocation)
{
    int currentDistance = 1;
    Vector2 previousLocation = startLocation;
    Vector2 currentLocation = location;
    
    while (true)
    {
        if (currentLocation.isNegative() || (currentLocation.x >= map[0].size() || currentLocation.y >= map.size()))
        {
            return currentDistance;
        }
        Tile& currentTile = map[currentLocation.y][currentLocation.x];
        if (!currentTile.isPipe())
        {
            return currentDistance;
        }
        /*if (currentTile.getDistance() <= currentDistance && currentTile.distanceSet())
        {
            return currentDistance;
        } */
        currentTile.setDistance(currentDistance);
        currentDistance++;
        Vector2 distanceTraveled = previousLocation - currentLocation;
        Vector2 newLocation = currentLocation + currentTile.getNext(distanceTraveled);
        previousLocation = currentLocation;
        currentLocation = newLocation;
    }
}

void PipeMaze::fillAdjacentTiles(std::vector<std::vector<Tile>>& map, Vector2 location)
{
    if (location.isNegative() || (location.x >= map[0].size() || location.y >= map.size()))
    {
        return;
    }
    Tile& tileToFill = map[location.y][location.x];
    // if we've already filled this tile, or the distance has been set (which means it's part of the loop)
    if (tileToFill.filled || tileToFill.distanceSet())
    {
        return;
    }
    // printf("Filling tile (%i, %i)\n", location.x, location.y);
    tileToFill.filled = true;

    std::vector<Vector2> locationsToFill = {
        location + Vector2::north(),
        location + Vector2::north() + Vector2::east(),
        location + Vector2::east(),
        location + Vector2::south() + Vector2::east(),
        location + Vector2::south(),
        location + Vector2::south() + Vector2::west(),
        location + Vector2::west(),
        location + Vector2::north() + Vector2::west()
    };

    for (Vector2 locationToFill : locationsToFill)
    {
        fillAdjacentTiles(map, locationToFill);
    }
}

int PipeMaze::sumLine(std::vector<Tile>& tiles)
{
    int sum = 0;
    bool open = true;
    for (Tile& tile : tiles)
    {
        if (tile.toPrint() == 'S')
        {
            open = true;
            printf("S");
            continue;
        }
        if (tile.isPipe() && tile.distanceSet())
        {
            wchar_t tileChar = tile.toPrint();
            if (tileChar == '|' || tileChar == 'F' || tileChar == '7')
            {
                open = !open;
            }
            printf("X");
            continue;
        }
        if (!open)
        {
            printf("I");
            sum++;
        }
        else
        {
            printf(".");
        }
    }
    printf("\n");
    return sum;
}

PipeMaze::Tile::Tile(char c)
{
    valid = true;
    set = false;
    distance = 0;
    switch (c)
    {
    case '|':
    {
        entrance = Vector2::north();
        exit = Vector2::south();
        //printChar = L'\u2551';
        printChar = c;
    }break;
    case '-':
    {
        entrance = Vector2::west();
        exit = Vector2::east();
        //printChar = L'\u2550';
        printChar = c;
    }break;
    case 'L':
    {
        entrance = Vector2::north();
        exit = Vector2::east();
        //printChar = L'\u255A';
        printChar = c;
    }break;
    case 'J':
    {
        entrance = Vector2::north();
        exit = Vector2::west();
        //printChar = L'\u255D';
        printChar = c;
    }break;
    case '7':
    {
        entrance = Vector2::west();
        exit = Vector2::south();
        //printChar = L'\u2557';
        printChar = c;
    }break;
    case 'F':
    {
        entrance = Vector2::south();
        exit = Vector2::east();
        //printChar = L'\u2554';
        printChar = c;
    }break;
    default:
    {
        entrance = Vector2(0, 0);
        exit = Vector2(0, 0);
        valid = false;
        printChar = ' ';
        if (c == 'S')
        {
            printChar = c;
        }
    }break;
    }
}

PipeMaze::Vector2 PipeMaze::Tile::getNext(Vector2 offset) const
{
    if (offset == entrance)
    {
        return exit;
    }
    if (offset == exit)
    {
        return entrance;
    }
    printf("Tried to enter a pipe from an invalid direction.\n");
    return offset;
}

int PipeMaze::Tile::getDistance() const
{
    return distance;
}

void PipeMaze::Tile::setDistance(int newDistance)
{
    if (!set)
    {
        set = true;
        distance = newDistance;
        return;
    }

    if (newDistance < distance)
    {
        distance = newDistance;
    }
}

bool PipeMaze::Tile::isPipe() const
{
    return valid;
}

bool PipeMaze::Tile::distanceSet() const
{
    return set;
}

wchar_t PipeMaze::Tile::toPrint() const
{
    return printChar;
}

const bool PipeMaze::Vector2::operator==(const Vector2& otherVector) const
{
    return x == otherVector.x && y == otherVector.y;
}

PipeMaze::Vector2 PipeMaze::Vector2::operator+(const Vector2& otherVector) const
{
    return Vector2(x + otherVector.x, y + otherVector.y);
}

PipeMaze::Vector2 PipeMaze::Vector2::operator-(const Vector2& otherVector) const
{
    return Vector2(x - otherVector.x, y - otherVector.y);
}

bool PipeMaze::Vector2::isNegative() const
{
    return x < 0 || y < 0;
}

PipeMaze::Vector2 PipeMaze::Vector2::north()
{
    return Vector2(0, -1);
}

PipeMaze::Vector2 PipeMaze::Vector2::south()
{
    return Vector2(0, 1);
}

PipeMaze::Vector2 PipeMaze::Vector2::east()
{
    return Vector2(1, 0);
}

PipeMaze::Vector2 PipeMaze::Vector2::west()
{
    return Vector2(-1, 0);
}
