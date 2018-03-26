#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	bAI_tank1 = false;
	bAI_tank2 = false;
	bAI_tank3 = false;
	bAI_tank4 = false;
	bAI_tank5 = false;
	bAI_tank6 = false;
	_bGameOver = false;
	bIsFirePressed_ = false;
	PlayerWin = false;
	AIWin = false;
	numbAI_Tanks = 0;

	srand(time(0));
	BuildObjects(PlayerTank.x, PlayerTank.y);
	
	while (!_bGameOver)
	{
		map.RefreshMap(MapMainArr, BattleArr);
		PlayerControllers();
		
		SetMovement();

		if(!bAI_tank1)
			CheckMovement(BattleArr, AI_Tank1.x, AI_Tank1.y, AI_Tank1.Symbol);
		if (!bAI_tank2)
			CheckMovement(BattleArr, AI_Tank2.x, AI_Tank2.y, AI_Tank2.Symbol);
		if (!bAI_tank3)
			CheckMovement(BattleArr, AI_Tank3.x, AI_Tank3.y, AI_Tank3.Symbol);
		if (!bAI_tank4)
			CheckMovement(BattleArr, AI_Tank4.x, AI_Tank4.y, AI_Tank4.Symbol);
		if (!bAI_tank5)
			CheckMovement(BattleArr, AI_Tank5.x, AI_Tank5.y, AI_Tank5.Symbol);
		if (!bAI_tank6)
			CheckMovement(BattleArr, AI_Tank6.x, AI_Tank6.y, AI_Tank6.Symbol);

		Shot();
	
		map.printMap(BattleArr);
		//system("pause");
		if (_bGameOver)
			GameResult(PlayerWin, AIWin);
	}
}

void Engine::Frame()
{
	for (int i = 0; i < _SIZE_Arr; i++)
		for (int j = 0; j < _SIZE_Arr; j++)
		{
			if (i == 0 || i == _SIZE_Arr - 1 || j == 0 || j == _SIZE_Arr - 1)
				MapMainArr[i][j] = wall.Symbol;
			else
				MapMainArr[i][j] = ' ';
		}
}

int Engine::RandLocation()
{
	int NewLocation = rand() % _SIZE_Arr + 1;
	return NewLocation;
}

void Engine::CheckWallLocation(char mainArr [][_SIZE_Arr], int wallX, int wallY, char Symbol, int WallSize)
{
	bool bLocationCheck = false;
	bool bHorizontalCheck = false;
	bool bVerticalCheck = false;
	bool RandOrientation = rand() % 2;
		
	while (!bLocationCheck)
	{
		for (int x = 0; x < WallSize; x++)
			if (mainArr[RandOrientation ? wallX - 1 : wallY + x][RandOrientation ? wallY + x : wallX + 1] != Symbol
				&& mainArr[RandOrientation ? wallX : wallY + x][RandOrientation ? wallY + x : wallX] != Symbol
				&& mainArr[RandOrientation ? wallX + 1 : wallY + x][RandOrientation ? wallY + x : wallX + 1] != Symbol)
				bHorizontalCheck = true;
			else
			{
				bHorizontalCheck = false;
				break;
			}

		for (int x = 0; x < WallSize; x++)
			if (mainArr[RandOrientation ? (wallX - 1) + x : wallY + 1][RandOrientation ? wallY + 1 : (wallX - 1) + x] != Symbol
				&& mainArr[RandOrientation ? (wallX - 1) + x : wallY + WallSize - 1][RandOrientation ? wallY + WallSize - 1 : (wallX - 1) + x] != Symbol)
				bVerticalCheck = true;
			else
			{
				bVerticalCheck = false;
				break;
			}
		
		if (bVerticalCheck && bHorizontalCheck)
		{
			for (int x = 0; x < WallSize; x++)
				mainArr[RandOrientation ? wallX : wallY + x][RandOrientation ? wallY + x : wallX] = Symbol;
			bLocationCheck = true;
		}
		else
		{
			wallX = RandLocation();
			wallY = RandLocation();
		}
	}
}

