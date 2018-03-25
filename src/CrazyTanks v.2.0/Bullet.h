
#include "Collision.h"

class Bullet : public Collision
{
private:
	static const int ammo = 400;

public:
	int tempBulletValX_, tempBulletValY_, temp2BulletValX_, temp2BulletValY_;
	int iSumOfBullets = 0;
	int SumOfBulletsX[ammo];
	int SumOfBulletsY[ammo];
	int tempSumOfBulletsX[ammo];
	int tempSumOfBulletsY[ammo];
	
	Bullet();


};

