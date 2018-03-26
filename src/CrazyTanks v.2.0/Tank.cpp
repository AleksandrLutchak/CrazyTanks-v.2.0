#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
{
	bAI_tank1 = false;
	bAI_tank2 = false;
	bAI_tank3 = false;
	bAI_tank4 = false;
	bAI_tank5 = false;
	bAI_tank6 = false;

	Win = false;
	
	numbAI_Tanks = 6;

	score_ = 0;
	HP_ = 3;
	Symbol = 'O';
	
}

