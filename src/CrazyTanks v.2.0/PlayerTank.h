#pragma once
#include "Tank.h"

class PlayerTank : public Tank
{
	enum eDirection { UP, DOWN, RIGHT, LEFT };
	eDirection PlayerDirection;

	const int HelthPoints = 3;
	int Score;

public:
	PlayerTank(int x, int y);
	void Input();
};

