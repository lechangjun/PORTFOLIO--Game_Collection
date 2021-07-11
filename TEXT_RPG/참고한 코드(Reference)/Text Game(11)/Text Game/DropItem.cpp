#include "stdafx.h"
#include "DropItem.h"

DropItem::DropItem()
{
}

DropItem::DropItem(DropItem* D)
{
	ItemI.Item_Name = D->ItemI.Item_Name;

	ItemI._Item_Price = D->ItemI._Item_Price;
}

DropItem::DropItem(string Name, int SPrice)
{
	ItemI.Item_Name = Name;

	ItemI._Item_Price = SPrice;
}

DropItem::~DropItem()
{
}
