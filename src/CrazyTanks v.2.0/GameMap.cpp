#include "stdafx.h"
#include "GameMap.h"


void GameMap::printMap()
{
	{
		for (int x = 0; x < SIZE_Arr; x++)
			for (int y = 0; y < SIZE_Arr; y++)
			{
				cout << BattleArr[x][y];
			}
		cout << endl;
	}
}
