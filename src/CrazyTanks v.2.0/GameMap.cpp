#include "stdafx.h"
#include "GameMap.h"


char GameMap::printMap(char arr[][_SIZE_Arr])
{
	Sleep(SleepScale_);
	system ("cls");
	for (int i = 0; i < _SIZE_Arr; i++)
	{
		for (int j = 0; j < _SIZE_Arr; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
	return 0;
}

void GameMap::RefreshMap(char (*mainArr)[_SIZE_Arr], char (*BattleArr)[_SIZE_Arr])
{
	for (int i = 0; i < _SIZE_Arr; i++)
		for (int j = 0; j < _SIZE_Arr; j++)
			BattleArr[i][j] = mainArr[i][j];
}


