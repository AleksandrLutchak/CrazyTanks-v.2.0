
#include <iostream>
#include <windows.h>

using namespace std;

class GameMap
{
private:
	static const int _SIZE_Arr = 20;
	
	int PlayerY_;
	int PlayerX_;
public:
	const int SleepScale_ = 100;
	char printMap(char arr[][_SIZE_Arr]);
	void RefreshMap(char(*mainArr)[_SIZE_Arr], char(*BattleArr)[_SIZE_Arr]);
	
	
};

