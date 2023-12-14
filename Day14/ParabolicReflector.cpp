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
    // fstream file = fstream("Day14/input.txt");
    fstream file = fstream("Day14/test.txt");

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

    vector<string> valuesLastCycle = lines;
    int i = 0;
    int width = lines[0].size();
    int height = lines.size();

    while (!moveCycle(lines))
    //while(i < 500)
    {
        // moveCycle(lines);
        int tempSum = 0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (lines[y][x] == 'O')
                {
                    tempSum += height - y;
                }
            }
        }
        printf("%i: %i\n", i, tempSum);
        i++;
    }

    int firstOccurence = 0;
    for (int i = 0; i < valuesMap.size(); ++i)
    {
        if (valuesMap[i].first == lines)
        {
            firstOccurence = i - 1;
            break;
        }
    }
    size_t repeatRate = valuesMap.size() - firstOccurence;
    // printf("Sequence repeats every %llu loops, starting at entry '%i'\n", repeatRate, firstOccurence);
    int sum = 0;

    int64_t finalPosition = 1000000000;
    int64_t finalValue = firstOccurence + (finalPosition - firstOccurence) % repeatRate - 1;
    // printf("Entry '%lld' is the same as entry '%lld'\n", finalPosition, finalValue);

    lines = valuesMap[finalValue].second;
    //int width = lines[0].size();
    //int height = lines.size();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (lines[y][x] == 'O')
            {
                sum += height - y;
            }
        }
    }
    return sum;
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

void ParabolicReflector::moveSouth(std::vector<std::string>& values)
{
    int width = values[0].size();
    int height = values.size();

    vector<int> highestPosition;
    for (int i = 0; i < width; ++i)
    {
        highestPosition.push_back(height - 1);
    }

    for (int y = height - 1; y >= 0; --y)
    {
        string& line = values[y];
        for (int x = 0; x < line.size(); ++x)
        {
            char& c = line[x];
            if (c == 'O')
            {
                c = '.';
                values[highestPosition[x]][x] = 'O';
                highestPosition[x]--;
                continue;
            }
            if (c == '#')
            {
                highestPosition[x] = y - 1;
            }
        }
    }
}

void ParabolicReflector::moveEast(std::vector<std::string>& values)
{
    int width = values[0].size();
    int height = values.size();

    vector<int> highestPosition;
    for (int i = 0; i < height; ++i)
    {
        highestPosition.push_back(width - 1);
    }

    for (int x = width - 1; x >= 0; --x)
    {
        for (int y = 0; y < height; ++y)
        {
            char& c = values[y][x];
            if (c == 'O')
            {
                c = '.';
                values[y][highestPosition[y]] = 'O';
                highestPosition[y]--;
                continue;
            }
            if (c == '#')
            {
                highestPosition[y] = x - 1;
            }
        }
    }
}

void ParabolicReflector::moveWest(std::vector<std::string>& values)
{
    int width = values[0].size();
    int height = values.size();

    vector<int> highestPosition;
    for (int i = 0; i < height; ++i)
    {
        highestPosition.push_back(0);
    }

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            char& c = values[y][x];
            if (c == 'O')
            {
                c = '.';
                values[y][highestPosition[y]] = 'O';
                highestPosition[y]++;
                continue;
            }
            if (c == '#')
            {
                highestPosition[y] = x + 1;
            }
        }
    }
}

bool ParabolicReflector::moveCycle(std::vector<std::string>& values)
{
    for (auto cachedValue : valuesMap)
    {
        if (cachedValue.first == values)
        {
            values = cachedValue.second;
            return true;
        }
    }
    std::vector<std::string> key = values;

    moveNorth(values);
    moveWest(values);
    moveSouth(values);
    moveEast(values);

    valuesMap.emplace_back(key, values);
    return false;
}
