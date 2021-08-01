#include "stdafx.h"
#include "Character.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Parser.h"

CCharacter::CCharacter()
{
	inventory = new CInventory;
}

CCharacter::~CCharacter()
{
	if (inventory)
	{
		delete inventory;

	}

}

void CCharacter::CreateCharacter(int selection)
{
	switch (selection)
	{
	case 1:
		strcpy_s(name, "전사");
		attack = 10;
		maxHealth = 200;
		maxExp = 50;
		occupation = WARRIOR;
		break;
	case 2:
		strcpy_s(name, "마법사");
		attack = 15;
		maxHealth = 80;
		maxExp = 50;
		occupation = WIZARD;
		break;
	case 3:
		strcpy_s(name, "도적");
		attack = 7;
		maxHealth = 150;
		maxExp = 50;
		occupation = THIEF;
		break;
	default:
		cout << "잘못된 입력입니다." << endl;
		return;
	}

	currHealth = maxHealth;
	currExp = 0;
	gold = 0;
	level = 1;

}

void CCharacter::PrintCharacter() const
{
	cout << "  __________________________________________   " << endl;
	cout << "<| ======         Player Info        ====== |>" << endl;
	cout << "<|__________________________________________|> " << endl;
	cout << " " << endl;
	cout << "직업: " << name << endl;
	cout << "레벨: " << level << endl;
	cout << "공격력: " << attack << "(+" << inventory->currWeapon->attack << ")" << endl;
	cout << "체력: " << currHealth << " / " << maxHealth << endl;
	cout << "경험치: " << currExp << " / " << maxExp << endl;
	cout << "골드: " << gold << endl;
	char element[16] = "";
	CParser parser;
	parser.ElementToString(inventory->currWeapon->element, element);
	cout << "장비: " << inventory->currWeapon->name << "(" << element << ")" << endl;

}

void CCharacter::LevelUp()
{

	float weight = level / 3.f;
	weight = weight < 1 ? weight = 1 : weight;

	level += (int)1;
	maxHealth += (int)(20 * weight);
	currHealth = maxHealth;
	attack += (int)(5 * weight);
	maxExp += (int)(20 * weight);
	currExp = 0;

}

void CCharacter::OnGetExp()
{
	if (currExp >= maxExp)
	{
		LevelUp();
	}
}