void Engine::CheckAI_TankLocation(char mainArr[][_SIZE_Arr], int randTankX, int randTankY, int& AI_TankX, int& AI_TankY, char AI_TankSymbol, char wallSymb)
{
	bool panzerCheck = false;
	bool totalpanzerCheck = false;
	int safeZone = 3;
	int PanzerSafeZone = 5;
	
		while (!totalpanzerCheck)
		{
			for (int x = 0; x < PanzerSafeZone; x++)
			{
				if (   mainArr[randTankX - 2][(randTankY - 2) + x] != AI_TankSymbol 
					&& mainArr[randTankX - 1][(randTankY - 2) + x] != AI_TankSymbol 
					&& mainArr[randTankX]    [(randTankY - 2) + x] != AI_TankSymbol 
					&& mainArr[randTankX + 1][(randTankY - 2) + x] != AI_TankSymbol 
					&& mainArr[randTankX + 2][(randTankY - 2) + x] != AI_TankSymbol 
					&& MapMainArr[randTankX][randTankY] != gold.Symbol
					&& MapMainArr[randTankX][randTankY] != castle.Symbol
					&& MapMainArr[randTankX][randTankY] != wallSymb)
					panzerCheck = true;
				else
				{
					panzerCheck = false;
					break;
				}
			}
			if (panzerCheck)
			{
				mainArr[randTankX][randTankY] = AI_TankSymbol;
				totalpanzerCheck = true;
			
					AI_TankX = randTankX;
					AI_TankY = randTankY;
			
			}
			else
			{
				randTankX = RandLocation();
				randTankY = RandLocation();
			}
			panzerCheck = false;
		}
}

