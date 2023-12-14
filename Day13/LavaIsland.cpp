#include "LavaIsland.h"

#include <fstream>

#include "../Common/Common.h"

using namespace std;

int64_t LavaIsland::get()
{
	fstream file = fstream("Day13/input.txt", ios::in);
	// fstream file = fstream("Day13/test.txt", ios::in);

	if (!file.is_open())
	{
		return -1;
	}

	vector<Map> maps;

	string line;
	vector<string> mapString;
	while (getline(file, line))
	{
		if (line.empty())
		{
			maps.emplace_back(mapString);
			mapString.clear();
			continue;
		}
		mapString.push_back(line);
	}
	maps.emplace_back(mapString);

	int64_t sum = 0;
	for (Map& map : maps)
	{
		int value = map.getValue();
		printf("%i\n", value);
		sum += value;
	}
	return sum;
}

int64_t LavaIsland::get2()
{
	fstream file = fstream("Day13/input.txt", ios::in);
	// fstream file = fstream("Day13/test.txt", ios::in);

	if (!file.is_open())
	{
		return -1;
	}

	vector<Map> maps;

	string line;
	vector<string> mapString;
	while (getline(file, line))
	{
		if (line.empty())
		{
			maps.emplace_back(mapString);
			mapString.clear();
			continue;
		}
		mapString.push_back(line);
	}
	maps.emplace_back(mapString);

	int64_t sum = 0;
	for (Map& map : maps)
	{
		map.getValue();
		int value = map.getSmudgedValue();
		printf("%i\n", value);
		sum += value;
	}
	return sum;
}

LavaIsland::Map::Map(vector<string> lines)
{
	for (const string& line : lines)
	{
		std::vector<bool> data;
		for (const char& c : line)
		{
			data.push_back(c == '#');
		}
		map.push_back(data);
	}
	reflectionX = -1;
	reflectionY = -1;
}

string LavaIsland::Map::toString() const
{
	string result;
	for (const vector<bool>& dataLine : map)
	{
		for (bool data : dataLine)
		{
			result.push_back(data ? '#' : '.');
		}
		result.push_back('\n');
	}
	return result;
}

bool LavaIsland::Map::findXReflection()
{
	int width = map[0].size();
	for (int i = 0; i < width - 1; ++i)
	{
		if (i == reflectionX)
		{
			continue;
		}
		if (validXReflection(i))
		{
			reflectionX = i;
			return true;
		}
	}
	return false;
}

bool LavaIsland::Map::findYReflection()
{
	int height = map.size();
	for (int i = 0; i < height - 1; ++i)
	{
		if (i == reflectionY)
		{
			continue;
		}
		if (validYReflection(i))
		{
			reflectionY = i;
			return true;
		}
	}
	return false;
}

bool LavaIsland::Map::validXReflection(int x) const
{
	int left = x;
	int right = x + 1;

	while (true)
	{
		if (left < 0)
		{
			return true;
		}
		if (right >= map[0].size())
		{
			return true;
		}
		if (getColumn(left) != getColumn(right))
		{
			return false;
		}
		left--;
		right++;
	}
}

bool LavaIsland::Map::validYReflection(int y) const
{
	int top = y;
	int bottom = y + 1;

	while (true)
	{
		if (top < 0)
		{
			return true;
		}
		if (bottom >= map.size())
		{
			return true;
		}
		if (map[top] != map[bottom])
		{
			return false;
		}
		top--;
		bottom++;
	}
}

vector<bool> LavaIsland::Map::getColumn(int x) const
{
	vector<bool> result;

	for (const vector<bool>& data : map)
	{
		result.push_back(data[x]);
	}
	return result;
}

int LavaIsland::Map::getValue()
{
	findXReflection();
	if (reflectionX == -1)
	{
		findYReflection();
		return (reflectionY + 1) * 100;
	}
	else
	{
		return reflectionX + 1;
	}
}

int LavaIsland::Map::getSmudgedValue()
{
	for (int y = 0; y < map.size(); ++y)
	{
		vector<bool>& currentLine = map[y];
		for (int x = 0; x < currentLine.size(); ++x)
		{
			currentLine[x] = !currentLine[x];

			if (findXReflection())
			{
				printf("Found smudge at (%i, %i)\n", x, y);
				return reflectionX + 1;
			}
			if (findYReflection())
			{
				printf("Found smudge at (%i, %i)\n", x, y);
				return (reflectionY + 1) * 100;
			}
			currentLine[x] = !currentLine[x];
		}
	}
	return -1;
}
