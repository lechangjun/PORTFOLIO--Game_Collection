#include "stdafx.h"
#include "Potion.h"

Potion::Potion()
{
}

Potion::Potion(Potion* P)
{
	ItemI.Item_Name = P->ItemI.Item_Name;
	ItemI.Item_Hp = P->ItemI.Item_Hp;
	ItemI.Item_Att = P->ItemI.Item_Att;

	ItemI.Item_Price = P->ItemI.Item_Price;
	ItemI._Item_Price = P->ItemI._Item_Price;
}

Potion::Potion(string Name, int Hp, int Att, int Price, int SPrice)
{
	ItemI.Item_Name = Name;
	ItemI.Item_Hp = Hp;
	ItemI.Item_Att = Att;

	ItemI.Item_Price = Price;
	ItemI._Item_Price = SPrice;
}

Potion::~Potion()
{
}
