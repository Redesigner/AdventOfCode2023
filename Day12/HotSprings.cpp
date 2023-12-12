#include "HotSprings.h"

#include <fstream>

#include "../Common/Common.h"

int HotSprings::get()
{
    std::fstream file = std::fstream("Day12/input.txt", std::ios::in);
    // std::fstream file = std::fstream("Day12/test.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    std::string line;
    std::vector<ConditionEntry> springConditions;
    while (std::getline(file, line))
    {
        springConditions.emplace_back(line);
    }

    int sum = 0;
    for (ConditionEntry& springCondition : springConditions)
    {
        int valuesThisString = 0;
        //printf("Checking line:\n%s\n", springCondition.conditionString.c_str());
        std::vector<std::string> possibleValues = springCondition.getAllPossibleValues(springCondition.conditionString);
        for (std::string& string : possibleValues)
        {
            if (springCondition.isValidString(string))
            {
                valuesThisString++;
                //printf("%s\n", string.c_str());
            }
        }
        printf("%i possible arrangements for this line.\n", valuesThisString);
        sum += valuesThisString;
    }
    return sum;
}

int HotSprings::get2()
{
    // std::fstream file = std::fstream("Day12/input.txt", std::ios::in);
    std::fstream file = std::fstream("Day12/test.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    std::string line;
    std::vector<ConditionEntry> springConditions;
    while (std::getline(file, line))
    {
        springConditions.emplace_back(line);
    }

    int sum = 0;
    for (ConditionEntry& springCondition : springConditions)
    {
        std::string conditionString = springCondition.conditionString;
        springCondition.conditionString = conditionString + "?" + conditionString + "?" + conditionString + "?" + conditionString + "?" + conditionString;
        std::vector<int> newValues;
        for (int i = 0; i < 5; ++i)
        {
            for (int value : springCondition.springGroups)
            {
                newValues.push_back(value);
            }
        }
        springCondition.springGroups = newValues;


        int valuesThisString = 0;
        //printf("Checking line:\n%s\n", springCondition.conditionString.c_str());
        std::vector<std::string> possibleValues = springCondition.getAllPossibleValues(springCondition.conditionString);
        printf("Cached '%llu' values\n", valuesMap.size());
        printf("Checking '%llu' values for the current string\n", possibleValues.size());
        for (std::string& string : possibleValues)
        {
            if (springCondition.isValidString(string))
            {
                valuesThisString++;
                //printf("%s\n", string.c_str());
            }
        }
        printf("%i possible arrangements for this line.\n", valuesThisString);
        sum += valuesThisString;
    }
    return sum;
}

HotSprings::ConditionEntry::ConditionEntry(std::string& string)
{
    std::vector<std::string> strings = Common::splitString(string, ' ');
    conditionString = strings[0];
    springGroups = std::vector<int>();

    for (std::string& value : Common::splitString(strings[1], ','))
    {
        springGroups.emplace_back(atoi(value.c_str()));
    }
}

std::vector<std::string> HotSprings::ConditionEntry::getAllPossibleValues(std::string string) const
{
    if (valuesMap.contains(string))
    {
        return valuesMap[string];
    }
    if (string.size() < 1)
    {
        return {};
    }
    size_t firstUnknownValue = string.find('?');
    if (firstUnknownValue == std::string::npos)
    {
        std::vector <std::string> result = { string };
        valuesMap.insert(std::make_pair(string, result));
        return result;
    }

    size_t substringStart = firstUnknownValue + 1;
    std::string startString = string.substr(0, firstUnknownValue);
    int substringLength = string.size() - substringStart;
    if (substringLength < 1)
    {
        std::vector <std::string> result = { startString + "#", startString + "." };
        valuesMap.insert(std::make_pair(string, result));
        return result; 
    }

    std::vector<std::string> result;
    std::string subString = string.substr(substringStart, substringLength);
    for (std::string subGuess : getAllPossibleValues(subString))
    {
        result.emplace_back(startString + "#" + subGuess);
        result.emplace_back(startString + "." + subGuess);
    }
    valuesMap.insert(std::make_pair(string, result));
    return result;
}

bool HotSprings::ConditionEntry::isValidString(std::string& string) const
{
    std::vector<int> values;

    int i = 0;
    int currentCount = 0;
    bool inOperationalGroup = false;
    for (char c : string)
    {
        if (c == '.')
        {
            if (inOperationalGroup)
            {
                if (springGroups.size() <= i)
                {
                    return false;
                }
                if (springGroups[i] != currentCount)
                {
                    return false;
                }
                values.push_back(currentCount);
                inOperationalGroup = false;
                currentCount = 0;
                i++;
            }
            continue;
        }
        if (c == '#')
        {
            inOperationalGroup = true;
            currentCount++;
        }
    }
    if (inOperationalGroup)
    {
        values.push_back(currentCount);
    }
    return values == springGroups;
}
