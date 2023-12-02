#pragma once

#include <string>

namespace Trebuchet
{
	int get(bool useWords);

	int matchStringToInt(std::string& string);

	int getFirstInteger(std::string& string, bool useWords);

	int getLastInteger(std::string& string, bool useWords);
}