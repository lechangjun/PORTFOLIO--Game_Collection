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
		strcpy_s(name, "����");
		attack = 10;
		maxHealth = 200;
		maxExp = 50;
		occupation = WARRIOR;
		break;
	case 2:
		strcpy_s(name, "������");
		attack = 15;
		maxHealth = 80;
		maxExp = 50;
		occupation = WIZARD;
		break;
	case 3:
		strcpy_s(name, "����");
		attack = 7;
		maxHealth = 150;
		maxExp = 50;
		occupation = THIEF;
		break;
	default:
		cout << "�߸��� �Է��Դϴ�." << endl;
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
	cout << "����: " << name << endl;
	cout << "����: " << level << endl;
	cout << "���ݷ�: " << attack << "(+" << inventory->currWeapon->attack << ")" << endl;
	cout << "ü��: " << currHealth << " / " << maxHealth << endl;
	cout << "����ġ: " << currExp << " / " << maxExp << endl;
	cout << "���: " << gold << endl;
	char element[16] = "";
	CParser parser;
	parser.ElementToString(inventory->currWeapon->element, element);
	cout << "���: " << inventory->currWeapon->name << "(" << element << ")" << endl;

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

