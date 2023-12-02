#include "CubeConundrum.h"

#include "fstream"
#include "format"

int CubeConundrum::get_total_ids()
{
	CubeBag referenceBag = CubeBag(12, 13, 14);

	std::fstream file = std::fstream("Day2/input.txt", std::ios::in);
	std::string line;

	if (!file.is_open())
	{
		printf("Failed to open file.");
		return -1;
	}

	int i = 0;
	int total = 0;
	while (std::getline(file, line))
	{
		i++;
		if (isGameValid(getCubeBagsFromString(line), referenceBag))
		{
			total += i;
			// printf("Game %i was valid.\n", i);
		}
		else
		{
			// printf("Game %i was invalid.\n", i);
		}
	}
	return total;
}

int CubeConundrum::get_powers()
{
	int sum = 0;
	std::fstream file = std::fstream("Day2/input.txt", std::ios::in);
	std::string line;

	while (std::getline(file, line))
	{
		CubeBag minimum = getMinimumSize(getCubeBagsFromString(line));
		sum += minimum.red * minimum.blue * minimum.green;
	}
	return sum;
}

std::vector<CubeConundrum::CubeBag> CubeConundrum::getCubeBagsFromString(std::string& string)
{
	std::vector<CubeBag> result = std::vector<CubeBag>();

	bool endOfString = false;
	std::size_t startIndex = string.find(':');
	while (!endOfString)
	{
		std::size_t endIndex = string.find(';', startIndex);
		if (endIndex == std::string::npos)
		{
			endIndex = string.size() - 1;
			endOfString = true;
		}
		std::string currentBagString = string.substr(startIndex, endIndex - startIndex);

		result.push_back(getCubeBagFromString(currentBagString));
		startIndex = endIndex + 1;
	}
	return result;
}

CubeConundrum::CubeBag CubeConundrum::getCubeBagFromString(std::string& string)
{
	size_t startingIndex = 0;

	CubeBag result = CubeBag(0, 0, 0);

	while (startingIndex != std::string::npos)
	{
		size_t intBegin = string.find(' ', startingIndex) + 1;
		size_t intEnd = string.find(' ', intBegin);
		std::string integerString = string.substr(intBegin, intEnd - intBegin);

		int value = std::atoi(integerString.c_str());

		char colorFirstChar = string.at(intEnd + 1);
		switch (colorFirstChar)
		{
		case 'b':
		{
			result.blue = value;
		}break;
		case 'r':
		{
			result.red = value;
		}break;
		case 'g':
		{
			result.green = value;
		}break;
		}

		startingIndex = string.find(',', startingIndex + 1);
	}
	return result;
}

bool CubeConundrum::isGameValid(const std::vector<CubeBag>& bags, CubeBag& referenceBag)
{
	for (const CubeBag& cubeBag : bags)
	{
		if (!(cubeBag <= referenceBag))
		{
			return false;
		}
	}
	return true;
}

CubeConundrum::CubeBag CubeConundrum::getMinimumSize(const std::vector<CubeBag>& bags)
{
	CubeBag result = CubeBag(0, 0, 0);

	for (const CubeBag& cubeBag : bags)
	{
		result.red = std::max(result.red, cubeBag.red);
		result.green = std::max(result.green, cubeBag.green);
		result.blue = std::max(result.blue, cubeBag.blue);
	}

	return result;
}

bool CubeConundrum::CubeBag::operator<=(CubeBag& otherBag) const
{
	return red <= otherBag.red && green <= otherBag.green && blue <= otherBag.blue;
}
