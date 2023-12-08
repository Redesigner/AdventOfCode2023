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