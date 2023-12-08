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

HauntedWasteland::Location::Location(std::string string)
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
