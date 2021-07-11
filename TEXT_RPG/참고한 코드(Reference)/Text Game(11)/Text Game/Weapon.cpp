#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(Weapon* W)
{
	ItemI.Item_Name = W->ItemI.Item_Name;
	ItemI.Item_Hp = W->ItemI.Item_Hp;
	ItemI.Item_Att = W->ItemI.Item_Att;

	ItemI.Item_Price = W->ItemI.Item_Price;
	ItemI._Item_Price = W->ItemI._Item_Price;
}

Weapon::Weapon(string Name, int Hp, int Att, int Price, int SPrice)
{
	ItemI.Item_Name = Name;
	ItemI.Item_Hp = Hp;
	ItemI.Item_Att = Att;

	ItemI.Item_Price = Price;
	ItemI._Item_Price = SPrice;
}

Weapon::~Weapon()
{
}
