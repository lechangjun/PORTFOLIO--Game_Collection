#pragma once

#include "stdafx.h"

class CBufItem;

class CWeapon
{
public:
	//������ ���̵�(1���� ����) 0�� �Ǽ�
	int id;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int attack;
	//������ ����. 
	char description[DESCRIPTION_LENGTH];
	int price;
	//����
	OCCUPATION  occupation;
	//��ȭ����
	int level;
	//�������� �Ӽ�
	ELEMENT element;
	//������ ��
	CBufItem* gem; // ���� Cweapon�� ���纻�� �� �ּҵ� ��������, �� ���纻�� �������� ���纻�� ������ Gem�� �Ȱ��� �ּҸ� ����Ű�� �ֱ⶧���� Gem�� �����.
public:
	CWeapon();
	~CWeapon();
	void printWeaponInfo() const;
	void CWeapon::EnhanceWeapon();
	




};