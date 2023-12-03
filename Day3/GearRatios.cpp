#include "GearRatios.h"

#include <fstream>
#include <iostream>
#include <string>

int GearRatios::get()
{
    std::fstream file = std::fstream("Day3/input.txt", std::ios::in);

    if (!file.is_open())
    {
        std::printf("Failed to open file.");
        return 0;
    }

    Grid grid = Grid(file);
    return grid.process([](Grid* grid, char c, int x, int y)
        {
            if (!charIsSymbol(c))
            {
                return 0;
            }
            int total = 0;
            for (std::pair<int, int> offset : grid->offsets)
            {
                int newX = x + offset.first;
                int newY = y + offset.second;
                char newChar = grid->getCharacter(newX, newY);
                if (newChar == 'x' || newChar == '.')
                {
                    continue;
                }

                int currentInt = 0;
                int charAsInt = charToInt(newChar);
                while (charAsInt >= 0)
                {
                    newX--;
                    newChar = grid->getCharacter(newX, newY);
                    charAsInt = charToInt(newChar);
                }
                newX++;
                newChar = grid->getCharacter(newX, newY);
                charAsInt = charToInt(newChar);
                while (charAsInt >= 0)
                {
                    currentInt *= 10;
                    currentInt += charAsInt;
                    grid->setCharacter(newX, newY, '.');
                    newX++;
                    newChar = grid->getCharacter(newX, newY);
                    charAsInt = charToInt(newChar);
                }
                std::printf("'%c' (%i, %i) : %i\n", c, offset.first, offset.second, currentInt);
                total += currentInt;
            }
            return total;
        });
}

int GearRatios::getGears()
{
    std::fstream file = std::fstream("Day3/input.txt", std::ios::in);

    if (!file.is_open())
    {
        std::printf("Failed to open file.");
        return 0;
    }

    Grid grid = Grid(file);
    return grid.process([](Grid* grid, char c, int x, int y)
        {
            if (c != '*')
            {
                return 0;
            }
            int total = 1;
            int numParts = 0;
            std::vector<std::pair<int, int>> ignoreValues;
            for (std::pair<int, int> offset : grid->offsets)
            {
                int newX = x + offset.first;
                int newY = y + offset.second;

                bool ignoreOffset = false;
                for (std::pair<int, int> ignoreValue : ignoreValues)
                {
                    if (ignoreValue.first == newX && ignoreValue.second == newY)
                    {
                        ignoreOffset = true;
                        continue;
                    }
                }
                if (ignoreOffset)
                {
                    continue;
                }
                char newChar = grid->getCharacter(newX, newY);
                if (newChar == 'x' || newChar == '.')
                {
                    continue;
                }

                int currentInt = 0;
                int charAsInt = charToInt(newChar);
                while (charAsInt >= 0)
                {
                    newX--;
                    newChar = grid->getCharacter(newX, newY);
                    charAsInt = charToInt(newChar);
                }
                newX++;
                newChar = grid->getCharacter(newX, newY);
                charAsInt = charToInt(newChar);
                while (charAsInt >= 0)
                {
                    currentInt *= 10;
                    currentInt += charAsInt;
                    newX++;
                    newChar = grid->getCharacter(newX, newY);
                    charAsInt = charToInt(newChar);
                    ignoreValues.push_back(std::pair<int, int>(newX, newY));
                    // grid->setCharacter(newX, newY, '.');
                }
                numParts++;
                total *= currentInt;
                printf("Gear found part %i\n", currentInt);
            }
            if (numParts != 2)
            {
                std::printf("Gear  at (%i, %i) has % i gears and is invalid\n", x, y, numParts);
                return 0;
            }
            return total;
        });
}

int GearRatios::charToInt(char c)
{
    int charAsInt = static_cast<int>(c) - 48;
    if (charAsInt >= 0 && charAsInt < 10)
    {
        return charAsInt;
    }
    return -1;
}

bool GearRatios::charIsSymbol(char c)
{
    std::vector<char> symbols = { '!', '@', '#', '$', '%', '^', '&', '*', '-', '=', '+', '/'};
    for (char symbol : symbols)
    {
        if (c == symbol)
        {
            return true;
        }
    }
    return false;
}

GearRatios::Grid::Grid(std::fstream& file)
{
    std::string line;
    while (std::getline(file, line))
    {
        processLine(line);
    }
    offsets = {
        {-1, -1},   {0, -1},    {1, -1},
        {-1, 0},                {1, 0},
        {-1, 1},    {0, 1},     {1, 1}
    };
}

int GearRatios::Grid::process(int (*function)(Grid* grid, char c, int xPos, int yPos))
{
    int total = 0;
    for (int y = 0; y < data.size(); y++)
    {
        for (int x = 0; x < data[y].size(); x++)
        {
            char c = data[y][x];
            total += function(this, c, x, y);
        }
    }
    return total;
}

void GearRatios::Grid::processLine(std::string& string)
{
    std::vector<char> currentLine;
    for (char c : string)
    {
        if (c == '\n')
        {
            continue;
        }
        currentLine.push_back(c);
    }
    data.push_back(currentLine);
}

char GearRatios::Grid::getCharacter(int x, int y) const
{
    if (y < 0 || y >= data.size())
    {
        // position is out of bounds
        return 'x';
    }
    const std::vector<char>& currentRow = data[y];
    if (x < 0 || x >= data.size())
    {
        return 'x';
    }
    return currentRow[x];
}

void GearRatios::Grid::setCharacter(int x, int y, char c)
{
    if (y < 0 || y >= data.size())
    {
        // position is out of bounds
        return;
    }
    std::vector<char>& currentRow = data[y];
    if (x < 0 || x >= data.size())
    {
        return;
    }
    currentRow[x] = c;
}
