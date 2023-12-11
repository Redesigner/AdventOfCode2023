#include "CosmicExpansion.h"

#include <string>
#include <fstream>

int CosmicExpansion::get()
{
    std::fstream file = std::fstream("Day11/input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }
    std::string line;

    std::vector<Vector2> galaxies;
    int currentY = 0;
    int currentX = 0;
    while (std::getline(file, line))
    {
        currentX = 0;
        for (char c : line)
        {
            if (c == '#')
            {
                galaxies.emplace_back(currentX, currentY);
            }
            currentX++;
        }
        currentY++;
    }

    int width = currentX;
    int height = currentY;

    for (int i = 0; i < width; ++i)
    {
        if (!galaxiesInColumn(galaxies, i))
        {
            // printf("Expanding column %i\n", i);
            for (Vector2& galaxy : galaxies)
            {
                if (galaxy.x > i)
                {
                    galaxy.x++;
                }
            }
            width++;
            i++;
        }
    }
    for (int i = 0; i < height; ++i)
    {
        if (!galaxiesInRow(galaxies, i))
        {
            // printf("Expanding row %i\n", i);
            for (Vector2& galaxy : galaxies)
            {
                if (galaxy.y > i)
                {
                    galaxy.y++;
                }
            }
            height++;
            i++;
        }
    }
    int sum = 0;
    for (int i = 0; i < galaxies.size(); ++i)
    {
        for (int j = i + 1; j < galaxies.size(); ++j)
        {
            sum += std::abs(galaxies[i].x - galaxies[j].x) + std::abs(galaxies[i].y - galaxies[j].y);
        }
    }
    return sum;
}

int64_t CosmicExpansion::get2()
{
    std::fstream file = std::fstream("Day11/input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }
    std::string line;

    std::vector<Vector2> galaxies;
    int currentY = 0;
    int currentX = 0;
    while (std::getline(file, line))
    {
        currentX = 0;
        for (char c : line)
        {
            if (c == '#')
            {
                galaxies.emplace_back(currentX, currentY);
            }
            currentX++;
        }
        currentY++;
    }

    int width = currentX;
    int height = currentY;

    const int expansionDistance = 1000000 - 1;

    for (int i = 0; i < width; ++i)
    {
        if (!galaxiesInColumn(galaxies, i))
        {
            // printf("Expanding column %i\n", i);
            for (Vector2& galaxy : galaxies)
            {
                if (galaxy.x > i - 1)
                {
                    galaxy.x += expansionDistance;
                }
            }
            width += expansionDistance;
            i += expansionDistance;
        }
    }
    for (int i = 0; i < height; ++i)
    {
        if (!galaxiesInRow(galaxies, i))
        {
            // printf("Expanding row %i\n", i);
            for (Vector2& galaxy : galaxies)
            {
                if (galaxy.y > i - 1)
                {
                    galaxy.y += expansionDistance;
                }
            }
            height += expansionDistance;
            i += expansionDistance;
        }
    }
    int64_t sum = 0;
    for (int i = 0; i < galaxies.size(); ++i)
    {
        for (int j = i + 1; j < galaxies.size(); ++j)
        {
            sum += std::abs(galaxies[i].x - galaxies[j].x) + std::abs(galaxies[i].y - galaxies[j].y);
        }
    }
    return sum;
}

bool CosmicExpansion::galaxiesInColumn(const std::vector<Vector2>& galaxies, int x)
{
    for (const Vector2& galaxy : galaxies)
    {
        if (galaxy.x == x)
        {
            return true;
        }
    }
    return false;
}

bool CosmicExpansion::galaxiesInRow(const std::vector<Vector2>& galaxies, int y)
{
    for (const Vector2& galaxy : galaxies)
    {
        if (galaxy.y == y)
        {
            return true;
        }
    }
    return false;
}
