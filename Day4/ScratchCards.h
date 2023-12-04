#pragma once

#include <vector>
#include <string>

namespace ScratchCards
{
	class Card
	{
	public:
		Card(std::string string);

		std::vector<int> winningNumbers;
		std::vector<int> myNumbers;

		int value;

		int number;
	};

	int get();

	int getCards();
}