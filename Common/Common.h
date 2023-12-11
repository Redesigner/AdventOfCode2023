#pragma once

#include <vector>
#include <string>

namespace Common
{
	std::vector<std::string> splitString(const std::string string, char delimiter);
}

struct Vector2
{
	int x;
	int y;

	const bool operator==(const Vector2& otherVector) const;
	Vector2 operator+(const Vector2& otherVector) const;
	Vector2 operator-(const Vector2& otherVector) const;
};