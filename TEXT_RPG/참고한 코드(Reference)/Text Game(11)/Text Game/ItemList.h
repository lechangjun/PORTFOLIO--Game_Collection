#pragma once
#include"stdafx.h"
#include"Weapon.h"
#include"Armor.h"
#include"Potion.h"
#include"DropItem.h"

struct ItemList
{
	Weapon* IronSword = new Weapon{ "��ö ��",0,10,200,140 };

	Armor* IronArmor = new Armor{ "��ö ����",20,0,300,210 };

	Potion* HpPotion = new Potion{ "Hp ȸ�� ����",20,0,100,70 };
	Potion* AttPorion = new Potion{ "���ݷ� ���� ����",0,20,100,70 };

	DropItem* Item1 = new DropItem{ "������ ����",50 };
	DropItem* Item2 = new DropItem{ "���� �� ����",70 };
	DropItem* Item3 = new DropItem{ "���̷����� ������",100 };
};
