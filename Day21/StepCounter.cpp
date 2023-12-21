#include "StepCounter.h"

#include <fstream>
#include <vector>
#include <string>
#include <queue>

#include "../Common/Common.h"

using namespace std;

int64_t StepCounter::get()
{
    bool useExample = false;
    fstream file = useExample ? fstream("Day21/test.txt", ios::in) : fstream("Day21/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    vector<vector<Node>> map;
    Vector2 startLocation = Vector2(0, 0);
    string line;

    int y = 0;
    while (getline(file, line))
    {
        vector<Node> row;
        for (int x = 0; x < line.size(); ++x)
        {
            row.emplace_back(line[x] == '#', Vector2(x, y));
            if (line[x] == 'S')
            {
                startLocation = Vector2(x, y);
            }
        }
        map.push_back(row);
        y++;
    }

    int mapWidth = static_cast<int>(map[0].size());
    int mapHeight = static_cast<int>(map.size());
    int64_t sum = 0;

    queue<pair<Node*, int>> nodesToVisit;
    Node* startingNode = &map[startLocation.y][startLocation.x];
    nodesToVisit.emplace(startingNode, 0);
    while (!nodesToVisit.empty())
    {
        Node* currentNode = nodesToVisit.front().first;
        int currentStep = nodesToVisit.front().second;
        if (currentStep <= 64 && currentStep % 2 == 0)
        {
            currentNode->valid = true;
        }
        nodesToVisit.pop();
        vector<Vector2> adjacentPositions = {
            currentNode->position + Vector2::up(),
            currentNode->position + Vector2::down(),
            currentNode->position + Vector2::left(),
            currentNode->position + Vector2::right()
        };
        for (Vector2 adjacentPosition : adjacentPositions)
        {
            if (adjacentPosition.x < 0 || adjacentPosition.x >= mapWidth || adjacentPosition.y < 0 || adjacentPosition.y >= mapHeight)
            {
                continue;
            }
            Node* adjacentNode = &map[adjacentPosition.y][adjacentPosition.x];
            if (adjacentNode->rock)
            {
                continue;
            }
            if (adjacentNode->distance < 0)
            {
                adjacentNode->distance = currentNode->distance + 1;
            }
            else
            {
                adjacentNode->distance = min(adjacentNode->distance, currentNode->distance + 1);
            }
            if (!adjacentNode->visited)
            {
                nodesToVisit.emplace(adjacentNode, currentStep + 1);
                adjacentNode->visited = true;
            }
        }

    }
    
    for (vector<Node>& row : map)
    {
        for (Node& node : row)
        {
            if (node.rock)
            {
                printf("#");
            }
            else
            {
                if (node.valid)
                {
                    printf("O");
                    sum++;
                }
                else
                {
                    printf(".");
                }
            }
        }
        printf("\n");
    }

    return sum;
}


int64_t StepCounter::get2()
{
    bool useExample = true;
    fstream file = useExample ? fstream("Day21/test.txt", ios::in) : fstream("Day21/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    vector<vector<Node>> map;
    Vector2 startLocation = Vector2(0, 0);
    string line;

    int y = 0;
    while (getline(file, line))
    {
        vector<Node> row;
        for (int x = 0; x < line.size(); ++x)
        {
            row.emplace_back(line[x] == '#', Vector2(x, y));
            if (line[x] == 'S')
            {
                startLocation = Vector2(x, y);
            }
        }
        map.push_back(row);
        y++;
    }

    int mapWidth = static_cast<int>(map[0].size());
    int mapHeight = static_cast<int>(map.size());
    int64_t sum = 0;

    queue<pair<Node*, int>> nodesToVisit;
    Node* startingNode = &map[startLocation.y][startLocation.x];
    nodesToVisit.emplace(startingNode, 0);
    while (!nodesToVisit.empty())
    {
        Node* currentNode = nodesToVisit.front().first;
        int currentStep = nodesToVisit.front().second;
        if (currentStep <= 26501365 && currentStep % 2 == 0)
        {
            sum++;
            currentNode->valid = true;
        }
        nodesToVisit.pop();
        vector<Vector2> adjacentPositions = {
            currentNode->position + Vector2::up(),
            currentNode->position + Vector2::down(),
            currentNode->position + Vector2::left(),
            currentNode->position + Vector2::right()
        };
        for (Vector2 adjacentPosition : adjacentPositions)
        {
            Node* adjacentNode = &map[adjacentPosition.y][adjacentPosition.x];
            if (adjacentNode->rock)
            {
                continue;
            }
            if (adjacentNode->distance < 0)
            {
                adjacentNode->distance = currentNode->distance + 1;
            }
            else
            {
                adjacentNode->distance = min(adjacentNode->distance, currentNode->distance + 1);
            }
            if (!adjacentNode->visited)
            {
                nodesToVisit.emplace(adjacentNode, currentStep + 1);
                adjacentNode->visited = true;
            }
        }

    }

    for (vector<Node>& row : map)
    {
        for (Node& node : row)
        {
            if (node.rock)
            {
                printf("#");
            }
            else
            {
                if (node.valid)
                {
                    printf("O");
                }
                else
                {
                    printf(".");
                }
            }
        }
        printf("\n");
    }

    return sum;
}

StepCounter::Node::Node(bool rock, Vector2 position)
    :rock(rock), position(position)
{
}

StepCounter::Node2::Node2(bool rock, Vector2 position)
    :rock(rock), position(position)
{
}
