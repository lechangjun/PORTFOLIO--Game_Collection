#pragma once
#include "stdafx.h"
#include "Item.h"

class Potion : public Item
{
private:

public:
	Potion();
	Potion(Potion* P);
	Potion(string Name, int Hp, int Att, int Price, int SPrice);
	~Potion();

	string Get_PotionName() { return ItemI.Item_Name; }
	int Get_PotionHp() { return ItemI.Item_Hp; }
	int Get_PotionAtt() { return ItemI.Item_Att; }
	int Get_PotionPrice() { return ItemI.Item_Price; }
	int Get_PotionSPrice() { return ItemI._Item_Price; }
};