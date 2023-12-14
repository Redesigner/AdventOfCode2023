#include "ParabolicReflector.h"

#include <fstream>
#include <vector>
#include <string>

using namespace std;

int64_t ParabolicReflector::get()
{
    fstream file = fstream("Day14/input.txt");

    if (!file.is_open())
    {
        return -1;
    }


    string line;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    int width = lines[0].size();
    int height = lines.size();

    vector<int> highestPosition;
    for (int i = 0; i < width; ++i)
    {
        highestPosition.push_back(0);
    }

    int sum = 0;
    for (int y = 0; y < lines.size(); ++y)
    {
        string& line = lines[y];
        for (int x = 0; x < line.size(); ++x)
        {
            char& c = line[x];
            if (c == 'O')
            {
                sum += height - highestPosition[x];
                highestPosition[x]++;
                continue;
            }
            if (c == '#')
            {
                highestPosition[x] = y + 1;
            }
        }
    }
    return sum;
}

int64_t ParabolicReflector::get2()
{
    fstream file = fstream("Day14/input.txt");

    if (!file.is_open())
    {
        return -1;
    }


    string line;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    moveNorth(lines);

    int width = lines[0].size();
    int height = lines.size();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x);
    }
}

void ParabolicReflector::moveNorth(std::vector<std::string>& values)
{
    int width = values[0].size();
    int height = values.size();

    vector<int> highestPosition;
    for (int i = 0; i < width; ++i)
    {
        highestPosition.push_back(0);
    }

    for (int y = 0; y < values.size(); ++y)
    {
        string& line = values[y];
        for (int x = 0; x < line.size(); ++x)
        {
            char& c = line[x];
            if (c == 'O')
            {
                c = '.';
                values[highestPosition[x]][x] = 'O';
                highestPosition[x]++;
                continue;
            }
            if (c == '#')
            {
                highestPosition[x] = y + 1;
            }
        }
    }
}
