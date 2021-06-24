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
	cout << "이름: " << name << endl;
	cout << "공격력: " << attack << endl;
	cout << "체력: " << currHealth << " / " << maxHealth << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "속성: " << arr << endl;


}
