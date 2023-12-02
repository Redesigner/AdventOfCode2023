#include <iostream>

#include "Day1/Trebuchet.h"
#include "Day2/CubeConundrum.h"

int main()
{
	std::printf("Welcome to the Advent of Code!\nPlease enter a number to see the solution for that day! (1 - 25)\n");

	int chosenDay = 0;
	while (chosenDay >= 0)
	{
		std::cin >> chosenDay;

		if (chosenDay >= 25 || chosenDay <= 0)
		{
			return 0;
		}

		switch (chosenDay)
		{
		case 1:
		{
			std::printf("Sum of first calibration values: %i\n", Trebuchet::get(false));
			std::printf("Sum of second calibration values: %i\n", Trebuchet::get(true));
		}break;
		case 2:
		{
			std::printf("Total IDs: %i\n", CubeConundrum::get_total_ids());
			std::printf("Power sum: %i\n", CubeConundrum::get_powers());
		}break;
		default:
		{
			std::printf("That day isn't available yet! Check back later.\n");
		}break;
		}
	}
	return 0;
}