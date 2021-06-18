#pragma once

#include "stdafx.h"


class CMonster;
class CPotion;
class CWeapon;
class CBufItem;

class CFactory
{
private:
	CMonster* monsters = nullptr;
	int monsterCnt = 0;
	CPotion* potions = nullptr;
	int potionCnt = 0;
	CWeapon* weapons = nullptr;
	int weaponCnt = 0;
	CBufItem* bufItems = nullptr;
	int bufItemCnt = 0;

public:

	CFactory();

	~CFactory();

	const CWeapon* const  GetWeapons() const;

	const CMonster* const GetMonsters() const;

	const CPotion* const GetPotions() const;

	const CBufItem* const GetBufitems() const;

	int GetWeaponsSize() const;

	int GetMonstersSize() const;

	int GetPotionsSize() const;

	int GetBufItemsSize() const;

	CWeapon* CreateWeapon(int id);


	CMonster* CreateMonster(int id);


	CMonster* CreateMonster(HABITAT habitat);

	CPotion* CreatePotion(int id);


	CBufItem* CreateBufItem(int id);


	CBufItem* CreateDropItem();





private:

	int GetInfo(char(**items)[CHAR_PER_LINE], char path[30]);

	void CreateAllWeapons();

	void CreateAllMonsters();

	void CreateAllPotions();

	void CreateAllbufItems();

	void Release();




};
