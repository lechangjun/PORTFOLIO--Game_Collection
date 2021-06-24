#pragma once

#include "Item.h"
#include"Weapon.h"
#include"Armor.h"
#include"Potion.h"

class Inventory
{
private:
	static const int			ITEMSIZE = 50;
	int							_pGold;		  //Player Gold
	Item<int>					_pTrophy	; //player trophy
	Item<Weapon>				_pWeapon	;
	Item<Armor>					_pArmor		;
	Item<Potion>				_pPotion	;
	int							_Itemcount;

public:

	Inventory(): _pGold(1000), _Itemcount(0)
	{
		_pTrophy.getiarr().resize(ITEMSIZE);
		_pWeapon.getiarr().resize(ITEMSIZE);
		_pArmor.getiarr().resize(ITEMSIZE);
		_pPotion.getiarr().resize(ITEMSIZE);

	}
	
	void ShowInfo() const
	{
		std::cout << "you have " << _pGold << "Gold" << std::endl;
	
		//std::cout << "you have Trophy ";
		//for (auto& ele_Trophy : _pTrophy)
		//{
		//	std::cout << ele_Trophy << "\t";
		//}
		//std::cout <<std::endl;

		//std::cout << "you have Weapon ";
		//for (auto& ele_Weapon : _pWeapon)
		//{
		//	std::cout << ele_Weapon << "\t";
		//}
		//std::cout << std::endl;

		//std::cout << "you have Armor ";
		//for (auto& ele_Armor : _pArmor)
		//{
		//	std::cout << ele_Armor << "\t";
		//}
		//std::cout << std::endl;

		//std::cout << "you have Potion ";
		//for (auto& ele_Potion : _pPotion)
		//{
		//	std::cout << ele_Potion << "\t";
		//}
		//std::cout << std::endl;
	}

};




//[ITEMSIZE]
//[ITEMSIZE]
//[ITEMSIZE]
//[ITEMSIZE]

