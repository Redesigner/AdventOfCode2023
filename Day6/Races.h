#pragma once

namespace Races
{
	struct Race
	{
		Race(int time, long long int distance);

		int time;
		long long int record;

		int numberRecords() const;
	};

	int get();
	int getPart2();
}