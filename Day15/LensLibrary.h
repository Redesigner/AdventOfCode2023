#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace LensLibrary
{
	struct Lens
	{
		Lens(const std::string& input);

		std::string label;
		int focalLength;
		char controlChar;
	};

	int64_t get();
	int64_t get2();

	int64_t hash(const std::string& value);

	void removeLens(std::vector<std::vector<Lens>>& map, const std::string& label, int position);

	void insertUniqueLens(std::vector<std::vector<Lens>>& map, const Lens& lens, int position);
}