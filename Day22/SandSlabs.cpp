#include "SandSlabs.h"

#include <fstream>
#include <string>
#include <algorithm>
#include <queue>

#include "../Common/Common.h"

using namespace std;

int64_t SandSlabs::get()
{
    bool useExample = false;
    fstream file = useExample ? fstream("Day22/test.txt", ios::in) : fstream("Day22/input.txt", ios::in);
    if (!file.is_open())
    {
        printf("Failed to open file.\n");
        return -1;
    }
    
    vector<Brick> bricks;
    string line;
    char label = 'A';
    while (getline(file, line))
    {
        vector<string> positions = Common::splitString(line, '~');
        vector<string> positionStrings = Common::splitString(positions[0], ',');
        Vector3 startPosition = Vector3(stoi(positionStrings[0]), stoi(positionStrings[1]), stoi(positionStrings[2]));
        positionStrings = Common::splitString(positions[1], ',');
        Vector3 endPosition = Vector3(stoi(positionStrings[0]), stoi(positionStrings[1]), stoi(positionStrings[2]));
        bricks.emplace_back(startPosition, endPosition, string(1, label));
        label++;
    }
    sort(bricks.begin(), bricks.end(), [](Brick a, Brick b) { return a.origin.z < b.origin.z; });


    int movesLastTick = 1;
    while (movesLastTick > 0)
    {
        movesLastTick = 0;
        for (Brick& brick : bricks)
        {
            if (brick.stable)
            {
                continue;
            }
            if (brick.moveDown(bricks))
            {
                movesLastTick++;
            }
        }
    }

    int sum = 0;
    for (Brick& brick : bricks)
    {
        if (brick.canBeRemoved())
        {
            sum++;
        }
    }
    return sum;
}

int64_t SandSlabs::get2()
{
    bool useExample = false;
    fstream file = useExample ? fstream("Day22/test.txt", ios::in) : fstream("Day22/input.txt", ios::in);
    if (!file.is_open())
    {
        printf("Failed to open file.\n");
        return -1;
    }

    vector<Brick> bricks;
    string line;
    char label = 'A';
    while (getline(file, line))
    {
        vector<string> positions = Common::splitString(line, '~');
        vector<string> positionStrings = Common::splitString(positions[0], ',');
        Vector3 startPosition = Vector3(stoi(positionStrings[0]), stoi(positionStrings[1]), stoi(positionStrings[2]));
        positionStrings = Common::splitString(positions[1], ',');
        Vector3 endPosition = Vector3(stoi(positionStrings[0]), stoi(positionStrings[1]), stoi(positionStrings[2]));
        bricks.emplace_back(startPosition, endPosition, string(1, label));
        label++;
    }
    sort(bricks.begin(), bricks.end(), [](Brick a, Brick b) { return a.origin.z < b.origin.z; });


    int movesLastTick = 1;
    while (movesLastTick > 0)
    {
        movesLastTick = 0;
        for (Brick& brick : bricks)
        {
            if (brick.stable)
            {
                continue;
            }
            if (brick.moveDown(bricks))
            {
                movesLastTick++;
            }
        }
    }

    int sum = 0;
    for (Brick& brick : bricks)
    {
        int bricksDropped = brick.bricksOnlySupport();
        // printf("Brick %s would cause %i blocks to fall\n", brick.label.c_str(), bricksDropped);
        sum += bricksDropped;
    }
    return sum;
}

bool SandSlabs::containsFullSet(const std::vector<Brick*>& source, const std::vector<Brick*>& set)
{
    for (Brick* setBrick : set)
    {
        if (!contains(source, setBrick))
        {
            return false;
        }
    }
    return true;
}

bool SandSlabs::contains(const std::vector<Brick*> source, const Brick* brick)
{
    for (Brick* set : source)
    {
        if (brick == set)
        {
            return true;
        }
    }
    return false;
}

SandSlabs::Vector3::Vector3(int x, int y, int z)
    :x(x), y(y), z(z)
{
}

SandSlabs::Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

bool SandSlabs::Vector3::operator==(const Vector3& otherVector) const
{
    return x == otherVector.x && y == otherVector.y == otherVector.z;
}

SandSlabs::Vector3 SandSlabs::Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

SandSlabs::Vector3 SandSlabs::Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

SandSlabs::Brick::Brick(Vector3 start, Vector3 end, string label)
    :label(label)
{
    origin = start;
    size = end - start + Vector3(1, 1, 1);
}

bool SandSlabs::Brick::overlaps(const Brick& other) const
{
    const Vector3 end = origin + size - Vector3(1, 1, 1);
    const Vector3 otherEnd = other.origin + other.size - Vector3(1, 1, 1);
    return 
        (origin.x <= otherEnd.x && end.x >= other.origin.x) &&
        (origin.y <= otherEnd.y && end.y >= other.origin.y) &&
        (origin.z <= otherEnd.z && end.z >= other.origin.z);
}

bool SandSlabs::Brick::moveDown(std::vector<Brick>& bricks)
{
    if (origin.z == 1)
    {
        stable = true;
        return false;
    }
    origin.z--;
    bool validMove = true;
    for (Brick& brick : bricks)
    {
        if (&brick == this)
        {
            continue;
        }
        if (overlaps(brick))
        {
            validMove = false;
            if (brick.stable)
            {
                brick.bricksSupporting.emplace_back(this);
                supports.emplace_back(&brick);
                // this brick is stable if it's on top of a stable brick
                stable = true;
            }
        }
    }
    if (!validMove)
    {
        origin.z++;
    }
    return validMove;
}

bool SandSlabs::Brick::canBeRemoved() const
{
    for (Brick* supporting : bricksSupporting)
    {
        if (supporting->supports.size() <= 1)
        {
            return false;
        }
    }
    return true;
}

int SandSlabs::Brick::bricksOnlySupport() const
{
    queue<Brick*> bricksChecking;
    for (Brick* supporting : bricksSupporting)
    {
       bricksChecking.emplace(supporting);
    }

    vector<Brick*> bricksDropped;
    int sum = 0;
    while (!bricksChecking.empty())
    {
        Brick* brick = bricksChecking.front();
        bricksChecking.pop();

        if (brick->supports.size() <= 1)
        {
            if (contains(bricksDropped, brick))
            {
                continue;
            }
            bricksDropped.push_back(brick);
            for (Brick* subSupports : brick->bricksSupporting)
            {
                bricksChecking.emplace(subSupports);
            }
            // printf("Brick %s dropped brick %s\n", label.c_str(), brick->label.c_str());
            sum++;
            continue;
        }
        if (containsFullSet(bricksDropped, brick->supports))
        {
            if (contains(bricksDropped, brick))
            {
                continue;
            }
            bricksDropped.push_back(brick);
            for (Brick* subSupports : brick->bricksSupporting)
            {
                bricksChecking.emplace(subSupports);
            }
            // printf("Brick %s dropped brick %s\n", label.c_str(), brick->label.c_str());
            sum++;
        }
    }

    return sum;
}
