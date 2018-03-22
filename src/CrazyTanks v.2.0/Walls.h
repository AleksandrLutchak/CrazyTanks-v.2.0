#pragma once
#include <iostream>
#include <ctime>

class Walls
{
	int WallX;
	int WallY;
	int MainArrSize = gameMap.GetSizeArr();
	char WallSymbl = '#';
	char EmptySymbl = ' ';

public:
	void Frame();
	int randWallLocation();
	void CheckWallPosition();
	void BuildWalls();

};

