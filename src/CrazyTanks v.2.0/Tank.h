
#include "Collision.h"

class Tank : public Collision
{
private:

public:
	bool bAI_tank1;
	bool bAI_tank2;
	bool bAI_tank3;
	bool bAI_tank4;
	bool bAI_tank5;
	bool bAI_tank6;

	bool Win;
	
	enum eDirection { UP, DOWN, LEFT, RIGHT };
	eDirection playerDir;

	int HP_;
	int score_;
	int numbAI_Tanks;

	Tank();
};

