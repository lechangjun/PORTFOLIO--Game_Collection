#ifndef __Monsterheader__
#define __Monsterheader__

#include"Trophy.h"
#include<string>
#include<iostream>
#include<tuple>
class Monster
{
private:

	std::string _Name;
	Trophy		_Item;
	int			_Level;
	int			_Hp;
	int			_HpMax;
	int			_Mp;
	int			_MpMax;
	int			_Exp;
	int			_Gold;
	int			_Physical_damage_attack;
	int			_Magical_damage_attack;
	double		_Physical_defense_rate;
	double		_Magical_defense_rate;
	std::tuple<int, Trophy> _Drops;

public:

	Monster(std::string Name, Trophy Item, int Level, int Hp,int HpMax, int Mp,int MpMax, int Exp, int Gold, int Physical_damage_attack,
		int Magical_damage_attack, double Physical_defense_rate, double Magical_defense_rate) :
		  _Name(Name)
		, _Item(Item)
		, _Level(Level)
		, _Hp(Hp)
		, _HpMax(HpMax)
		, _Mp(Mp)
		, _MpMax(MpMax)
		, _Exp(Exp)
		, _Gold(Gold)
		, _Physical_damage_attack(Physical_damage_attack)
		, _Magical_damage_attack(Magical_damage_attack)
		, _Physical_defense_rate(Physical_defense_rate)
		, _Magical_defense_rate(Magical_defense_rate)
	{
		_Drops = std::make_tuple(_Gold, _Item);

	}

	virtual ~Monster()
	{}

	virtual const std::string& getName() const
	{
		return _Name;
	}
	virtual	const int& getLevel() const
	{
		return _Level;
	}
	virtual	const int& getHp() const
	{
		return _Hp;
	}
	virtual	const int& getMp() const
	{
		return _Mp;
	}
	virtual	const int& getExp() const
	{
		return _Exp;
	}
	virtual	const int& getGold() const
	{
		return _Gold;
	}
	virtual	const int& getPhysical_damage_attack() const
	{
		return _Physical_damage_attack;
	}
	virtual	const int& getMagical_damage_attack() const
	{
		return _Magical_damage_attack;
	}
	virtual	const double& getPhysical_defense_rate() const
	{
		return _Physical_defense_rate;
	}
	virtual	const double& getMagical_defense_rate() const
	{
		return _Magical_defense_rate;
	}
	//골드랑 아이템을 한번에 튜플로 반환=>나중에 주인공이 받아서 인벤토리에 넣을거다
	virtual const std::tuple<int, Trophy>& getDrops()
	{
		return _Drops; //나중에 tuple을 get으로 받아서 인벤토리에 넣을거다.
	}

	virtual void ShowInfo() const
	{
		std::cout << "Name:"<< _Name<<" " << "Level:" << _Level<<" " <<"Hp:"<< _Hp<<" " << "Mp:"<< _Mp <<std::endl;
	}


	//virtual void Attack()  = 0;
	virtual void UseSkill() = 0;
	virtual void CalculateDamage()  = 0;

};


#endif
