#pragma once
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
	Bullet bullet;

	GameMap Map;

	static const int _SIZE_Arr = 20;

	char MapMainArr[_SIZE_Arr][_SIZE_Arr];
	char BattleArr[_SIZE_Arr][_SIZE_Arr];

	bool _bGameOver = false;
	bool bIsFirePressed_ = false;
	bool _bWinner;

	bool up = false;
	bool down = false;
	bool left = false;

	bool caseUPCheck = false;
	bool caseDownCheck = false;
	bool caseRightCheck = false;
	bool caseLeftCheck = false;

	const int MaxWallSize_ = 4;
	int PlayerX;
	int PlayerY;
	int BulletY;
	int BulletX;
	int numbAI_Tanks = 0;
	int AI_TankX;
	int AI_TankY;
		
private:
	void Frame();
	void CheckWallLocation(char mainArr[][_SIZE_Arr], int wallX, int wallY, char Symbol, int WallSize);
	void CheckAI_TankLocation(char mainArr[][_SIZE_Arr], int TankX, int TankY, char AI_TankSymbol, char wallSymb);
	void BuildObjects();
	void PlayerControllers();
	void SetMovement();
	void CheckMovement(char mainArr[][_SIZE_Arr], int& AI_TankX, int& AI_TankY);
	void Shot();
	void CheckBulletWithObjectHit();
	void KillPlayer();
	void DestroyGold();
	void GameResult();
	
public:
	int RandLocation();
	Engine();
		
};

