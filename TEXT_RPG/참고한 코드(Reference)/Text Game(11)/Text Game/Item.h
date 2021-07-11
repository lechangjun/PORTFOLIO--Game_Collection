#pragma once
#include "stdafx.h"

class Item
{
private:
protected:
	struct ItemInfo
	{
		string Item_Name;
		int Item_Hp;
		int Item_Att;

		int Item_Price;
		int _Item_Price;
	}ItemI;

public:
	Item();
	Item(Item* I);
	Item(string Name, int Hp, int Att, int Price, int SPrice);

	virtual ~Item();
};