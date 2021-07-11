#pragma once
#include "stdafx.h"
#include "Item.h"

class Armor : public Item
{
private:

public:
	Armor();
	Armor(Armor* A);
	Armor(string Name, int Hp, int Att, int Price, int SPrice);
	~Armor();

	string Get_ArmorName() { return ItemI.Item_Name; }
	int Get_ArmorHp() { return ItemI.Item_Hp; }
	int Get_ArmorPrice() { return ItemI.Item_Price; }
	int Get_ArmorSPrice() { return ItemI._Item_Price; }
};