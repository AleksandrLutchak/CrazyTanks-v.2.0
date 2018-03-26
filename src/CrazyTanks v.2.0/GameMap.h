#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

class GameMap
{
private:
	static const int _SIZE_Arr = 20;
	
public:
	const int SleepScale_ = 200;

	char printMap(char arr[][_SIZE_Arr]);
	void RefreshMap(char(*mainArr)[_SIZE_Arr], char(*BattleArr)[_SIZE_Arr]);
	
	
};

