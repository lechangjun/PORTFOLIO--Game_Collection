#pragma once
#include "stdafx.h"

class CMonster
{
public:
	// 1���� ����
	int id;
	char name[ITEM_NAME_LENGTH];
	char GFX_PATH[GFX_PATH_LENGTH];
	int attack;
	int maxHealth;
	int currHealth;
	int exp;
	int gold;
	//������
	HABITAT habitat;
	float spawnChance;
	ELEMENT element;

public:
	CMonster();
	~CMonster();
	void PrintMonster() const;
	
};
