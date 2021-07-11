#pragma once
#include "stdafx.h"
#include "Item.h"

enum class MonsterType
{
	Rat,
	Golem,
	Skeleton
};

class Monster
{
	string M_Name;
	int M_MAXHP;
	int M_HP;
	int M_ATT;

	int M_Num;
protected:
public:
	Monster();
	~Monster();

	string GetM_Name() { return M_Name; }
	int GetM_MAXHP() { return M_MAXHP; }
	int GetM_HP() { return M_HP; }
	int GetM_ATT() { return M_ATT; }

	void M_Create();
	int M_Select();
	void M_Profile(MonsterType(Num));
	void Show_M_Profile();

	void Damage(int val);
};