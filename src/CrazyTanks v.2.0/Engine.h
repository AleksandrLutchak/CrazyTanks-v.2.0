
#include <iostream>
#include <ctime>
#include <conio.h>


#include "Castle.h"
#include "Gold.h"
#include "Wall.h"
#include "Tank.h"
#include "Bullet.h"
#include "GameMap.h"

class Engine
{
private:
	Castle castle;
	Wall wall;
	Gold gold;
	Tank PlayerTank;
	Tank AI_Tank;
	Tank AI_Tank1;
	Tank AI_Tank2;
	Tank AI_Tank3;
	Tank AI_Tank4;
	Tank AI_Tank5;
	Tank AI_Tank6;
	Bullet bullet;
	Bullet bullet2;
	Bullet bullet3;
	Bullet bullet4;

	GameMap Map;

	static const int _SIZE_Arr = 20;
	const int MaxWallSize_ = 4;

	char MapMainArr[_SIZE_Arr][_SIZE_Arr];
	char BattleArr[_SIZE_Arr][_SIZE_Arr];

	bool _bGameOver;
	bool bIsFirePressed_;
	bool _bWinner;
	bool PlayerWin;
	bool AIWin;

	int numbAI_Tanks;
	
private:
	void Frame();
	void CheckWallLocation(char mainArr[][_SIZE_Arr], int wallX, int wallY, char Symbol, int WallSize);
	void CheckAI_TankLocation(char mainArr[][_SIZE_Arr], int randTankX, int randTankY, int& AI_TankX, int& AI_TankY, char AI_TankSymbol, char wallSymb);
	void BuildObjects(int& pTankX, int& pTankY);
	void PlayerControllers();
	void SetMovement();
	void CheckMovement(char mainArr[][_SIZE_Arr], int& AI_TankX, int& AI_TankY, char AI_TankSymbol);
	void Shot();
	void CheckBulletWithObjectHit(int& AI_TankX, int& AI_TankY);
	void KillPlayer();
	void DestroyGold();
	void GameResult(bool pWin, bool aiWin);
	
public:
	Engine();
	int RandLocation();

	
		
};

