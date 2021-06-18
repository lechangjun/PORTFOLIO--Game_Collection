#include "stdafx.h"
#include "Bufitem.h"
#include "Parser.h"

CBufItem::CBufItem()
{
	id = 0;
	strcpy_s(GFX_PATH, ITEM_NAME_LENGTH, "");
	strcpy_s(name, ITEM_NAME_LENGTH, "");
	attackBuf = 0;
	maxHealthBuf = 0;
	levelBuf = 0;
	expBuf = 0;
	element = ELEMENT_END;
	isConsumable = false;
	strcpy_s(description, ITEM_NAME_LENGTH, "");
	dropChance = .0f;
	price = 0;

}

CBufItem::~CBufItem()
{
}

void CBufItem::PrintGemInfo() const
{
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << "�̸�: " << name << endl;
	cout << "���ݷ�: " << attackBuf << endl;
	cout << "�ִ�ü��: " << maxHealthBuf << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "�Ӽ�: " << arr << endl;
	cout << "��ġ: " << price << endl;
	cout << description << endl;


}