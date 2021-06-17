#include "stdafx.h"
#include "Weapon.h"
#include "Parser.h"
#include "BufItem.h"

CWeapon::CWeapon()
{
	id = 0;
	strcpy_s(GFX_PATH, ITEM_NAME_LENGTH, "");
	strcpy_s(name, ITEM_NAME_LENGTH, "�Ǽ�");
	strcpy_s(description, ITEM_NAME_LENGTH, "");
	price = 0;
	attack = 0;
	level = 1;
	occupation = OCCUPATION_END;
	element = ELEMENT_END;
	gem = new CBufItem; 
}

CWeapon::~CWeapon()
{
	//cout << "���� �Ҹ��� ȣ��!" << endl;
	//system("pause");
	if (gem)
	{
		delete gem;
	}
}

void CWeapon::printWeaponInfo() const
{
	if (0 == id)
	{
		cout << "�Ǽ�" << endl;
		return;
	}

	cout << "\n\n";
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << name << '\n';
	cout << "����: " << attack << '\n';
	cout << description << '\n';
	cout << "����: " << price << '\n';
	char arr[16] = "";
	parser.OccupationToString(occupation, arr);
	cout << "����: " << occupation << '\n';
	char arr2[16] = "";
	parser.ElementToString(element, arr2);
	cout << "�Ӽ�: " << arr2 << endl;
	cout << "��: " << gem->name << endl;
	cout << '\n' << "==========================================================================================" << endl;
}


void CWeapon::EnhanceWeapon()
{
	//0~99������ �Ǽ� ����.
	float random = (rand() / (float)RAND_MAX) * 99.f;

	//���� 1�϶� �⺻ Ȯ��
	float chance = BASE_ENHANCE_CHANCE;

	//�������� 5.2�踸ŭ Ȯ�� �϶�
	chance -= level * 5.2f;




	if (chance >= random)
	{
		system("cls");
		cout << "��ȭ�� �����߽��ϴ�!" << endl;
		cout << "<��ȭ ��>" << endl;
		printWeaponInfo();
		float weight = level / 3.f;
		weight = weight < 1 ? weight = 1 : weight;
		level += 1;
		attack += int(6 * weight);
		price += int(30 * weight);
		cout << "<��ȭ ��>" << endl;
		printWeaponInfo();
		system("pause");
	}
	else
	{
		cout << "��ȭ ����!" << endl;
		system("pause");
	}



}