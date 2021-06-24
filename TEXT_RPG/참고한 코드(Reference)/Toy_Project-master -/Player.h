#pragma once

#include"Inventory.h"
#include<string>
#include<iostream>

class Player
{
private:

	std::string _Name;
	int			_Hp;
	int			_HpMax;
	int			_Mp; //���� MP ��Ȳ
	int			_MpMax; //�� ���ִ� MP ��Ȳ
	int			_Level;
	int			_STR; //�� ����
	int			_DEX; //��ø ����
	int			_INT; //���� ����
	int			_LUK; // �� ����
	int			_Physical_AttackMin; //�ּ� ���ݷ�, �ִ� ���ݷ� ��� �����ְ�
	int			_Physical_AttackMax;
	int			_Magical_AttackMin;
	int			_Magical_AttackMax;
	double		_Physical_Defense_Rate;
	double		_Magical_Defense_Rate;
	int			_Exp;
	int			_ExpMax;
	int			_Gold;
	Inventory	_Invetory;

public:

	Player(std::string name, int hp, int hpmax, int mp, int mpmax, int level, int str, int dex, int Int, int luk,
		int physicalattackmin, int physicalattackmax, int magicalattackmin, int magicalattackmax,
		double physicaldefenserate, double magicaldefenserate, int exp, int expmax) :
		_Name(name)
		, _Hp(hp)
		, _HpMax(hpmax)
		, _Mp(mp)
		, _MpMax(mpmax)
		, _Level(level)
		, _STR(str)
		, _DEX(dex)
		, _INT(Int)
		, _LUK(luk)
		, _Physical_AttackMin(physicalattackmin)
		, _Physical_AttackMax(physicalattackmax)
		, _Magical_AttackMin(magicalattackmin)
		, _Magical_AttackMax(magicalattackmax)
		, _Physical_Defense_Rate(physicaldefenserate)
		, _Magical_Defense_Rate(magicaldefenserate)
		, _Exp(exp)
		, _ExpMax(expmax)
		
	{}

	void ShowInfo() const 
	{
		std::cout << "Name: " << _Name << std::endl; 
		std::cout << "Hp/HpMax: " << _Hp << "/" << _HpMax << std::endl;  
		std::cout << "Mp/MpMax: " << _Mp << "/" << _MpMax << std::endl;
		std::cout << "STR: " << _STR << std::endl;
		std::cout << "DEX: " << _DEX << std::endl;
		std::cout << "INT: " << _INT << std::endl;
		std::cout << "LUK: " << _LUK << std::endl;
		std::cout << "Gold: " << _Gold << std::endl;
		std::cout << "Physical_AttackMin: " << _Physical_AttackMin << std::endl;
		std::cout << "Physical_AttackMax: " << _Physical_AttackMax << std::endl;
		std::cout << "Magical_AttackMin: " << _Magical_AttackMin << std::endl;
		std::cout << "Magical_AttackMax: " << _Magical_AttackMax << std::endl;
		std::cout << "Physical_Defense_Rate: " << _Physical_Defense_Rate << std::endl;
		std::cout << "Magical_Defense_Rate: " << _Magical_Defense_Rate << std::endl;
		std::cout << "Exp/ExpMax: " << _Exp << "/" << _ExpMax << std::endl;
		
	}

	void setInventory()
	{

	}

	Inventory& getInventory()
	{
		return _Invetory;
	}

	void ShowInventory(const Inventory& Inven)
	{
		Inven.ShowInfo();
	}


	void setName(const std::string& name) 
	{
		_Name = name;
	}
	
		
	


		
	








};

