#include "stdafx.h"
#include "GameMap.h"
#include "Walls.h"


void Walls::Frame()
{
	
}

int Walls::randWallLocation()
{
	srand(time(0));
	int NewWallLocation = rand() % MainArrSize + 1;
	return NewWallLocation;
}

void Walls::CheckWallPosition()
{
}

void Walls::BuildWalls()
{
}
