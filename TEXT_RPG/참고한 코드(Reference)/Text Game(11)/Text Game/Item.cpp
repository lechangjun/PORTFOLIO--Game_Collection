#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::Item(Item* I)
{
	ItemI.Item_Name = I->ItemI.Item_Name;
	ItemI.Item_Hp = I->ItemI.Item_Hp;
	ItemI.Item_Att = I->ItemI.Item_Att;

	ItemI.Item_Price = I->ItemI.Item_Price;
	ItemI._Item_Price = I->ItemI._Item_Price;
}

Item::Item(string Name, int Hp, int Att, int Price, int SPrice)
{
	ItemI.Item_Name = Name;
	ItemI.Item_Hp = Hp;
	ItemI.Item_Att = Att;

	ItemI.Item_Price = Price;
	ItemI._Item_Price = SPrice;
}

Item::~Item()
{

}