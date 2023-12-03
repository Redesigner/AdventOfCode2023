#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace GearRatios
{
    class Grid
    {
    public:
        Grid();
        Grid(std::fstream& file);

        int process(int (*function)(Grid* grid, char c, int xPos, int yPos));

        char getCharacter(int x, int y) const;

        void setCharacter(int x, int y, char c);

    private:
        void processLine(std::string& string);

    public:
        std::vector<std::pair<int, int>> offsets;

    private:
        std::vector<std::vector<char>> data;
    };

    int get();

    int getGears();

    int charToInt(char c);

    bool charIsSymbol(char c);
}