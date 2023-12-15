#include "LensLibrary.h"

#include <fstream>
#include <string>
#include <vector>

#include "../Common/Common.h"

using namespace std;

int64_t LensLibrary::get()
{
    fstream file("Day15/input.txt", ios::in);
    // fstream file("Day15/test.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }

    string sequence;
    getline(file, sequence);

    int64_t sum = 0;
    for (string value : Common::splitString(sequence, ','))
    {
        sum += hash(value);
    }
    return sum;
}

int64_t LensLibrary::get2()
{
    fstream file("Day15/input.txt", ios::in);
    // fstream file("Day15/test.txt", ios::in);

    if (!file.is_open())
    {
        return -1;
    }
    string sequence;
    getline(file, sequence);

    for (string value : Common::splitString(sequence, ','))
    {
        hash(value);
    }

    string sequence;
    getline(file, sequence);

}

int64_t LensLibrary::hash(const std::string& value)
{
    int64_t result = 0;
    for (char c : value)
    {
        result += c;
        result *= 17;
        result = result % 256;
    }
    return result;
}
