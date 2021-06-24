#include "stdafx.h"
#include "Weapon.h"
#include "Parser.h"
#include "BufItem.h"

CWeapon::CWeapon()
{
	id = 0;
	strcpy_s(GFX_PATH, ITEM_NAME_LENGTH, "");
	strcpy_s(name, ITEM_NAME_LENGTH, "맨손");
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
	//cout << "웨폰 소멸자 호출!" << endl;
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
		cout << "맨손" << endl;
		return;
	}

	cout << "\n\n";
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << name << '\n';
	cout << "공격: " << attack << '\n';
	cout << description << '\n';
	cout << "가격: " << price << '\n';
	char arr[16] = "";
	parser.OccupationToString(occupation, arr);
	cout << "직업: " << occupation << '\n';
	char arr2[16] = "";
	parser.ElementToString(element, arr2);
	cout << "속성: " << arr2 << endl;
	cout << "젬: " << gem->name << endl;
	cout << '\n' << "==========================================================================================" << endl;
}


void CWeapon::EnhanceWeapon()
{
	//0~99까지의 실수 난수.
	float random = (rand() / (float)RAND_MAX) * 99.f;

	//레벨 1일때 기본 확률
	float chance = BASE_ENHANCE_CHANCE;

	//레벨이의 5.2배만큼 확률 하락
	chance -= level * 5.2f;




	if (chance >= random)
	{
		system("cls");
		cout << "강화에 성공했습니다!" << endl;
		cout << "<강화 전>" << endl;
		printWeaponInfo();
		float weight = level / 3.f;
		weight = weight < 1 ? weight = 1 : weight;
		level += 1;
		attack += int(6 * weight);
		price += int(30 * weight);
		cout << "<강화 후>" << endl;
		printWeaponInfo();
		system("pause");
	}
	else
	{
		cout << "강화 실패!" << endl;
		system("pause");
	}



}