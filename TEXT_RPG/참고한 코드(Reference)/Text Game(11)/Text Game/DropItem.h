#pragma once
#include "stdafx.h"
#include "Item.h"

class DropItem : public Item
{
private:
public:
	DropItem();
	DropItem(DropItem* D);
	DropItem(string Name, int Price);
	~DropItem();

	string Get_DropName() { return ItemI.Item_Name; }
	int Get_DropPrice() { return ItemI._Item_Price; }
};
