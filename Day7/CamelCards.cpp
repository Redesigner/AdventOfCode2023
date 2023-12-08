#include "CamelCards.h"

#include <fstream>
#include <algorithm>

#include "../Common/Common.h"

// std::vector<char> cardValues = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
std::vector<char> cardValues = { 'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A' };

std::vector<std::string> rankNames = { "Junk", "One pair", "Two pair", "Three of a kind", "Full house", "Four of a kind", "Five of a kind", "x"};


CamelCards::Card::Card(char c)
{
	for (int i = 0; i < cardValues.size(); ++i)
	{
		if (c == cardValues[i])
		{
			value = i + 2;
			return;
		}
	}
	value = 0;
}

bool CamelCards::Card::operator>(const Card& otherCard) const
{
	return value > otherCard.value;
}

bool CamelCards::Card::operator==(const Card& otherCard) const
{
	return value == otherCard.value;
}

bool CamelCards::Card::operator<(const Card& otherCard) const
{
	return value < otherCard.value;
}


int CamelCards::get()
{
	std::fstream file = std::fstream("Day7/input.txt", std::ios::in);
	std::string line;

	if (!file.is_open())
	{
		return -1;
	}
	
	std::vector<Hand> hands;

	while (std::getline(file, line))
	{
		auto strings = Common::splitString(line, ' ');
		hands.emplace_back(strings[0], atoi(strings[1].c_str()));
	}
	std::sort(hands.begin(), hands.end());

	int value = 0;
	for (int i = 0; i < hands.size(); ++i)
	{
		printf("Hand '%s' value %i, %i \t%s\n", hands[i].toString().c_str(), hands[i].value, i, rankNames[hands[i].type].c_str());
		value += hands[i].value * (i + 1);
	}
	return value;
}


CamelCards::Hand::Hand(const std::string& string, int value)
	:value(value)
{
	type = 0;
	for (char c : string)
	{
		cards.emplace_back(c);
	}
	std::vector cardsCopy = cards;
	std::sort(cardsCopy.begin(), cardsCopy.end());

	std::vector<int> foundValues;
	int selectedValueCount = 0;

	int jokerCount = 0;

	int selectedValue = cardsCopy[0].value;
	if (cardsCopy[0] == Card('J'))
	{
		jokerCount = 1;
	}
	for (int i = 1; i < cardsCopy.size(); ++i)
	{
		const Card& card = cardsCopy[i];
		if (card == Card('J')) // is joker
		{
			jokerCount++;
			continue;
		}
		if (card.value == selectedValue)
		{
			selectedValueCount++;
			continue;
		}
		foundValues.push_back(selectedValueCount);
		selectedValueCount = 0;
		selectedValue = card.value;
	}
	foundValues.push_back(selectedValueCount);
	std::sort(foundValues.begin(), foundValues.end());
	foundValues[foundValues.size() - 1] += jokerCount;
	if (jokerCount == 5)
	{
		type = 6;
		return;
	}
	if (foundValues.size() == 2)
	{
		// full house
		if (foundValues[0] == 1 || foundValues[0] == 2)
		{
			type = 4;
			return;
		}
	}
	if (foundValues.size() == 3)
	{
		// two pair
		if (foundValues[0] == 1 || foundValues[1] == 1 || foundValues[2] == 1)
		{
			if (jokerCount == 1)
			{
				type = 4;
				return;
			}
			type = 2;
			return;
		}
	}

	// find how many of the card we have the most number of
	for (int value : foundValues)
	{
		type = std::max(type, value);
	}
	if (type >= 3)
	{
		type += 2;
		return;
	}
	if (type == 2)
	{
		type++;
	}
}

CamelCards::Card CamelCards::Hand::get(size_t index) const
{
	return cards[index];
}

size_t CamelCards::Hand::getSize() const
{
	return cards.size();
}

bool CamelCards::Hand::operator>(const Hand& otherHand) const
{
	if (type != otherHand.type)
	{
		return type > otherHand.type;
	}
	for (int i = 0; i < cards.size(); ++i)
	{
		if (cards[i] == otherHand.get(i))
		{
			continue;
		}
		return cards[i] > otherHand.get(i);
	}
}

bool CamelCards::Hand::operator==(const Hand& otherHand) const
{
	if (type != otherHand.type)
	{
		return false;
	}
	for (int i = 0; i < cards.size(); ++i)
	{
		if (cards[i] == otherHand.get(i))
		{
			continue;
		}
		return false;
	}
	return true;
}

bool CamelCards::Hand::operator<(const Hand& otherHand) const
{
	if (type != otherHand.type)
	{
		return type < otherHand.type;
	}
	for (int i = 0 ; i < cards.size(); ++i)
	{
		if (cards[i] == otherHand.get(i))
		{
			continue;
		}
		return cards[i] < otherHand.get(i);
	}
}

std::string CamelCards::Hand::toString() const
{
	std::string result;
	for (const Card& card : cards)
	{
		result.push_back(cardValues[card.value - 2]);
	}
	return result;
}
