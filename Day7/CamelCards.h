#pragma once

#include <string>
#include <vector>

namespace CamelCards
{
	struct Card
	{
		Card(char c);

		bool operator >(const Card& otherCard) const;
		bool operator ==(const Card& otherCard) const;
		bool operator <(const Card& otherCard) const;

		int value;
	};

	struct Hand
	{
		Hand(const std::string& string, int value);

		Card get(size_t index) const;

		size_t getSize() const;

		bool operator >(const Hand& otherHand) const;
		bool operator ==(const Hand& otherHand) const;
		bool operator <(const Hand& otherHand) const;

		std::string toString() const;

		std::vector<Card> cards;
		int value;
		int type;
	};

	int get();
}