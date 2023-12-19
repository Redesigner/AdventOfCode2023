#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Aplenty
{
	struct Part
	{
		Part(std::string token);

		int x = 0;
		int m = 0;
		int a = 0;
		int s = 0;

		bool accepted = false;
	};

	enum Category
	{
		X,
		M,
		A,
		S,
		Invalid
	};
	enum Destination
	{
		Accepted,
		Rejected,
		Jump
	};

	struct Rule
	{
		Rule(std::string_view token);

		std::string process(Part& part) const;

		Category category;
		int value;
		bool greaterThan;
		std::string workflow;
		Destination destination;
	};

	struct Workflow
	{
		Workflow(std::string token);
		Workflow();

		std::string processPart(Part& part);

		Destination finalDestination;
		std::string jumpDestination;
		std::vector<Rule> rules;
	};

	struct Range
	{
		Range(int start, int end);
		Range();

		std::vector<Range> split(int separator) const;
		bool inside(int value) const;
		int width() const;

		int start = 0;
		int end = 0;
	};

	struct PartRange
	{
		PartRange(int start, int end, std::string destination);

		std::vector<PartRange> splitByRule(Rule& rule) const;

		int64_t value() const;

		Range x;
		Range m;
		Range a;
		Range s;
		std::string destination;
		bool accpeted = false;
	};

	int64_t get();
	int64_t get2();

	Category getCategory(char c);
}