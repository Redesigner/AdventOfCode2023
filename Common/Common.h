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

	int64_t GCD(const int& a, const int& b);
	int64_t GCD(const std::vector<int>& values);
	int64_t LCM(const std::vector<int>& values);

	int mod(int k, int n);
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
	bool operator<(const Vector2& otherVector) const;
	bool operator>(const Vector2& otherVector) const;

	Vector2 operator+(const Vector2& otherVector) const;
	Vector2 operator-(const Vector2& otherVector) const;
	Vector2 operator*(const int scalar) const;

	int64_t cross(const Vector2& otherVector) const;
	int lengthSquared() const;

	static Vector2 fromDirection(Direction direction);
	static Vector2 up();
	static Vector2 down();
	static Vector2 left();
	static Vector2 right();
};

struct Range
{
	Range(int start, int end);
	Range();

	std::vector<Range> split(int separator) const;
	std::vector<int> valuesInRange() const;
	bool inside(int value) const;
	int width() const;

	int start = 0;
	int end = 0;
};