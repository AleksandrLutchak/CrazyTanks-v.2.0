#pragma once
#include <iostream>

using namespace std;

class GameMap
{
	static const int SIZE_Arr = 20;
	
	
public:

	char MapMainArr[SIZE_Arr][SIZE_Arr];
	char BattleArr[SIZE_Arr][SIZE_Arr];

	void printMap();
	
};

GameMap gameMap;