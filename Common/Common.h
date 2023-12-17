#pragma once

#include <vector>
#include <string>

namespace Common
{
	std::vector<std::string> splitString(const std::string string, char delimiter);

	bool stringContains(const std::string& string, char c);
	bool stringContains(std::string_view string, char c);
}

struct Vector2
{
	int x;
	int y;

	bool insideBounds(int width, int height) const;

	const bool operator==(const Vector2& otherVector) const;
	Vector2 operator+(const Vector2& otherVector) const;
	Vector2 operator-(const Vector2& otherVector) const;
};