#pragma once
#include "stdafx.h"
#include "ItemList.h"

class Store
{
private:
	ItemList* _SItemList;
public:
	Store();
	~Store();

	void Show_Store();

	void Show_Equip();
	void Show_Potion();
};
