#pragma once

#include <vector>

namespace MirageMaintenance
{
	int get();

	int get2();

	bool isZero(const std::vector<int>& values);

	std::vector<int> extrapolateValues(const std::vector<int>& values);

	void extrapolateUntilZero(std::vector<std::vector<int>>& values);

	int getSum(const std::vector<std::vector<int>>& values);

	int getHistory(const std::vector<std::vector<int>>& values);
}