#include "Fertilizer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <ranges>
#include <vector>

#include "../Common/Common.h"

int64 Fertilizer::get()
{
    std::fstream file = std::fstream("Day5/input.txt", std::ios::in);
    std::string line;

    if (!file.is_open())
    {
        printf("Failed to open file.");
        return -1;
    }

    std::vector<int64> seeds;
    std::vector<std::vector<Range>> maps;

    bool writingMap = false;
    int currentMap = 0;

    while (std::getline(file, line))
    {
        if (!writingMap)
        {
            if (line.starts_with("seeds:"))
            {
                for (std::string value : Common::splitString(line, ' '))
                {
                    if (value.starts_with("s"))
                    {
                        continue;
                    }
                    char* pEnd;
                    seeds.push_back(std::strtoll(value.c_str(), &pEnd, 10));
                }
                continue;
            }
            int charAsInt = static_cast<int>(line[0]) - 48;
            if (charAsInt >= 0 && charAsInt < 10)
            {
                writingMap = true;
                std::vector<std::string> values = Common::splitString(line, ' ');
                maps.push_back(std::vector<Range>({ Range(values) }));
            }
            continue;
        }
        if (line.size() <= 1)
        {
            currentMap++;
            writingMap = false;
            continue;
        }
        maps[currentMap].emplace_back(Common::splitString(line, ' '));
    }

    int64 minimum = 9223372036854775807L;
    for (int64& seed : seeds)
    {
        for (int i = 0 ; i < maps.size(); ++i)
        {
            bool mapped = false;
            const std::vector<Range>& map = maps[i];
            for (const Range& range : map)
            {
                if (mapped)
                {
                    continue;
                }
                if (range.inSourceRange(seed))
                {
                    seed = range.map(seed);
                    // printf("ExpandingMap %i: mapping seed to %i\n", i, seed);
                    mapped = true;
                }
            }
        }
        if (seed < minimum)
        {
            minimum = seed;
        }
        // printf("%i\n", seed);
    }
    return minimum;
}

int64 Fertilizer::getRange()
{
    std::fstream file = std::fstream("Day5/input.txt", std::ios::in);
    std::string line;

    if (!file.is_open())
    {
        printf("Failed to open file.");
        return -1;
    }

    std::vector<SeedRange> seeds;
    std::vector<std::vector<Range>> maps;

    bool writingMap = false;
    int currentMap = 0;

    while (std::getline(file, line))
    {
        if (!writingMap)
        {
            if (line.starts_with("seeds:"))
            {
                std::vector<std::string> values = Common::splitString(line, ' ');
                for (int i = 1; i < values.size(); i += 2)
                {
                    char* pEnd;
                    int64 start = std::strtoll(values[i].c_str(), &pEnd, 10);
                    int64 end = std::strtoll(values[i + 1].c_str(), &pEnd, 10);
                    seeds.emplace_back(start, start + end - 1);
                }
                continue;
            }
            int charAsInt = static_cast<int>(line[0]) - 48;
            if (charAsInt >= 0 && charAsInt < 10)
            {
                writingMap = true;
                std::vector<std::string> values = Common::splitString(line, ' ');
                maps.push_back(std::vector<Range>({ Range(values) }));
            }
            continue;
        }
        if (line.size() <= 1)
        {
            currentMap++;
            writingMap = false;
            continue;
        }
        maps[currentMap].emplace_back(Common::splitString(line, ' '));
    }

    printf("Performing reverse lookup of seed tables. This may take a few seconds...\n");
    int64 max = 9223372036854775807L;
    for (int64 seed = 0; seed < max; ++seed)
    {
        int64 mappedSeed = seed;
        for (int i = maps.size() - 1; i >= 0; --i)
        {
            bool mapped = false;
            const std::vector<Range>& map = maps[i];
            for (const Range& range : map)
            {
                if (mapped)
                {
                    continue;
                }
                if (range.inOutputRange(mappedSeed))
                {
                    mappedSeed = range.reverseMap(mappedSeed);
                    mapped = true;
                }
            }
        }
        for (SeedRange& seedRange : seeds)
        {
            if (seedRange.inRange(mappedSeed))
            {
                return seed;
            }
        }
        // printf("%lld\n", seed);
    }
    return -1;
}


Fertilizer::Range::Range(const std::vector<std::string>& values)
{
    char* pEnd;
    int64 destinationStart = std::strtoll(values[0].c_str(), &pEnd, 10);
    sourceStart = std::strtoll(values[1].c_str(), &pEnd, 10);
    int64 rangeLength = std::strtoll(values[2].c_str(), &pEnd, 10);

    sourceEnd = sourceStart + rangeLength - 1;
    offset = destinationStart - sourceStart;
    outputStart = sourceStart + offset;
    outputEnd = sourceEnd + offset;
}

bool Fertilizer::Range::inSourceRange(int64 value) const
{
    return value >= sourceStart && value <= sourceEnd;
}

int64 Fertilizer::Range::map(int64 value) const
{
    return value + offset;
}

bool Fertilizer::Range::inOutputRange(int64 value) const
{
    return value >= outputStart && value <= outputEnd;
}

int64 Fertilizer::Range::reverseMap(int64 value) const
{
    return value - offset;
}

Fertilizer::SeedRange::SeedRange(int64 start, int64 end)
    :start(start), end(end)
{
}

bool Fertilizer::SeedRange::inRange(int64 value) const
{
    return value >= start && value < end;
}
