#pragma once
#include "Character.h"
#include "Enemy.h"

class BattleField
{
public:
	BattleField();
	~BattleField();

	void GameStart();

	void Store();
	void Field();
	void Hospital();

private:
	Character player;
	Enemy enemy;

	int select;

};