void Engine::BuildObjects(int& pTankX,int& pTankY)
{
	Frame(); // Draw the Frame

		/////Rand some walls///
	for (int i = 1; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_);
	for (int i = -1; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_ - 1);
	for (int i = -2; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_ - 2);
	for (int i = 0; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_ - 3);

	//////Spawn Castle////////
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MapMainArr[_SIZE_Arr + i - 3][((_SIZE_Arr / 2) - 1) + j] = castle.Symbol;
		}
	}

	//////Spawn some Gold//////
	gold.x += _SIZE_Arr - 2;
	gold.y += _SIZE_Arr / 2;

	MapMainArr[gold.x][gold.y] = gold.Symbol;

	/////Spawn PlayerTank///////
	pTankX =+ (_SIZE_Arr - 4);
	pTankY =+ (_SIZE_Arr / 2);

	BattleArr[PlayerTank.x][PlayerTank.y] = PlayerTank.Symbol = 'X';
	
	/////Spawn some AI_Tanks////
	CheckAI_TankLocation(BattleArr, RandLocation(), RandLocation(), AI_Tank1.x, AI_Tank1.y, AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(BattleArr, RandLocation(), RandLocation(), AI_Tank2.x, AI_Tank2.y, AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(BattleArr, RandLocation(), RandLocation(), AI_Tank3.x, AI_Tank3.y, AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(BattleArr, RandLocation(), RandLocation(), AI_Tank4.x, AI_Tank4.y, AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(BattleArr, RandLocation(), RandLocation(), AI_Tank5.x, AI_Tank5.y, AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(BattleArr, RandLocation(), RandLocation(), AI_Tank6.x, AI_Tank6.y, AI_Tank.Symbol, wall.Symbol);

}

void Engine::PlayerControllers()
{
	if (_kbhit())
		switch (_getch())
		{
		case 72:
			PlayerTank.playerDir = PlayerTank.UP;
			if(BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol 
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != AI_Tank.Symbol
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != castle.Symbol 
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != gold.Symbol)
			PlayerTank.x--;
			break;
		case 80:
			PlayerTank.playerDir = PlayerTank.DOWN;
			if (BattleArr[PlayerTank.x + 1][PlayerTank.y] != wall.Symbol 
				&& BattleArr[PlayerTank.x + 1][PlayerTank.y] != AI_Tank.Symbol
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != castle.Symbol 
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != gold.Symbol)
			PlayerTank.x++;
			break;
		case 77:
			PlayerTank.playerDir = PlayerTank.RIGHT;
			if (BattleArr[PlayerTank.x][PlayerTank.y + 1] != wall.Symbol 
				&& BattleArr[PlayerTank.x][PlayerTank.y + 1] != AI_Tank.Symbol
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != castle.Symbol 
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != gold.Symbol)
			PlayerTank.y++;
			break;
		case 75:
			PlayerTank.playerDir = PlayerTank.LEFT;
			if (BattleArr[PlayerTank.x][PlayerTank.y - 1] != wall.Symbol 
				&& BattleArr[PlayerTank.x][PlayerTank.y - 1] != AI_Tank.Symbol
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != castle.Symbol 
				&& BattleArr[PlayerTank.x - 1][PlayerTank.y] != wall.Symbol != gold.Symbol)
			PlayerTank.y--;
			break;
		case 32:
			cout << "BANG!";
			bIsFirePressed_ = true;

			bullet.tempBulletValX_ = bullet.SumOfBulletsX[0];
			bullet.tempBulletValY_ = bullet.SumOfBulletsY[0];
			bullet.SumOfBulletsX[0] = PlayerTank.x ;
			bullet.SumOfBulletsY[0] = PlayerTank.y;
						
			for (int i = 1; i <= bullet.iSumOfBullets; i++)
			{
 				bullet.temp2BulletValX_ = bullet.SumOfBulletsX[i];
				bullet.temp2BulletValY_ = bullet.SumOfBulletsY[i];

				bullet.SumOfBulletsX[i] = bullet.tempBulletValX_;
				bullet.SumOfBulletsY[i] = bullet.tempBulletValY_;

				bullet.tempBulletValX_ = bullet.temp2BulletValX_;
				bullet.tempBulletValY_ = bullet.temp2BulletValY_;
			}
			bullet.iSumOfBullets++;
			
			break;

		default:
			break;
		}
	
}

void Engine::SetMovement()
{
	for (int i = 0; i < _SIZE_Arr; i++)
		for (int j = 0; j < _SIZE_Arr; j++)
		{
			if (i == PlayerTank.x && j == PlayerTank.y)
				BattleArr[i][j] = PlayerTank.Symbol;

			if (!bAI_tank1)
				if (i == AI_Tank1.x && j == AI_Tank1.y)
					BattleArr[i][j] = AI_Tank1.Symbol;
			if (!bAI_tank2)
				if (i == AI_Tank2.x && j == AI_Tank2.y)
					BattleArr[i][j] = AI_Tank2.Symbol;
			if (!bAI_tank3)
				if (i == AI_Tank3.x && j == AI_Tank3.y)
					BattleArr[i][j] = AI_Tank3.Symbol;
			if (!bAI_tank4)
				if (i == AI_Tank4.x && j == AI_Tank4.y)
					BattleArr[i][j] = AI_Tank4.Symbol;
			if (!bAI_tank5)
				if (i == AI_Tank5.x && j == AI_Tank5.y)
					BattleArr[i][j] = AI_Tank5.Symbol;
			if (!bAI_tank6)
				if (i == AI_Tank6.x && j == AI_Tank6.y)
					BattleArr[i][j] = AI_Tank6.Symbol;

			for (int z = 0; z < bullet.iSumOfBullets; z++)
				if (i == bullet.SumOfBulletsX[z] && j == bullet.SumOfBulletsY[z])
					BattleArr[i][j] = bullet.Symbol;
		}
}

void Engine::CheckMovement(char mainArr[][_SIZE_Arr], int& AI_TankX, int& AI_TankY, char AI_TankSymbol)
{
	int randWalkOnMap = rand() % 4 + 1;  //4 - is 4 ways to go. UP DOWN RIGHT LEFT
	if (AI_TankX != 0 && AI_TankY != 0)
	{
		switch (randWalkOnMap)
		{
		case 1:
			if (mainArr[AI_TankX - 1][AI_TankY] != AI_Tank.Symbol
				&& mainArr[AI_TankX - 1][AI_TankY] != PlayerTank.Symbol
				&& mainArr[AI_TankX - 1][AI_TankY] != wall.Symbol
				&& mainArr[AI_TankX - 1][AI_TankY] != gold.Symbol
				&& mainArr[AI_TankX - 1][AI_TankY] != castle.Symbol)
				AI_TankX--;
			else
				break;
			break;
		case 2:
			if (mainArr[AI_TankX + 1][AI_TankY] != AI_Tank.Symbol
				&& mainArr[AI_TankX + 1][AI_TankY] != PlayerTank.Symbol
				&& mainArr[AI_TankX + 1][AI_TankY] != wall.Symbol
				&& mainArr[AI_TankX + 1][AI_TankY] != gold.Symbol
				&& mainArr[AI_TankX + 1][AI_TankY] != castle.Symbol)
				AI_TankX++;
			else
				break;
			break;
		case 3:
			if (mainArr[AI_TankX][AI_TankY + 1] != AI_Tank.Symbol
				&& mainArr[AI_TankX][AI_TankY + 1] != PlayerTank.Symbol
				&& mainArr[AI_TankX][AI_TankY + 1] != wall.Symbol
				&& mainArr[AI_TankX][AI_TankY + 1] != gold.Symbol
				&& mainArr[AI_TankX][AI_TankY + 1] != castle.Symbol)
				AI_TankY++;
			else
				break;
			break;
		case 4:
			if (mainArr[AI_TankX][AI_TankY - 1] != AI_Tank.Symbol
				&& mainArr[AI_TankX][AI_TankY - 1] != PlayerTank.Symbol
				&& mainArr[AI_TankX][AI_TankY - 1] != wall.Symbol
				&& mainArr[AI_TankX][AI_TankY - 1] != gold.Symbol
				&& mainArr[AI_TankX][AI_TankY - 1] != castle.Symbol)
				AI_TankY--;
			else
				break;
			break;

		default:
			break;
		}

		//BattleArr[AI_TankX][AI_TankY] = AI_TankSymbol;
	}
}

void Engine::Shot()
{
	for (int i = 0; i < bullet.iSumOfBullets; i++)
	{
		/*if (PlayerTank.playerDir == PlayerTank.UP && bIsFirePressed_)
		{*/
			bullet.x = bullet.SumOfBulletsX[i];
			bullet.tempSumOfBulletsX[i] = bullet.x;
			bullet.x--;
			bullet.SumOfBulletsX[i] = bullet.x;
			bIsFirePressed_ = false;
			bullet.y = bullet.SumOfBulletsY[i];
		//}
		//else if (bullet.tempSumOfBulletsX[i] > bullet.x && bullet.x != 0)
		//{
		//	bullet.tempSumOfBulletsX[i] = bullet.x;
		//	bullet.x--;
		//	bullet.SumOfBulletsX[i] = bullet.x;
		//}
		//
		//if (PlayerTank.playerDir == PlayerTank.DOWN && bIsFirePressed_)
		//{
		//	bullet2.x = bullet.SumOfBulletsX[i];
		//	bullet.tempSumOfBulletsX[i] = bullet2.x;
		//	bullet2.x++;
		//	bullet.SumOfBulletsX[i] = bullet2.x;
		//	bIsFirePressed_ = false;
		//}
		//else if (bullet.tempSumOfBulletsX[i] < bullet2.x && bullet2.x != 0)
		//{
		//	//bullet.tempSumOfBulletsX[i] = bullet2.x;
		//	bullet2.x++;
		//	bullet.SumOfBulletsX[i] = bullet2.x;
		//}
		//if (PlayerTank.playerDir == PlayerTank.LEFT && bIsFirePressed_)
		//{
		//	bullet3.y = bullet.SumOfBulletsY[i];
		//	bullet.tempSumOfBulletsY[i] = bullet3.y;
		//	bullet3.y--;
		//	bullet.SumOfBulletsY[i] = bullet3.y;
		//	bIsFirePressed_ = false;
		//	bullet.x = bullet.SumOfBulletsX[i];
		//}
		//else if (bullet.tempSumOfBulletsY[i] > bullet3.y && bullet3.y != 0)
		//{
		//	//bullet.tempSumOfBulletsY[i] = bullet3.y;
		//	bullet3.y--;
		//	bullet.SumOfBulletsY[i] = bullet3.y;
		//}
		//
		//if (PlayerTank.playerDir == PlayerTank.RIGHT && bIsFirePressed_)
		//{
		//	bullet4.y = bullet.SumOfBulletsY[i];
		//	bullet.tempSumOfBulletsY[i] = bullet4.y;
		//	bullet4.y++;
		//	bullet.SumOfBulletsY[i] = bullet4.y;
		//	bIsFirePressed_ = false;
		//}
		//else if (bullet.tempSumOfBulletsY[i] < bullet4.y && bullet4.y != 0)
		//{
		//	//bullet.tempSumOfBulletsY[i] = bullet4.y;
		//	bullet4.y++;
		//	bullet.SumOfBulletsY[i] = bullet4.y;
		//}
		//

	}

	CheckBulletWithObjectHit(AI_Tank1.x, AI_Tank1.y, bAI_tank1);
	CheckBulletWithObjectHit(AI_Tank2.x, AI_Tank2.y, bAI_tank2);
	CheckBulletWithObjectHit(AI_Tank3.x, AI_Tank3.y, bAI_tank3);
	CheckBulletWithObjectHit(AI_Tank4.x, AI_Tank4.y, bAI_tank4);
	CheckBulletWithObjectHit(AI_Tank5.x, AI_Tank5.y, bAI_tank5);
	CheckBulletWithObjectHit(AI_Tank6.x, AI_Tank6.y, bAI_tank6);
}

void Engine::CheckBulletWithObjectHit(int& AI_TankX, int& AI_TankY, bool bIsDead)
{
	
	for (int i = 0; i < bullet.iSumOfBullets; i++)
	{
		if (MapMainArr[bullet.SumOfBulletsX[i]][bullet.SumOfBulletsY[i]] == wall.Symbol)
		{
			MapMainArr[bullet.SumOfBulletsX[i]][bullet.SumOfBulletsY[i]] = castle.Symbol;
			bullet.SumOfBulletsX[i] = 0;
			bullet.SumOfBulletsY[i] = 0;
			bullet.iSumOfBullets--;

		}
		if (MapMainArr[bullet.SumOfBulletsX[i]][bullet.SumOfBulletsY[i]] == castle.Symbol)
		{
			MapMainArr[bullet.SumOfBulletsX[i]][bullet.SumOfBulletsY[i]] = 0;
			bullet.SumOfBulletsX[i] = 0;
			bullet.SumOfBulletsY[i] = 0;
			bullet.iSumOfBullets--;

		}
		if (MapMainArr[bullet.SumOfBulletsX[i]][bullet.SumOfBulletsY[i]] == gold.Symbol)
		{
			bullet.SumOfBulletsX[i] = 0;
			bullet.SumOfBulletsY[i] = 0;
			bullet.iSumOfBullets--;

			AIWin = true;
			_bGameOver = true;
		}
		if (bullet.SumOfBulletsX[i] == AI_TankX && bullet.SumOfBulletsY[i] == AI_TankY)
		{
  			bullet.SumOfBulletsX[i] = 0;
			bullet.SumOfBulletsY[i] = 0;
			bullet.iSumOfBullets--;
			AI_TankX = 0;
			AI_TankY = 0;
			bIsDead = true;
		}
	}
	if (AI_Tank1.x == 0 && AI_Tank1.y == 0 &&
		AI_Tank2.x == 0 && AI_Tank2.y == 0 &&
		AI_Tank3.x == 0 && AI_Tank3.y == 0 &&
		AI_Tank4.x == 0 && AI_Tank4.y == 0 &&
		AI_Tank5.x == 0 && AI_Tank5.y == 0 &&
		AI_Tank6.x == 0 && AI_Tank6.y == 0)
	{
         PlayerWin = true;
		_bGameOver = true;
	}
	
}

void Engine::KillPlayer()
{

}

void Engine::DestroyGold()
{

}

void Engine::GameResult(bool pWin, bool aiWin)
{
	if (pWin)
		cout << "\t\tNICE!";
	system("pause");
}
