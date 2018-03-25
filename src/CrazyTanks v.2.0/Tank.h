
#include "Collision.h"

class Tank : public Collision
{
private:
	
public:
	enum eDirection { UP, DOWN, LEFT, RIGHT };
	eDirection playerDir;
	Tank();
};

