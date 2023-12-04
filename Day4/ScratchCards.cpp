#include "ScratchCards.h"

#include <string_view>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "../Common/Common.h"

int ScratchCards::get()
{
    std::fstream file = std::fstream("Day4/input.txt", std::ios_base::in);
    std::string line;

    if (!file.is_open())
    {
        std::printf("Failed to open file.\n");
        return -1;
    }

    std::vector<Card> cards;

    int total = 0;
    while (std::getline(file, line))
    {
        cards.push_back(Card(line));
    }
    for (const Card& card : cards)
    {
        if (card.value == 0)
        {
            continue;
        }
        total += std::pow(2, card.value - 1);
    }
    return total;
}

int ScratchCards::getCards()
{
    std::fstream file = std::fstream("Day4/input.txt", std::ios_base::in);
    std::string line;

    if (!file.is_open())
    {
        std::printf("Failed to open file.\n");
        return -1;
    }

    std::vector<Card> cards;

    while (std::getline(file, line))
    {
        cards.push_back(Card(line));
    }
    for (int i = 0; i < cards.size(); ++i)
    {
        Card& card = cards[i];
        for (int j = 1; j <= card.value; ++j)
        {
            cards[i + j].number += card.number;
        }
    }
    int total = 0;
    for (int i = 0; i < cards.size(); ++i)
    {
        const Card& card = cards[i];
        // printf("'Card %i': %i copies\n", i + 1, card.number);
        total += card.number;
    }
    return total;
}

ScratchCards::Card::Card(std::string line)
{
    number = 1;
    value = 0;

    size_t valueStart = line.find(':');
    // strip out the index and newline char
    std::string cardString = line.substr(valueStart + 1, line.size() - valueStart - 1);
    std::vector<std::string> cards = Common::splitString(cardString, '|');

    std::vector<int> winningNumbers;

    for (std::string numberAsString : Common::splitString(cards[0], ' '))
    {
        int number = std::atoi(numberAsString.c_str());
        if (number <= 0)
        {
            continue;
        }
        winningNumbers.push_back(number);
    }
    std::vector<int> myNumbers;
    for (std::string numberAsString : Common::splitString(cards[1], ' '))
    {
        int number = std::atoi(numberAsString.c_str());
        if (number <= 0)
        {
            continue;
        }
        myNumbers.push_back(number);
    }

    for (int winningNumber : winningNumbers)
    {
        for (int myNumber : myNumbers)
        {
            if (myNumber != winningNumber)
            {
                continue;
            }
            value++;
        }
    }
}
