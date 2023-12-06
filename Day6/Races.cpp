#include "Races.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int Races::get()
{
    // std::vector<int> times = { 7, 15, 30 };
    // std::vector<int> distances = { 9, 40, 200 };
    std::vector<int> times = { 48, 87, 69, 81 };
    std::vector<int> distances = { 255,1288, 1117, 1623 };

    std::vector<Race> races;

    for (int i = 0; i < times.size(); ++i)
    {
        races.emplace_back(times[i], distances[i]);
    }

    int value = 1;
    for (Race& race : races)
    {
        value *= race.numberRecords();
    }

    return value;
}

int Races::getPart2()
{
    // Race race = Race(71530, 940200);
    Race race = Race(48876981, 255128811171623);
    return race.numberRecords();
}

Races::Race::Race(int time, long long int distance)
    :time(time), record(distance)
{
}

int Races::Race::numberRecords() const
{
    // The answers are just quadratic equations
    long long int timeSquared = static_cast<long long int>(time) * static_cast<long long int>(time);
    double root = sqrt(timeSquared - static_cast<long long int>(4) * (record + 1));
    int maxHoldTime = floor((time + root) / 2);
    int minHoldTime = ceil((time - root) / 2);
    // printf("You must hold the button for at least %i and at most %i seconds\n", minHoldTime, maxHoldTime);
    return maxHoldTime - minHoldTime + 1;
}
