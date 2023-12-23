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

bool Vector2::operator<(const Vector2& otherVector) const
{
    return lengthSquared() < otherVector.lengthSquared();
}

bool Vector2::operator>(const Vector2& otherVector) const
{
    return lengthSquared() > otherVector.lengthSquared();
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

int Vector2::lengthSquared() const
{
    return x * x + y * y;
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

int64_t Common::GCD(const int& a, const int& b)
{
    int64_t r02 = a;
    int64_t r01 = b;
    while (true)
    {
        int64_t remainder = r02 % r01;
        if (remainder == 0)
        {
            return r01;
        }
        r02 = r01;
        r01 = remainder;
    }
}

int64_t Common::GCD(const std::vector<int>& values)
{
    if (values.size() <= 2)
    {
        return 0;
    }
    int64_t currentGCD = values[0];
    for (const int value : values)
    {
        currentGCD = GCD(currentGCD, value);
    }
    return currentGCD;
}

int64_t Common::LCM(const std::vector<int>& values)
{
    int64_t valuesGCD = GCD(values);
    int64_t result = 1;
    for (int64_t value : values)
    {
        int64_t factor = value / valuesGCD;
        result *= factor;
    }
    return result * valuesGCD;
}

int Common::mod(int k, int n)
{
    return ((k %= n) < 0) ? k + n : k;
}

Range::Range(int start, int end)
    :start(start), end(end)
{
}

Range::Range()
{
    start = 0;
    end = 0;
}

std::vector<Range> Range::split(int separator) const
{
    if (!inside(separator))
    {
        return { Range(start, end) };
    }
    return { Range(start, separator), Range(separator + 1, end) };
}

std::vector<int> Range::valuesInRange() const
{
    std::vector<int> result;
    for (int i = start; i <= end; ++i)
    {
        result.emplace_back(i);
    }
    return result;
}

bool Range::inside(int value) const
{
    return value >= start && value <= end;
}

int Range::width() const
{
    return end - start + 1;
}