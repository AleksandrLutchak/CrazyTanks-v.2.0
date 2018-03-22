#pragma once
class Walls
{
	int WallX;
	int WallY;

public:
	void Frame();
	int randWallLocation();
	void CheckWallPosition();
	void BuildWalls();
};

