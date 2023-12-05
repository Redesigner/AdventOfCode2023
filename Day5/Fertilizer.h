#pragma once

#include <vector>
#include <string>

using int64 = long long int;

namespace Fertilizer
{
	struct Range
	{
		Range(const std::vector<std::string>& values);

		int64 sourceStart = 0;
		int64 sourceEnd = 0;

		int64 outputStart = 0;
		int64 outputEnd = 0;

		int64 offset = 0;

		bool inSourceRange(int64 value) const;
		int64 map(int64 value) const;
		bool inOutputRange(int64 value) const;
		int64 reverseMap(int64 value) const;
	};

	struct SeedRange
	{
		SeedRange(int64 start, int64 end);

		int64 start;
		int64 end;

		bool inRange(int64 value) const;
	};

	int64 get();
	int64 getRange();
}