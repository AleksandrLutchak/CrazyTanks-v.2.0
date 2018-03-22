#pragma once
#include "Tank.h"

class AI_Tank : public Tank
{
public:
	AI_Tank(int x, int y);
	int randAI_TankLocation();
	void checkAI_TankLocation();
	void putAI_Tank();
	void killPlayer();
	void destroyGold();
};

