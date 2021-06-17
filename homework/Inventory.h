#pragma once
#include "stdafx.h"

#define MAX_INVENTORY_SIZE 20

class CWeapon;
class CBufItem;
class CPotion;


//인벤토리에 들어갈 자료형 추가시, Finalize함수에서 인벤토리 할당해제할때 그 자료형도 같이 해제해야함.
class CInventory
{
private:
	//포션가방
	CPotion* potions[MAX_INVENTORY_SIZE];
	int potionIndex;
	//무기가방
	CWeapon* weapons[MAX_INVENTORY_SIZE];
	int weaponIndex;
	CBufItem* gems[MAX_INVENTORY_SIZE];
	int gemIndex;
public:
	CWeapon* currWeapon;
public:
	CInventory();
	~CInventory();
	int GetInventorySize();
	CPotion* GetPotion(int _index);
	CWeapon* GetWeapon(int _index);
	CBufItem* GetGem(int _index);
	void DeletePotion(int _index);
	void DeleteWeapon(int _index);
	void DeleteGem(int _index);
	void InsertPotion(CPotion* _potion);
	void InsertWeapon(CWeapon* _weapon);
	void InsertGem(CBufItem* bufItem);
	int GetPotionSize()const;
	int GetWeaponSize()const;
	int GetGemSize()const;
	bool isPotionEmpty();
	bool isWeaponEmpty();
	bool isGemEmpty();
private:
	//인벤토리의 각 항목에 대해 참조할 인덱스가 유효한 인덱스인지 검사한다.
	//_index : 인벤토리의 항목에 대한 인덱스, _factor: 검사할 인덱스
	bool isVaildIndex(int _invenIndex, int _factor);
	bool isFull(int _invenIndex);

	
	
};
