#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace Common
{
	std::vector<std::string> splitString(const std::string string, char delimiter);

	bool stringContains(const std::string& string, char c);
	bool stringContains(std::string_view string, char c);

	uint32_t hexStringToInt(std::string_view string);
	char charToHex(char c);
}

enum Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

struct Vector2
{
	int x;
	int y;

	bool insideBounds(int width, int height) const;

	const bool operator==(const Vector2& otherVector) const;
	Vector2 operator+(const Vector2& otherVector) const;
	Vector2 operator-(const Vector2& otherVector) const;
	Vector2 operator*(const int scalar) const;
	int64_t cross(const Vector2& otherVector) const;

	static Vector2 fromDirection(Direction direction);
	static Vector2 up();
	static Vector2 down();
	static Vector2 left();
	static Vector2 right();
};