#include "stdafx.h"
#include "BattleField.h"
#include "Character.h"
#include "Enemy.h"


BattleField::BattleField()
{
	GameStart();
}

BattleField::~BattleField()
{

}

void BattleField::GameStart()
{
	cout << "선택해" << endl;

	cout << "1.상점" << endl;
	cout << "2.필드" << endl;
	cout << "3.병원" << endl;

	cin >> select;

	switch (select)
	{
		case 1 :
			Store();
			break;
		case 2:
			Field();
			break;
		case 3:
			Hospital();
			break;

		default:
			break;
	}

}

void BattleField::Store()
{
	cout << "상점";
}

void BattleField::Field()
{
	cout << "필드";
}

void BattleField::Hospital()
{
	cout << "병원";
}
