#pragma once
#include"Player.h"

class Warrior : public Player
{

public:

	Warrior(std::string name="warrior", int hp = 500, int hpmax = 500, int mp = 100, int mpmax = 100, int level = 1, int str = 20, int dex = 5, int Int = 5, int luk = 10,
		int physicalattackmin = 5, int physicalattackmax = 10, int magicalattackmin = 0, int magicalattackmax = 0,
		double physicaldefenserate = 0.2, double magicaldefenserate = 0.1, int exp = 0, int expmax = 100) :
		Player(name, hp, hpmax, mp, mpmax, level, str, dex, Int, luk,
			physicalattackmin, physicalattackmax, magicalattackmin, magicalattackmax,
			physicaldefenserate, magicaldefenserate, exp, expmax)
	{}

	~Warrior()
	{
		std::cout << "¼Ò¸êÀÚ È£Ãâ" << std::endl;
	}

};

