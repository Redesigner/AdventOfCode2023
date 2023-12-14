#include "HotSprings.h"

#include <fstream>
#include <stack>

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
    int i = 0;
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
        printf("%i:\t%i\n", i + 1, valuesThisString);
        i++;
        sum += valuesThisString;
    }
    return sum;
}

uint64_t HotSprings::get2()
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

    int64_t sum = 0;
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
        springCondition.conditionString = springCondition.conditionString;
    }
    int i = 0;
    for (ConditionEntry& entry : springConditions)
    {
        //int value = entry.getSum();
        int64_t value = count(entry.conditionString, entry.springGroups, false);
        printf("%i:\t%lld\n", i + 1, value);
        // sum += entry.getSum();
        sum += value;
        i++;
    }
    
    return sum;
}

uint64_t HotSprings::count(std::string_view string, const std::vector<int>& values, bool valid)
{
    // this algorithm is from this post by reddit user DrunkHacker: https://www.reddit.com/r/adventofcode/comments/18ge41g/comment/kd2ihcg/?utm_name=mweb3xcss
    auto input = std::make_tuple(std::string(string), values, valid);
    if (valuesMap.contains(input))
    {
        return valuesMap[input];
    }
    int sum = 0;
    for (int value : values)
    {
        sum += value;
    }

    if (sum == 0)
    {
        // if we're out of values to check, but we still have numbers in the string, this can't be valid
        if (Common::stringContains(string, '#'))
        {
            valuesMap.emplace(input, 0);
            return 0;
        }
        valuesMap.emplace(input, 1);
        return 1;
    }
    // we've reached the end of the string
    if (string.empty())
    {
        if (sum == 0)
        {
            valuesMap.emplace(input, 1);
            return 1;
        }
        valuesMap.emplace(input, 0);
        return 0;
    }
    // Our current value is 0, so we want to check the next number in out value set
    if (values[0] == 0)
    {
        if (string[0] == '?' || string[0] == '.')
        {
            std::vector newValues(values);
            newValues.erase(newValues.begin());
            uint64_t result = count(string.substr(1, string.size() - 1), newValues, false);
            valuesMap.emplace(input, result);
            return result;
        }
        valuesMap.emplace(input, 0);
        return 0;
    }
    if (valid)
    {
        if (string[0] == '?' || string[0] == '#')
        {
            std::vector<int> newValues(values);
            --newValues[0];
            uint64_t result = count(string.substr(1, string.size() - 1), newValues, true);
            valuesMap.emplace(input, result);
            return result;
        }
        valuesMap.emplace(input, 0);
        return 0;
    }
    // if our next character is #, decrement our current group size and check the next part of the string
    if (string[0] == '#')
    {
        std::vector<int> newValues(values);
        --newValues[0];
        uint64_t result = count(string.substr(1, string.size() - 1), newValues, true);
        valuesMap.emplace(input, result);
        return result;
    }
    if (string[0] == '.')
    {
        uint64_t result = count(string.substr(1, string.size() - 1), values, false);
        valuesMap.emplace(input, result);
        return result;
    }
    std::vector<int> newValues(values);
    newValues[0]--;
    // add up the possibilities of the string being either
    uint64_t result = count(string.substr(1, string.size() - 1), values, false) + count(string.substr(1, string.size() - 1), newValues, true);
    valuesMap.emplace(input, result);
    return result;
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
    if (string.size() < 1)
    {
        return {};
    }
    size_t firstUnknownValue = string.find('?');
    if (firstUnknownValue == std::string::npos)
    {
        std::vector <std::string> result = { string };
        return result;
    }

    size_t substringStart = firstUnknownValue + 1;
    std::string startString = string.substr(0, firstUnknownValue);
    int substringLength = string.size() - substringStart;
    if (substringLength < 1)
    {
        std::vector <std::string> result = { startString + "#", startString + "." };
        return result; 
    }

    std::vector<std::string> result;
    std::string subString = string.substr(substringStart, substringLength);
    for (std::string subGuess : getAllPossibleValues(subString))
    {
        result.emplace_back(startString + "#" + subGuess);
        result.emplace_back(startString + "." + subGuess);
    }
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

int HotSprings::ConditionEntry::getSum() const
{
    /*printf("Calculating sum:\n");
    printf("\"%s\" ", conditionString.c_str());
    for (int value : springGroups)
    {
        printf("%i, ", value);
    }
    printf("\n"); */
    int sum = 0;
    std::vector<int> cursors;
    int currentCursor = 0;
    while (true)
    {
        // printf("%i : ", currentCursor);
        if (cursors.size() == springGroups.size())
        {
            // printf("++ <== \n");
            sum++;
            int previousValue = 0;
            /*for (int i = 0; i < cursors.size(); ++i)
            {
                printf("%s%s", std::string(cursors[i] - previousValue, '.').c_str(), std::string(springGroups[i], '#').c_str());
                previousValue = cursors[i] + springGroups[i];
            }
            printf("\n"); */
            currentCursor = cursors.back() + 1;
            cursors.pop_back();
            continue;
        }
        int currentGroupSize = springGroups[cursors.size()];
        std::string currentGroupString = "." + std::string(currentGroupSize, '#') + ".";
        if (canInsert(currentGroupString, currentCursor))
        {
            // printf("==> ");
            cursors.push_back(currentCursor);
            currentCursor += currentGroupSize + 1;
            continue;
        }
        currentCursor++;
        if (currentCursor >= conditionString.size())
        {
            if (cursors.empty())
            {
                return sum;
            }
            // printf("<== \n");
            currentCursor = cursors.back() + 1;
            cursors.pop_back();
        }
        if (currentCursor >= conditionString.size())
        {
            return sum;
        }
    }
}

bool HotSprings::ConditionEntry::canInsert(std::string& string, size_t startIndex) const
{
    if (string.size() == 3 && startIndex == 1)
    {
        startIndex = 1;
    }
    if (startIndex + string.size() > conditionString.size())
    {
        return false;
    }
    for (int i = 0; i < string.size(); ++i)
    {
        char c = conditionString[startIndex + i];
        if (c == '?')
        {
            continue;
        }
        if (c != string[i])
        {
            return false;
        }
    }
    return true;
}
