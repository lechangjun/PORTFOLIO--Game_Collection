#pragma once

#include"Monster.h"

class Green_Snail : public Monster
{
	
public:

	//Green_Snail(std::string Name="GreenSnail", Item Item =Item::GREEN_SNAIL_SHELL,int Level=1, int Hp=15, int HpMax=15, int Mp=0, int MpMax=0, int Exp=3,int Gold=10,
	//	int Physical_damage_attack=2,int Magical_damage_attack=1,double Physical_defense_rate=0.1, double Magical_defense_rate=0.1) : 
	//	Monster(Name,Item, Level, Hp,HpMax, Mp,MpMax, Exp,Gold,Physical_damage_attack, Magical_damage_attack, Physical_defense_rate, Magical_defense_rate)
	//{
	//	
	//}
	

	virtual void Attack()
	{
		std::cout << Monster::getName() << "가 플레이어를 공격했다!" <<std:: endl;
	}

	virtual void CalculateDamage() override
	{
		std::cout << "dfd";
	}
	virtual void UseSkill() override
	{
		std::cout << "Mp가 부족해 skill을 사용할 수 없습니다" <<std::endl;
	}


};

