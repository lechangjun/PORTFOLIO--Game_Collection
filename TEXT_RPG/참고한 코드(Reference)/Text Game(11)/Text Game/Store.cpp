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
	cout << ":: ���� ::" << endl;
	cout << endl;

	cout << "������ �Ͻðڽ��ϱ�?" << endl;
	cout << "[1]: ����, [2]: �Ǹ�, [0]: ���� ȭ������" << endl;
	cout << ">> ";
}

void Store::Show_Equip()
{
	cout << ":: ��� ::" << endl;
	cout << endl;

	cout << "[1]: " << _SItemList->IronSword->Get_WeaponName() <<"(���ݷ� + 10)\t"<< _SItemList->IronSword->Get_WeaponPrice()<<"G"<< endl;
	cout << "[2]: " << _SItemList->IronArmor->Get_ArmorName()<< "(ü�� + 20)\t" << _SItemList->IronArmor->Get_ArmorPrice() << "G" << endl;
	cout << "[3]: ---" << endl;
	cout << "[0]: ���� ȭ������" << endl;
	cout << endl;

	cout << "� ��� �����Ͻðڽ��ϱ�?" << endl;
	cout << ">> ";
}

void Store::Show_Potion()
{
	cout << ":: ���� ::" << endl;
	cout << endl;

	cout << "[1]: " << _SItemList->HpPotion->Get_PotionName() << "(ü�� ȸ�� + 20)\t" << _SItemList->HpPotion->Get_PotionPrice() << "G" << endl;
	cout << "[2]: " << _SItemList->AttPorion->Get_PotionName() << "(���ݷ� ���� + 20)\t" << _SItemList->AttPorion->Get_PotionPrice() << "G" << endl;
	cout << "[3]: ---" << endl;
	cout << "[0]: ���� ȭ������" << endl;
	cout << endl;

	cout << "� ������ �����Ͻðڽ��ϱ�?" << endl;
	cout << ">> ";
}