#include <iostream>
#include <chrono>

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

int main()
{
	std::printf("Welcome to the Advent of Code!\nPlease enter a number to see the solution for that day! (1 - 25)\n");

	int chosenDay = 14;
	while (chosenDay >= 0)
	{
		//std::cin >> chosenDay;

		if (chosenDay >= 25 || chosenDay <= 0)
		{
			return 0;
		}

		std::chrono::system_clock::time_point startTime;
		std::chrono::system_clock::time_point endTime;
		switch (chosenDay)
		{
		case 1:
		{
			startTime = std::chrono::system_clock::now();
			std::printf("Sum of first calibration values: %i\n", Trebuchet::get(false));
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

			startTime = std::chrono::system_clock::now();
			std::printf("Sum of second calibration values: %i\n", Trebuchet::get(true));
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

		}break;
		case 2:
		{
			startTime = std::chrono::system_clock::now();
			std::printf("Total IDs: %i\n", CubeConundrum::get_total_ids());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

			std::printf("Power sum: %i\n", CubeConundrum::get_powers());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);
		}break;
		case 3:
		{
			startTime = std::chrono::system_clock::now();
			std::printf("Part numbers sum: %i\n", GearRatios::get());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

			startTime = std::chrono::system_clock::now();
			std::printf("Gear ratios sum: %i\n", GearRatios::getGears());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);
		}break;
		case 4:
		{
			startTime = std::chrono::system_clock::now();
			std::printf("Scratch cards value: %i\n", ScratchCards::get());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

			startTime = std::chrono::system_clock::now();
			std::printf("Scratch cards total: %i\n", ScratchCards::getCards());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);
		}break;
		case 5:
		{
			startTime = std::chrono::system_clock::now();
			std::printf("Maps value: %lld\n", Fertilizer::get());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

			startTime = std::chrono::system_clock::now();
			std::printf("Maps value: %lld\n", Fertilizer::getRange());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);
		}
		case 6:
		{
			startTime = std::chrono::system_clock::now();
			printf("Race values %i\n", Races::get());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);

			startTime = std::chrono::system_clock::now();
			printf("Single race value %i\n", Races::getPart2());
			endTime = std::chrono::system_clock::now();
			printf("Calculated values in %.3f ms\n", std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f);
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
		}
		default:
		{
			std::printf("That day isn't available yet! Check back later.\n");
			chosenDay = 0;
		}break;
		}
	}
	return 0;
}