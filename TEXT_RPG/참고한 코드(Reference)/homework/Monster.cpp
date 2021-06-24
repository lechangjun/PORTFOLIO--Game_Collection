#include "stdafx.h"
#include "Monster.h"
#include "Parser.h"

CMonster::CMonster()
{
	id = 0;
	strcpy_s(name, ITEM_NAME_LENGTH, "");
	strcpy_s(GFX_PATH, ITEM_NAME_LENGTH, "");
	attack = 0;
	maxHealth = 0;
	currHealth = 0;
	exp = 0;
	gold = 0;
	habitat = HABITAT_END;
	spawnChance = 0;
	element = ELEMENT_END;

}

CMonster::~CMonster()
{
}

void CMonster::PrintMonster() const {

	CParser parser;
	if (strcmp(GFX_PATH, "") != 0)
		parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << "�̸�: " << name << endl;
	cout << "���ݷ�: " << attack << endl;
	cout << "ü��: " << currHealth << " / " << maxHealth << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "�Ӽ�: " << arr << endl;


}
