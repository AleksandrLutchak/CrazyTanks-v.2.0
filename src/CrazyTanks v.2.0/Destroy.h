#pragma once
class Destroy
{
	bool bGameOver = false;
	bool Winner;
public:
	Destroy();
	void AI_TankHit();
	void PlayerTankHit();
	void WallHit();
	void CastelHit();
	void GoldHit();

};

