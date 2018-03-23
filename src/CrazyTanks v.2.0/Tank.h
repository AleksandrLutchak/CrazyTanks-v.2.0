#pragma once
#include "Collision.h"

class Tank : public Collision
{
private:
	
public:
	enum eDirection { UP, DOWN, LEFT, RIGHT, FIRE };
	eDirection dir;
	Tank();
};

