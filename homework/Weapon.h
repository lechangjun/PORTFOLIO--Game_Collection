#pragma once

#include "stdafx.h"

class CBufItem;

class CWeapon
{
public:
	//아이템 아이디(1부터 시작) 0은 맨손
	int id;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	int attack;
	//아이템 설명. 
	char description[DESCRIPTION_LENGTH];
	int price;
	//직업
	OCCUPATION  occupation;
	//강화레벨
	int level;
	//아이템의 속성
	ELEMENT element;
	//부착된 젬
	CBufItem* gem; // 만약 Cweapon의 복사본이 이 주소도 가져갔고, 그 복사본이 지워지면 복사본은 원본의 Gem과 똑같은 주소를 가리키고 있기때문에 Gem이 사라짐.
public:
	CWeapon();
	~CWeapon();
	void printWeaponInfo() const;
	void CWeapon::EnhanceWeapon();
	




};