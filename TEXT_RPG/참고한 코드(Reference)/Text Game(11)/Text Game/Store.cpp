#include "stdafx.h"
#include "Store.h"

Store::Store()
{
	_SItemList = new ItemList;
}

Store::~Store()
{
	delete _SItemList;
}

void Store::Show_Store()
{
	cout << ":: 상점 ::" << endl;
	cout << endl;

	cout << "무엇을 하시겠습니까?" << endl;
	cout << "[1]: 구입, [2]: 판매, [0]: 메인 화면으로" << endl;
	cout << ">> ";
}

void Store::Show_Equip()
{
	cout << ":: 장비 ::" << endl;
	cout << endl;

	cout << "[1]: " << _SItemList->IronSword->Get_WeaponName() <<"(공격력 + 10)\t"<< _SItemList->IronSword->Get_WeaponPrice()<<"G"<< endl;
	cout << "[2]: " << _SItemList->IronArmor->Get_ArmorName()<< "(체력 + 20)\t" << _SItemList->IronArmor->Get_ArmorPrice() << "G" << endl;
	cout << "[3]: ---" << endl;
	cout << "[0]: 이전 화면으로" << endl;
	cout << endl;

	cout << "어떤 장비를 구입하시겠습니까?" << endl;
	cout << ">> ";
}

void Store::Show_Potion()
{
	cout << ":: 포션 ::" << endl;
	cout << endl;

	cout << "[1]: " << _SItemList->HpPotion->Get_PotionName() << "(체력 회복 + 20)\t" << _SItemList->HpPotion->Get_PotionPrice() << "G" << endl;
	cout << "[2]: " << _SItemList->AttPorion->Get_PotionName() << "(공격력 증가 + 20)\t" << _SItemList->AttPorion->Get_PotionPrice() << "G" << endl;
	cout << "[3]: ---" << endl;
	cout << "[0]: 이전 화면으로" << endl;
	cout << endl;

	cout << "어떤 포션을 구입하시겠습니까?" << endl;
	cout << ">> ";
}