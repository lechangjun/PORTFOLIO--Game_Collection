#pragma once
#include "stdafx.h"

class CPotion
{
public:
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int healAmount;
	char description[DESCRIPTION_LENGTH];
	int price;

public:

	void printPotionInfo() const;
};
