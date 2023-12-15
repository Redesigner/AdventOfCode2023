#pragma once

#include <cstdint>
#include <string>

namespace LensLibrary
{
	int64_t get();
	int64_t get2();

	int64_t hash(const std::string& value);
}