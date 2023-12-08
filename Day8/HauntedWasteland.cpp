#include "HauntedWasteland.h"

#include <fstream>
#include <functional>
#include <map>

#include "../Common/Common.h"

int HauntedWasteland::get()
{
    std::fstream file = std::fstream("Day8/Input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    std::string directionString;
    std::getline(file, directionString);

    std::map<Location, Node> map;

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = Common::splitString(line, ' ');

        const std::string& key = tokens[0];
        const std::string& left = tokens[2].substr(1, 3);
        const std::string& right = tokens[3].substr(0, 3);

        map.insert(std::pair<Location, Node>(Location(key), Node(left, right)));
    }

    int stepsTaken = 0;
    Node currentNode = map.at(Location("AAA"));

    while (true)
    {
        for (int i = 0; i < directionString.size(); ++i)
        {
            if (directionString[i] == 'R')
            {
                stepsTaken++;
                if (currentNode.right == Location("ZZZ"))
                {
                    return stepsTaken;
                }
                currentNode = map.at(currentNode.right);
            }
            if (directionString[i] == 'L')
            {
                stepsTaken++;
                if (currentNode.left == Location("ZZZ"))
                {
                    return stepsTaken;
                }
                currentNode = map.at(currentNode.left);
            }
        }
    }
}

int64_t HauntedWasteland::get2()
{
    std::fstream file = std::fstream("Day8/Input.txt", std::ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    std::string directionString;
    std::getline(file, directionString);

    std::map<Location, Node> map;

    std::vector<Location> startingLocations;
    std::vector<int> minimumDistances;

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = Common::splitString(line, ' ');

        const std::string& key = tokens[0];
        const std::string& left = tokens[2].substr(1, 3);
        const std::string& right = tokens[3].substr(0, 3);

        map.insert(std::pair<Location, Node>(Location(key), Node(left, right)));

        if (key[2] == 'A')
        {
            startingLocations.emplace_back(key);
        }
    }

    for (const Location& startingLocation : startingLocations)
    {
        const int shortestDistance = getShortestValue(startingLocation, directionString, map);
        minimumDistances.push_back(shortestDistance);
    }
    return LCM(minimumDistances);
}

int HauntedWasteland::getShortestValue(const Location& startingLocation, const std::string directionString, const std::map<Location, Node>& map)
{
    int stepsTaken = 0;
    Node currentNode = map.at(startingLocation);

    while (true)
    {
        for (int i = 0; i < directionString.size(); ++i)
        {
            if (directionString[i] == 'R')
            {
                stepsTaken++;
                if (currentNode.right.c == 'Z')
                {
                    return stepsTaken;
                }
                currentNode = map.at(currentNode.right);
            }
            if (directionString[i] == 'L')
            {
                stepsTaken++;
                if (currentNode.left.c == 'Z')
                {
                    return stepsTaken;
                }
                currentNode = map.at(currentNode.left);
            }
        }
    }
}

int64_t HauntedWasteland::GCD(const int& a, const int& b)
{
    int64_t r02 = a;
    int64_t r01 = b;
    while (true)
    {
        int64_t remainder = r02 % r01;
        if (remainder == 0)
        {
            return r01;
        }
        r02 = r01;
        r01 = remainder;
    }
}

int64_t HauntedWasteland::GCD(const std::vector<int>& values)
{
    if (values.size() <= 2)
    {
        return 0;
    }
    int64_t currentGCD = values[0];
    for (const int value : values)
    {
        currentGCD = GCD(currentGCD, value);
    }
    return currentGCD;
}

int64_t HauntedWasteland::LCM(const std::vector<int>& values)
{
    int64_t valuesGCD = GCD(values);
    int64_t result = 1;
    for (int64_t value : values)
    {
        int64_t factor = value / valuesGCD;
        result *= factor;
    }
    return result * valuesGCD;
}


HauntedWasteland::Location::Location(const std::string& string)
{
    if (string.size() < 3)
    {
        a = '#';
        b = '#';
        c = '#';
        return;
    }
    a = string[0];
    b = string[1];
    c = string[2];
}

bool HauntedWasteland::Location::operator==(const Location& other) const
{
    return a == other.a && a == other.b && c == other.c;
}

bool HauntedWasteland::Location::operator>(const Location& other) const
{
    if (a != other.a)
    {
        return a > other.a;
    }
    if (b != other.b)
    {
        return b > other.b;
    }
    if (c != other.c)
    {
        return c > other.c;
    }
    return false;
}

bool HauntedWasteland::Location::operator<(const Location& other) const
{
    if (a != other.a)
    {
        return a < other.a;
    }
    if (b != other.b)
    {
        return b < other.b;
    }
    if (c != other.c)
    {
        return c < other.c;
    }
    return false;
}

HauntedWasteland::Node::Node(const std::string& left, const std::string& right)
    :left(left), right(right)
{
}

bool HauntedWasteland::Node::operator==(const Node& other) const
{
    return left == other.left && right == other.right;
}
