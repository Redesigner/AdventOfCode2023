#include "Common.h"

std::vector<std::string> Common::splitString(const std::string string, char delimiter)
{
    std::vector<std::string> result;

    size_t startIndex = 0;
    size_t endIndex = string.size() - 1;
    size_t delimiterIndex = 0;
    do
    {
        delimiterIndex = string.find(delimiter, startIndex);
        if (delimiterIndex != std::string::npos)
        {
            endIndex = delimiterIndex;
        }
        result.push_back(string.substr(startIndex, endIndex - startIndex));
        startIndex = endIndex + 1;
    } while (delimiterIndex != std::string::npos);
    return result;
}

bool Common::stringContains(const std::string& string, char c)
{
    return string.find(c) != std::string::npos;
}

bool Common::stringContains(std::string_view string, char c)
{
    return string.find(c) != std::string::npos;
}

uint32_t Common::hexStringToInt(std::string_view string)
{
    if (string.size() > 8)
    {
        return 0;
    }
    int result = 0;
    for (int i = 0; i < string.size(); ++i)
    {
        result = result << 4;
        result += charToHex(string[i]);
    }
    return result;
}

char Common::charToHex(char c)
{
    if (c >= 48 && c < 58)
    {
        return c - 48;
    }
    if (c >= 65 && c < 71)
    {
        return c - 55;
    }
    if (c >= 97 && c < 103)
    {
        return c - 87;
    }
    return 0;
}

bool Vector2::insideBounds(int width, int height) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

const bool Vector2::operator==(const Vector2& otherVector) const
{
    return x == otherVector.x && y == otherVector.y;
}

Vector2 Vector2::operator+(const Vector2& otherVector) const
{
    return Vector2(x + otherVector.x, y + otherVector.y);
}

Vector2 Vector2::operator-(const Vector2& otherVector) const
{
    return Vector2(x - otherVector.x, y - otherVector.y);
}

Vector2 Vector2::operator*(const int scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

int64_t Vector2::cross(const Vector2& otherVector) const
{
    return static_cast<int64_t>(x) * static_cast<int64_t>(otherVector.y) - static_cast<int64_t>(y) * static_cast<int64_t>(otherVector.x);
}

Vector2 Vector2::fromDirection(Direction direction)
{
    switch (direction)
    {
    case Up:
        return Vector2(0, -1);
    case Down:
        return Vector2(0, 1);
    case Left:
        return Vector2(-1, 0);
    case Right:
        return Vector2(1, 0);
    default:
        return Vector2(0, 0);
    }
}

Vector2 Vector2::up()
{
    return Vector2(0, -1);
}

Vector2 Vector2::down()
{
    return Vector2(0, 1);
}

Vector2 Vector2::left()
{
    return Vector2(-1, 0);
}

Vector2 Vector2::right()
{
    return Vector2(1, 0);
}
