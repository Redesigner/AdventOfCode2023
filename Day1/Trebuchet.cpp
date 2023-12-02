#include "Trebuchet.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <chrono>


std::vector<std::string> numberStrings = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int Trebuchet::get(bool useWords)
{
	auto startTime = std::chrono::system_clock::now();
	int lineCount = 1;
	std::string fileName = "Day1/input.txt";
	std::fstream file = std::fstream(fileName, std::ios::in);

	if (!file.is_open())
	{
		return 0;
	}

	std::string line;
	int valueThisLine = 0;
	int result = 0;
	while (std::getline(file, line))
	{
		int previousTotal = result;
		valueThisLine = getFirstInteger(line, useWords) * 10 + getLastInteger(line, useWords);
		result += valueThisLine;
		// std::printf("%i\t%s = %i\n", lineCount, line.c_str(), valueThisLine);
		// std::printf("%i\t%i + %i = %i\n", lineCount, previousTotal, valueThisLine, result);
		// std::printf("%i: %i\n", lineCount, valueThisLine);
		lineCount++;
	}
	auto endTime = std::chrono::system_clock::now();
	float delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f;
	// std::printf("Result: %i. Calculations took %.3f ms", result, delta);
	return result;
}

int Trebuchet::matchStringToInt(std::string& string)
{
	for (int i = 0; i < numberStrings.size(); i++)
	{
		if (string.size() < numberStrings[i].size())
		{
			continue;
		}
		if (string.find(numberStrings[i]) == std::string::npos)
		{
			continue;
		}
		return i;
	}
	return -1;
}

int Trebuchet::getFirstInteger(std::string& string, bool useWords)
{
	std::string current;
	for (char c : string)
	{
		int charAsInt = static_cast<int>(c) - 48;
		if (charAsInt >= 0 && charAsInt < 10)
		{
			return charAsInt;
		}
		if (!useWords)
		{
			continue;
		}
		current.push_back(c);
		charAsInt = matchStringToInt(current);
		if (charAsInt >= 0)
		{
			return charAsInt;
		}
	}
	return 0;
}

int Trebuchet::getLastInteger(std::string& string, bool useWords)
{
	std::string current;
	for (int i = static_cast<int>(string.size()) - 1; i >= 0; i--)
	{
		char c = string[i];
		int charAsInt = static_cast<int>(c) - 48;
		if (charAsInt >= 0 && charAsInt < 10)
		{
			return charAsInt;
		}
		if (!useWords)
		{
			continue;
		}
		current = c + current;
		charAsInt = matchStringToInt(current);
		if (charAsInt >= 0)
		{
			return charAsInt;
		}
	}
	return 0;
}