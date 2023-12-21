#include <iostream>

#include "Day1/Trebuchet.h"
#include "Day2/CubeConundrum.h"
#include "Day3/GearRatios.h"
#include "Day4/ScratchCards.h"
#include "Day5/Fertilizer.h"
#include "Day6/Races.h"
#include "Day7/CamelCards.h"
#include "Day8/HauntedWasteland.h"
#include "Day9/MirageMaintenance.h"
#include "Day10/PipeMaze.h"
#include "Day11/CosmicExpansion.h"
#include "Day12/HotSprings.h"
#include "Day13/LavaIsland.h"
#include "Day14/ParabolicReflector.h"
#include "Day15/LensLibrary.h"
#include "Day16/FloorLava.h"
#include "Day17/ClumsyCrucible.h"
#include "Day18/LavaductLagoon.h"
#include "Day19/Aplenty.h"
#include "Day20/PulsePropogation.h"
#include "Day21/StepCounter.h"

int main()
{
	std::printf("Welcome to the Advent of Code!\nPlease enter a number to see the solution for that day! (1 - 25)\n");

	int chosenDay = 21;
	while (chosenDay >= 0)
	{
		// std::cin >> chosenDay;

		if (chosenDay >= 25 || chosenDay <= 0)
		{
			return 0;
		}
		switch (chosenDay)
		{
		case 1:
		{
			printf("Sum of first calibration values: %i\n", Trebuchet::get(false));
			printf("Sum of second calibration values: %i\n", Trebuchet::get(true));

		}break;
		case 2:
		{
			printf("Total IDs: %i\n", CubeConundrum::get_total_ids());
			printf("Power sum: %i\n", CubeConundrum::get_powers());
		}break;
		case 3:
		{
			printf("Part numbers sum: %i\n", GearRatios::get());
			printf("Gear ratios sum: %i\n", GearRatios::getGears());
		}break;
		case 4:
		{
			printf("Scratch cards value: %i\n", ScratchCards::get());
			printf("Scratch cards total: %i\n", ScratchCards::getCards());
		}break;
		case 5:
		{
			printf("Maps value: %lld\n", Fertilizer::get());
			printf("Maps value: %lld\n", Fertilizer::getRange());
		}
		case 6:
		{
			printf("Race values %i\n", Races::get());
			printf("Single race value %i\n", Races::getPart2());
		}break;
		case 7:
		{
			printf("Card values: %i\n", CamelCards::get());
		}break;
		case 8:
		{
			printf("Map values: %i\n", HauntedWasteland::get());
			printf("Map values part 2: %lld\n", HauntedWasteland::get2());
		}break;
		case 9:
		{
			printf("Extrapolated sum: %i\n", MirageMaintenance::get());
			printf("Extrapolated historical sum: %i\n", MirageMaintenance::get2());
		}break;
		case 10:
		{
			printf("Pipe maze distance: %i\n", PipeMaze::get());
			printf("Pipe maze area: %i\n", PipeMaze::get2());
		}break;
		case 11:
		{
			printf("Map distance sum %i\n", CosmicExpansion::get());
			printf("Map distance sum %lld\n", CosmicExpansion::get2());
		}break;
		case 12:
		{
			printf("Hot springs possibilities: %i\n", HotSprings::get());
			printf("Hot springs possibilities: %llu\n", HotSprings::get2());
		}break;
		case 13:
		{
			printf("Mirror sum: %llu\n", LavaIsland::get());
			printf("Mirror sum: %llu\n", LavaIsland::get2());
		}break;
		case 14:
		{
			printf("Parabolic reflector sum: %llu\n", ParabolicReflector::get());
			printf("Parabolic reflector sum: %llu\n", ParabolicReflector::get2());
		}break;
		case 15:
		{
			printf("Hashed instruction sequence: %lld\n", LensLibrary::get());
			printf("Lens values sum: %lld\n", LensLibrary::get2());
		}break;
		case 16:
		{
			printf("Beam coverage: %lld\n", FloorLava::get());
			printf("Beam coverage: %lld\n", FloorLava::get2());
		}break;
		case 17:
		{
			printf("Lowest heat loss: %lld\n", ClumsyCrucible::get());
		}break;
		case 18:
		{
			printf("Filled area: %lld\n", LavaductLagoon::get());
			printf("Filled area: %lld\n", LavaductLagoon::get2());
		}break;
		case 19:
		{
			printf("Part rating sum %lld\n", Aplenty::get());
			printf("Accepted possible parts %lld\n", Aplenty::get2());
		}break;
		case 20:
		{
			printf("Pulses sent: %lld\n", PulsePropogation::get());
			printf("Minimum button presses: %lld\n", PulsePropogation::get2());
		}break;
		case 21:
		{
			// printf("Possible destinations: %lld\n", StepCounter::get());
			printf("Possible destinations: %lld\n", StepCounter::get2());
			chosenDay = 0;
		}break;
		default:
		{
			std::printf("That day isn't available yet! Check back later.\n");
		}break;
		}
	}
	return 0;
}