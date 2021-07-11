#pragma once
#include "stdafx.h"
#include "Item.h"

class Weapon : public Item
{
private:
public:
	Weapon();
	Weapon(Weapon* W);
	Weapon(string Name, int Hp, int Att, int Price, int SPrice);
	~Weapon();

	string Get_WeaponName() { return ItemI.Item_Name; }
	int Get_WeaponAtt() { return ItemI.Item_Att; }
	int Get_WeaponPrice() { return ItemI.Item_Price; }
	int Get_WeaponSPrice() { return ItemI._Item_Price; }
};