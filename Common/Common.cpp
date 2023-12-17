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