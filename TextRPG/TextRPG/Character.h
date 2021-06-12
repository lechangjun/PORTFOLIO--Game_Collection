#pragma once
#include "Macro.h"

class Character
{
protected:
	string m_strName;
	int m_iLevel;
	int m_iAttack;
	int m_iHP;
	int m_iDefaultHP;
	int m_iDefaultEXP;
	int m_iGetEXP;
	int m_iGold;
public:
	virtual inline int Attack() = 0;
	virtual inline bool DeathCheck();
	virtual inline void GetDamage(int Damage);

	Character();
	virtual ~Character();
};

