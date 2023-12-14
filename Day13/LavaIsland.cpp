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

	vector<vector<string>> maps;

	string line;
	vector<string> map;
	while (getline(file, line))
	{
		if (line.empty())
		{
			maps.push_back(map);
			map.clear();
			continue;
		}
		map.push_back(line);
	}
	maps.push_back(map);

	int64_t sum = 0;
	for (const vector<string>& reflectionMap : maps)
	{
		int value = getMirroredX(reflectionMap);
		if (value == 0)
		{
			value = getMirroredY(reflectionMap) * 100;
		}
		sum += value;
		printf("%i\n", value);
	}
	return sum;
}

int64_t LavaIsland::get2()
{
	// fstream file = fstream("Day13/input.txt", ios::in);
	fstream file = fstream("Day13/test.txt", ios::in);

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

	for (Map& map : maps)
	{
	}
	return -1;
}

std::string LavaIsland::getColumn(const vector<string>& map, int x)
{
	string columnResult;
	for (const string& row : map)
	{
		columnResult.push_back(row[x]);
	}
	return columnResult;
}

bool LavaIsland::mirrorsColumns(const std::vector<std::string>& map, int x)
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
		if (getColumn(map, left) != getColumn(map, right))
		{
			return false;
		}
		left--;
		right++;
	}
}

int LavaIsland::getMirroredX(const std::vector<std::string>& map)
{
	int width = map[0].size();
	for (int i = 0; i < width - 1; ++i)
	{
		if (mirrorsColumns(map, i))
		{
			return i + 1;
		}
	}
	return 0;
}


bool LavaIsland::mirrorsRows(const std::vector<std::string>& map, int y)
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

int LavaIsland::getMirroredY(const std::vector<std::string>& map)
{
	int height = map.size();
	for (int i = 0; i < height - 1; ++i)
	{
		if (mirrorsRows(map, i))
		{
			return i + 1;
		}
	}
	return 0;
}

void LavaIsland::remap(pair<vector<string>, int>& mapValue)
{
	vector<string>& map = mapValue.first;
	const int oldValue = mapValue.second;

	for (int y = 0; y < map.size(); ++y)
	{
		string& row = map[y];
		for (int x = 0; x < row.size(); ++x)
		{
			char& c = row[x];
			c = c == '.' ? '#' : '.';

			/*bool containsOldReflection = false;
			if (oldValue > 100)
			{
				int previousReflectionY = oldValue / 100 - 1;
				containsOldReflection = mirrorsRows(map, previousReflectionY);
			}
			else
			{
				int previousReflectionX = oldValue - 1;
				containsOldReflection = mirrorsColumns(map, previousReflectionX);
			}
			if (containsOldReflection)
			{
				c = c == '.' ? '#' : '.';
				continue;
			} */
			int mirroredX = getMirroredX(map);
			if (mirroredX != 0 && mirroredX != oldValue)
			{
				printf("Smudge found at (%i, %i)\n", x + 1, y + 1);
				mapValue.second = mirroredX;
				return;
			}
			int mirroredY = getMirroredY(map);
			if (mirroredY != 0 && mirroredY * 100 != oldValue)
			{
				printf("Smudge found at (%i, %i)\n", x + 1, y + 1);
				mapValue.second = mirroredY * 100;
				return;
			}
			c = c == '.' ? '#' : '.';
		}
	}
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

void LavaIsland::Map::findXReflection()
{
}

void LavaIsland::Map::findYReflection()
{
}

bool LavaIsland::Map::validXReflection(int x) const
{
	return false;
}

bool LavaIsland::Map::validYReflection(int y) const
{
	return false;
}

std::vector<bool> LavaIsland::Map::getColumn(int x) const
{
	return std::vector<bool>();
}
