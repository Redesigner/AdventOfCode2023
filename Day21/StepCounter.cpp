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
    bool useExample = false;
    fstream file = useExample ? fstream("Day21/test.txt", ios::in) : fstream("Day21/input.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    vector<vector<Node>> mapOriginal;
    Vector2 startLocation = Vector2(0, 0);
    string line;

    int y = 0;
    while (getline(file, line))
    {
        string copy = line;
        line.append(copy);
        line.append(copy);
        line.append(copy);
        line.append(copy);

        vector<Node> row;
        for (int x = 0; x < line.size(); ++x)
        {
            row.emplace_back(line[x] == '#', Vector2(x, y));
            if (line[x] == 'S')
            {
                // startLocation = Vector2(x, y);
            }
        }
        mapOriginal.push_back(row);
        y++;
    }

    int mapWidth = static_cast<int>(mapOriginal[0].size());
    int mapHeight = static_cast<int>(mapOriginal.size());

    startLocation = Vector2((mapWidth - 1) / 2, (mapHeight - 1) / 2);

    // int64_t fullDistance = 26501365;
    int64_t fullDistance = 500;

    // int numMapsRight = 
    for (int i = 65; i <= mapWidth; i += 131)
    {
        printf("(%i, %lld),\n", i, getPossiblePositions(&mapOriginal, startLocation, i));
        // printf("%lld\n", getPossiblePositions(&mapOriginal, startLocation, i));
    }
    // ========================= NOTES: ====================================
    // I plugged the answers from above into wolfram alpha... I will come up with a better solution... tomorrow :)
    return 0;
}

StepCounter::Node::Node(bool rock, Vector2 position)
    :rock(rock), position(position)
{
}

int64_t StepCounter::getPossiblePositions(std::vector<std::vector<Node>>* baseMap, Vector2 startLocation, int maxSteps)
{
    int mapWidth = baseMap[0].size();
    int mapHeight = baseMap->size();
    if (maxSteps >= mapHeight + mapWidth)
    {
        maxSteps = (mapHeight + mapWidth) + maxSteps % 2;
    }
    auto inputTuple = make_tuple(baseMap, startLocation, maxSteps);
    if (getPossiblePositionsCache.contains(inputTuple))
    {
        return getPossiblePositionsCache[inputTuple];
    }
    vector<vector<Node>> nodeMap = *baseMap;
    queue<pair<Node*, int>> nodesToVisit;

    Node* startingNode = &nodeMap[startLocation.y][startLocation.x];
    nodesToVisit.emplace(startingNode, 0);
    while (!nodesToVisit.empty())
    {
        Node* currentNode = nodesToVisit.front().first;
        int currentStep = nodesToVisit.front().second;
        if (currentStep <= maxSteps && currentStep % 2 == maxSteps % 2)
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
            Node* adjacentNode = &nodeMap[adjacentPosition.y][adjacentPosition.x];
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
    int64_t sum = 0;
    for (vector<Node>& row : nodeMap)
    {
        for (Node& node : row)
        {
            if (node.rock)
            {
                // printf("#");
            }
            else
            {
                if (node.valid)
                {
                    // printf("O");
                    sum++;
                }
                else
                {
                    // printf(".");
                }
            }
        }
        // printf("\n");
    }
    getPossiblePositionsCache.emplace(inputTuple, sum);
    // printf("Possible positions in %i steps: %lld \n\n", maxSteps, sum);
    return sum;
}