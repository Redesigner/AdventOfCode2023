#include "MirageMaintenance.h"

#include <string>
#include <fstream>
#include <vector>

#include "../Common/Common.h"

int MirageMaintenance::get()
{
    std::fstream file = std::fstream("Day9/input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    std::string line;

    std::vector<std::vector<std::vector<int>>> historicalValueTables;

    while (std::getline(file, line))
    {
        std::vector<std::vector<int>> currentHistoricalValueTable;
        std::vector<int> values;
        std::vector<std::string> valueStrings = Common::splitString(line, ' ');
        for (const std::string& valueString : valueStrings)
        {
            values.push_back(atoi(valueString.c_str()));
        }
        currentHistoricalValueTable.push_back(values);
        historicalValueTables.push_back(currentHistoricalValueTable);
    }

    int sum = 0;
    for (std::vector<std::vector<int>>& currentHistoricalValueTable : historicalValueTables)
    {
        extrapolateUntilZero(currentHistoricalValueTable);
        sum += getSum(currentHistoricalValueTable);
    }

    return sum;
}

int MirageMaintenance::get2()
{
    std::fstream file = std::fstream("Day9/input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    std::string line;

    std::vector<std::vector<std::vector<int>>> historicalValueTables;

    while (std::getline(file, line))
    {
        std::vector<std::vector<int>> currentHistoricalValueTable;
        std::vector<int> values;
        std::vector<std::string> valueStrings = Common::splitString(line, ' ');
        for (const std::string& valueString : valueStrings)
        {
            values.push_back(atoi(valueString.c_str()));
        }
        currentHistoricalValueTable.push_back(values);
        historicalValueTables.push_back(currentHistoricalValueTable);
    }

    int sum = 0;
    for (std::vector<std::vector<int>>& currentHistoricalValueTable : historicalValueTables)
    {
        extrapolateUntilZero(currentHistoricalValueTable);
        sum += getHistory(currentHistoricalValueTable);
    }
    return sum;
}

bool MirageMaintenance::isZero(const std::vector<int>& values)
{
    for (const int value : values)
    {
        if (value != 0)
        {
            return false;
        }
    }
    return true;
}

std::vector<int> MirageMaintenance::extrapolateValues(const std::vector<int>& values)
{
    std::vector<int> result;
    for (int i = 0; i < values.size() - 1; ++i)
    {
        result.push_back(values[i + 1] - values[i]);
    }
    return result;
}

void MirageMaintenance::extrapolateUntilZero(std::vector<std::vector<int>>& values)
{
    int currentLevel = 0;
    while (true)
    {
        std::vector<int> extrapolatedValues = extrapolateValues(values[currentLevel]);
        values.push_back(extrapolatedValues);
        if (isZero(extrapolatedValues))
        {
            return;
        }
        currentLevel++;
    }
}

int MirageMaintenance::getSum(const std::vector<std::vector<int>>& values)
{
    int result = 0;
    for (const std::vector<int>& value : values)
    {
        result += value[value.size() - 1];
    }
    return result;
}

int MirageMaintenance::getHistory(const std::vector<std::vector<int>>& values)
{
    int difference = 0;
    for (int i = values.size() - 2; i >= 0; --i)
    {
        difference = values[i][0] - difference;
    }
    return difference;
}
