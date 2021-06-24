#pragma once
#include "stdafx.h"

class CInventory;
class CCharacter
{

public:
	char name[16];
	int attack;
	int maxHealth;
	int currHealth;
	int level;
	int maxExp;
	int currExp;
	int gold;
	CInventory* inventory;
	OCCUPATION  occupation;

public:

	CCharacter();
	~CCharacter();

	void CreateCharacter(int selection);

	void PrintCharacter() const;

	void LevelUp();

	void OnGetExp();

	CCharacter* Load();

	void Save(CCharacter* character);
	

};