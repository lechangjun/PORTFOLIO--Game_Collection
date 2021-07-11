#pragma once
#include"stdafx.h"
#include"Weapon.h"
#include"Armor.h"
#include"Potion.h"
#include"DropItem.h"

struct ItemList
{
	Weapon* IronSword = new Weapon{ "°­Ã¶ °Ë",0,10,200,140 };

	Armor* IronArmor = new Armor{ "°­Ã¶ °©¿Ê",20,0,300,210 };

	Potion* HpPotion = new Potion{ "Hp È¸º¹ Æ÷¼Ç",20,0,100,70 };
	Potion* AttPorion = new Potion{ "°ø°Ý·Â Áõ°¡ Æ÷¼Ç",0,20,100,70 };

	DropItem* Item1 = new DropItem{ "µéÁãÀÇ ²¿¸®",50 };
	DropItem* Item2 = new DropItem{ "°ñ·½ÀÇ µ¹ Á¶°¢",70 };
	DropItem* Item3 = new DropItem{ "½ºÄÌ·¹ÅæÀÇ »ÄÁ¶°¢",100 };
};
