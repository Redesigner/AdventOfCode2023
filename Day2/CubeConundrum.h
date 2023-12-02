#pragma once

#include <string>
#include <vector>

namespace CubeConundrum
{
	struct CubeBag
	{
		int red;
		int green;
		int blue;

		bool operator <=(CubeBag& otherBag) const;
	};

	int get_total_ids();

	int get_powers();

	std::vector<CubeBag> getCubeBagsFromString(std::string& string);

	CubeBag getCubeBagFromString(std::string& string);

	bool isGameValid(const std::vector<CubeBag>& bags, CubeBag& referenceBag);

	CubeBag getMinimumSize(const std::vector<CubeBag>& bags);
}