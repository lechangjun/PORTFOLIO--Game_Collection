#include "Character.h"

Character::Character()
{
}

inline int Character::Attack()
{

}

inline void Character::GetDamage(int Damage)
{
	 m_iHP -= Damage;
}

inline bool Character::DeathCheck()
{
	if (m_iHP <= 0)
		return true;
	else
		return false;
}


Character::~Character()
{
}