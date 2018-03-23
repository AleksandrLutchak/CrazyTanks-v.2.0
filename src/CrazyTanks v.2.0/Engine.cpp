#include "stdafx.h"
#include "Engine.h"



Engine::Engine()
{
	srand(time(0));
	Frame(); // Draw the Frame
		
	BuildObjects();
	Map.RefreshMap(MapMainArr, BattleArr);
	while (!_bGameOver)
	{
		Map.printMap(BattleArr);
		PlayerControllers();
		Map.RefreshMap(MapMainArr, BattleArr);

		CheckMovement(BattleArr, AI_TankX, AI_TankY);

		SetMovement();
		Shot(); 

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

void Engine::CheckAI_TankLocation(char mainArr[][_SIZE_Arr], int TankX, int TankY, char AI_TankSymbol, char wallSymb)
{
	bool panzerCheck = false;
	
	bool totalpanzerCheck = false;
	int PanzerSafeZone = 5;

	while (!totalpanzerCheck)
	{
		for (int x = 0; x < PanzerSafeZone; x++)
		{
			if (mainArr[TankX - 2][(TankY - 2) + x] != AI_TankSymbol && mainArr[TankX - 1][(TankY - 2) + x] != AI_TankSymbol && mainArr[TankX][(TankY - 2) + x] != AI_TankSymbol &&
				mainArr[TankX + 1][(TankY - 2) + x] != AI_TankSymbol && mainArr[TankX + 2][(TankY - 2) + x] != AI_TankSymbol && mainArr[TankX][TankY] != wallSymb)
				panzerCheck = true;
			else
			{
				panzerCheck = false;
				break;
			}
		}
		if (panzerCheck)
		{
			mainArr[TankX][TankY] = AI_TankSymbol;
			totalpanzerCheck = true;
			
				AI_TankX = TankX;
				AI_TankY = TankY;
			
		}
		else
		{
			TankX = RandLocation();
			TankY = RandLocation();
		}
		panzerCheck = false;
	}
}

void Engine::BuildObjects()
{
		/////Rand some walls///
	for (int i = 1; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_);
	for (int i = -1; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_ - 1);
	for (int i = -2; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_ - 2);
	for (int i = 0; i < MaxWallSize_; i++)
		CheckWallLocation(MapMainArr, RandLocation(), RandLocation(), wall.Symbol, MaxWallSize_ - 3);

	/////Spawn some AI_Tanks////
	CheckAI_TankLocation(MapMainArr, RandLocation(), RandLocation(), AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(MapMainArr, RandLocation(), RandLocation(), AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(MapMainArr, RandLocation(), RandLocation(), AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(MapMainArr, RandLocation(), RandLocation(), AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(MapMainArr, RandLocation(), RandLocation(), AI_Tank.Symbol, wall.Symbol);
	CheckAI_TankLocation(MapMainArr, RandLocation(), RandLocation(), AI_Tank.Symbol, wall.Symbol);

	/////Spawn PlayerTank///////
	PlayerX = PlayerTank.x + (_SIZE_Arr - 4);
	PlayerY = PlayerTank.y + (_SIZE_Arr / 2);

	BattleArr[PlayerX][PlayerY] = PlayerTank.Symbol = 'X';

	//////Spawn Castle////////
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MapMainArr[_SIZE_Arr + i - 3][((_SIZE_Arr / 2) - 1) + j] = castle.Symbol;
		}
	}

	//////Spawn some Gold//////
	int GoldX = _SIZE_Arr - 2;
	int GoldY = _SIZE_Arr / 2;

	MapMainArr[GoldX][GoldY] = gold.Symbol;
}

void Engine::PlayerControllers()
{
	if (_kbhit())
		switch (_getch())
		{
		case 72:
			PlayerTank.dir = PlayerTank.UP;
			if(BattleArr[PlayerX - 1][PlayerY] != wall.Symbol && BattleArr[PlayerX - 1][PlayerY] != AI_Tank.Symbol)
			PlayerX--;
			up = true;
			break;
		case 80:
			PlayerTank.dir = PlayerTank.DOWN;
			if (BattleArr[PlayerX + 1][PlayerY] != wall.Symbol && BattleArr[PlayerX + 1][PlayerY] != AI_Tank.Symbol)
			PlayerX++;
			down = false;
			break;
		case 77:
			PlayerTank.dir = PlayerTank.RIGHT;
			if (BattleArr[PlayerX][PlayerY + 1] != wall.Symbol && BattleArr[PlayerX][PlayerY + 1] != AI_Tank.Symbol)
			PlayerY++;
			break;
		case 75:
			PlayerTank.dir = PlayerTank.LEFT;
			if (BattleArr[PlayerX][PlayerY - 1] != wall.Symbol && BattleArr[PlayerX][PlayerY - 1] != AI_Tank.Symbol)
			PlayerY--;
			left = true;
			break;
		case 32:
			PlayerTank.dir = PlayerTank.FIRE;
			cout << "BANG!";
			bIsFirePressed_ = true;

			bullet.tempBulletValX_ = bullet.SumOfBulletsX[0];
			bullet.tempBulletValY_ = bullet.SumOfBulletsY[0];
			
			/*if (up)
			{*/
				bullet.SumOfBulletsX[0] = PlayerX - 1;
				bullet.SumOfBulletsY[0] = PlayerY;
				down = false;  left = false;
			/*}
			if (down)
			{
				bullet.SumOfBulletsX[0] = PlayerX + 1;
				bullet.SumOfBulletsY[0] = PlayerY;
				up = false; left = false;
			}

			if (left)
			{
				bullet.SumOfBulletsX[0] = PlayerX;
				bullet.SumOfBulletsY[0] = PlayerY - 1;
				 up = false;
			}*/
			
				
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
		}
}

void Engine::SetMovement()
{
	for (int i = 0; i < _SIZE_Arr; i++)
		for (int j = 0; j < _SIZE_Arr; j++)
		{
			if (i == PlayerX && j == PlayerY)
				BattleArr[i][j] = PlayerTank.Symbol;

			for (int z = 0; z < bullet.iSumOfBullets; z++)
				if (i == bullet.SumOfBulletsX[z] && j == bullet.SumOfBulletsY[z])
					BattleArr[i][j] = bullet.Symbol;
		}
}

void Engine::CheckMovement(char mainArr[][_SIZE_Arr], int& AI_TankX, int& AI_TankY)
{
	int randWalkOnMap = rand() % 4 + 1;

	switch (randWalkOnMap)
	{
	case 1:
		if (mainArr[AI_TankX - 1][AI_TankY] != AI_Tank.Symbol && mainArr[AI_TankX - 1][AI_TankY] != PlayerTank.Symbol
			&& mainArr[AI_TankX - 1][AI_TankY] != wall.Symbol)
			AI_TankX--;
		else
		{
			caseUPCheck = false;
			break;
		}
		break;
	case 2:
		if (mainArr[AI_TankX + 1][AI_TankY] != AI_Tank.Symbol && mainArr[AI_TankX + 1][AI_TankY] != PlayerTank.Symbol
			&& mainArr[AI_TankX + 1][AI_TankY] != wall.Symbol)
			AI_TankX++;
		else
		{
			caseDownCheck = false;
			break;
		}
		break;
	case 3:
		if (mainArr[AI_TankX][AI_TankY + 1] != AI_Tank.Symbol && mainArr[AI_TankX][AI_TankY + 1] != PlayerTank.Symbol
			&& mainArr[AI_TankX][AI_TankY + 1] != wall.Symbol)
			AI_TankY++;
		else
		{
			caseRightCheck = false;
			break;
		}
		break;
	case 4:
		if (mainArr[AI_TankX][AI_TankY - 1] != AI_Tank.Symbol && mainArr[AI_TankX][AI_TankY - 1] != PlayerTank.Symbol
			&& mainArr[AI_TankX][AI_TankY - 1] != wall.Symbol)
			AI_TankY--;
		else
		{
			caseLeftCheck = false;
			break;
		}
		break;
	}

	mainArr[AI_TankX][AI_TankY] = AI_Tank.Symbol;
			
}

void Engine::Shot()
{
	for (int i = 0; i < bullet.iSumOfBullets; i++)
	{
		BulletX = bullet.SumOfBulletsX[i];
		bullet.tempSumOfBulletsX[i] = BulletX;
		BulletX--;
		bullet.SumOfBulletsX[i] = BulletX;

		BulletY = bullet.SumOfBulletsY[i];

	}
	CheckBulletWithObjectHit();
	
}

void Engine::CheckBulletWithObjectHit()
{
	for (int i = 0; i < bullet.iSumOfBullets; i++)
		if (MapMainArr[bullet.SumOfBulletsX[i]][bullet.SumOfBulletsY[i]] == wall.Symbol)
		{
			bullet.SumOfBulletsX[i] = 0;
			bullet.iSumOfBullets--;
		}
}

void Engine::KillPlayer()
{

}

void Engine::DestroyGold()
{

}

void Engine::GameResult()
{

}
