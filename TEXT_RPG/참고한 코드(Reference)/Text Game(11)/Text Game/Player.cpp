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
	cout << "�̸��� ���Ͻÿ�. : ";
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

	cout << ":: �÷��̾� "<< Name << " ::" << endl;
	cout << "ü��: " << this->GetP_MAXHP() << "/" << this->GetP_HP() << endl;
	cout << "���ݷ�: " << this->GetP_ATT() << endl;
	cout << "==================================" << endl;
}

void Player::Show_P_Inventory()
{
	system("cls");

	cout << ":: �κ��丮 ::" << endl;
	cout << "���� �ݾ�: " << Get_GOLD() << "G" << endl;
	cout << "���� ��:";
	if (Set_Item1 != 0)
	{
		cout << "[��ö ��]";
	}
	if (Set_Item2 != 0)
	{
		cout << "[��ö ����]";
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

	cout << "�÷��̾�� �޽��� ���� " << val << "��ŭ�� ü���� ȸ���ߴ�." << endl;
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

	cout << "�÷��̾� " << Name << "��(��) " << val << "G�� �տ� �־���." << endl;
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