#pragma once
#include "stdafx.h"

#define MAX_INVENTORY_SIZE 20

class CWeapon;
class CBufItem;
class CPotion;


//�κ��丮�� �� �ڷ��� �߰���, Finalize�Լ����� �κ��丮 �Ҵ������Ҷ� �� �ڷ����� ���� �����ؾ���.
class CInventory
{
private:
	//���ǰ���
	CPotion* potions[MAX_INVENTORY_SIZE];
	int potionIndex;
	//���Ⱑ��
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
	//�κ��丮�� �� �׸� ���� ������ �ε����� ��ȿ�� �ε������� �˻��Ѵ�.
	//_index : �κ��丮�� �׸� ���� �ε���, _factor: �˻��� �ε���
	bool isVaildIndex(int _invenIndex, int _factor);
	bool isFull(int _invenIndex);

	
	
};
