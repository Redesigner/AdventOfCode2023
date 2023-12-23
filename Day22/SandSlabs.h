#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace SandSlabs
{
	struct Vector3
	{
		Vector3(int x, int y, int z);
		Vector3();

		bool operator==(const Vector3& otherVector) const;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;

		int x;
		int y;
		int z;
	};

	struct Brick
	{
		Brick(Vector3 start, Vector3 end, std::string label);
		Brick() = delete;

		bool overlaps(const Brick& other) const;
		bool moveDown(std::vector<Brick>& bricks);

		bool canBeRemoved() const;
		int bricksOnlySupport() const;

		std::string label;
		Vector3 origin;
		Vector3 size;
		bool stable = false;
		std::vector<Brick*> bricksSupporting;
		std::vector<Brick*> supports;
	};

	int64_t get();
	int64_t get2();

	bool containsFullSet(const std::vector<Brick*>& source, const std::vector<Brick*>& set);
	bool contains(const std::vector<Brick*> source, const Brick* brick);
}