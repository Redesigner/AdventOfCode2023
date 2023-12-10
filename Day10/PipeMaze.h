#pragma once

#include <vector>

namespace PipeMaze
{
	struct Vector2
	{
		int x;
		int y;

		const bool operator==(const Vector2& otherVector) const;
		Vector2 operator+(const Vector2& otherVector) const;
		Vector2 operator-(const Vector2& otherVector) const;
		bool isNegative() const;

		static Vector2 north();
		static Vector2 south();
		static Vector2 east();
		static Vector2 west();
	};

	class Tile
	{
	public:
		Tile(char c);
		
		Vector2 getNext(Vector2 offset) const;

		int getDistance() const;
		void setDistance(int newDistance);

		bool isPipe() const;

		bool distanceSet() const;

		wchar_t toPrint() const;

		bool filled = false;

	private:
		bool valid;
		bool set;
		int distance;
		Vector2 entrance;
		Vector2 exit;
		wchar_t printChar;
	};

	int get();
	int get2();

	int traversePipe(std::vector<std::vector<Tile>>& map, Vector2 location, Vector2 startLocation);

	void fillAdjacentTiles(std::vector<std::vector<Tile>>& map, Vector2 location);

	int sumLine(std::vector<Tile>& tiles);
}