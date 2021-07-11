#include "stdafx.h"
#include "Armor.h"

Armor::Armor()
{
}

Armor::Armor(Armor* A)
{
	ItemI.Item_Name = A->ItemI.Item_Name;
	ItemI.Item_Hp = A->ItemI.Item_Hp;
	ItemI.Item_Att = A->ItemI.Item_Att;

	ItemI.Item_Price = A->ItemI.Item_Price;
	ItemI._Item_Price = A->ItemI._Item_Price;
}

Armor::Armor(string Name, int Hp, int Att, int Price, int SPrice)
{
	ItemI.Item_Name = Name;
	ItemI.Item_Hp = Hp;
	ItemI.Item_Att = Att;

	ItemI.Item_Price = Price;
	ItemI._Item_Price = SPrice;
}

Armor::~Armor()
{
}


