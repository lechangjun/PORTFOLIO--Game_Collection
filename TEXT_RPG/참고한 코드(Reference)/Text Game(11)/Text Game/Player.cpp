#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::NickName(string P_Name)
{
	cout << "이름을 정하시오. : ";
	cin >> P_Name;
	Name = P_Name;
}

void Player::Profile()
{
	if (P_HP > P_MAXHP)
	{
		P_HP = P_MAXHP;
	}
	if (P_HP <= 0)
	{
		P_HP = 0;
	}

	cout << ":: 플레이어 "<< Name << " ::" << endl;
	cout << "체력: " << this->GetP_MAXHP() << "/" << this->GetP_HP() << endl;
	cout << "공격력: " << this->GetP_ATT() << endl;
	cout << "==================================" << endl;
}

void Player::Show_P_Inventory()
{
	system("cls");

	cout << ":: 인벤토리 ::" << endl;
	cout << "보유 금액: " << Get_GOLD() << "G" << endl;
	cout << "착용 중:";
	if (Set_Item1 != 0)
	{
		cout << "[강철 검]";
	}
	if (Set_Item2 != 0)
	{
		cout << "[강철 갑옷]";
	}
	cout << endl;
	cout << "==================================" << endl;
}

void Player::Damage(int val)
{
	P_HP -= val;
}

void Player::Rest(int val)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		val = rand() % 10 + 1;
	}

	cout << "플레이어는 휴식을 취해 " << val << "만큼의 체력을 회복했다." << endl;
	P_HP += val;
}

void Player::PlusGold(int val)
{
	srand(size_t(time(NULL)));
	for (int i = 0; i < 10; i++)
	{
		val = rand() % 100 + 1;
	}

	GOLD += val;

	cout << "플레이어 " << Name << "은(는) " << val << "G를 손에 넣었다." << endl;
}

void Player::PayGold(int val)
{
	GOLD -= val;
}

void Player::ReceiveGold(int val)
{
	GOLD += val;
}

void Player::Att_Plus(int val)
{
	P_ATT += val;
	Set_Item1 = 1;
}

void Player::Att_Return(int val)
{
	P_ATT -= val;
	Set_Item1 = 0;
}

void Player::M_HP_Plus(int val)
{
	P_MAXHP += val;
	P_HP += val;
	Set_Item2 = 1;
}

void Player::HP_Heal(int val)
{
	P_HP += val;
}