#include "LensLibrary.h"

#include <fstream>

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
    vector<vector<Lens>> boxes;
    for (int i = 0; i < 256; ++i)
    {
        boxes.emplace_back();
    }
    string sequence;
    getline(file, sequence);

    for (string value : Common::splitString(sequence, ','))
    {
        Lens lens = Lens(value);
        if (lens.controlChar == '-')
        {
            removeLens(boxes, lens.label, hash(lens.label));
        }
        else
        {
            insertUniqueLens(boxes, lens, hash(lens.label));
        }
    }

    int64_t sum = 0;

    for (int i = 0; i < boxes.size(); ++i)
    {
        const vector<Lens>& box = boxes[i];
        for (int j = 0; j < box.size(); ++j)
        {
            sum += (i + 1) * (j + 1) * box[j].focalLength;
        }
    }
    return sum;
}

int64_t LensLibrary::hash(const string& value)
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

void LensLibrary::removeLens(vector<vector<Lens>>& map, const string& label, int position)
{
    vector<Lens>& lenses = map[position];

    for (int i = 0; i < lenses.size(); ++i)
    {
        if (lenses[i].label == label)
        {
            lenses.erase(lenses.begin() + i);
            return;
        }
    }
}

void LensLibrary::insertUniqueLens(vector<vector<Lens>>& map, const Lens& lens, int position)
{
    vector<Lens>& lenses = map[position];

    for (int i = 0; i < lenses.size(); ++i)
    {
        if (lenses[i].label == lens.label)
        {
            lenses[i].focalLength = lens.focalLength;
            return;
        }
    }
    lenses.emplace_back(lens);
}

LensLibrary::Lens::Lens(const string& input)
{
    
    if (input[input.size() - 1] == '-')
    {
        label = input.substr(0, input.size() - 1);
        controlChar = '-';
        focalLength = 0;
        return;
    }
    label = input.substr(0, input.size() - 2);
    focalLength = input[input.size() - 1] - 48;
    controlChar = '=';
}
