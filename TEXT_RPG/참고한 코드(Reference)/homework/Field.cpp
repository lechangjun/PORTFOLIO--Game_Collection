#include "stdafx.h"
#include "Field.h"
#include "Monster.h"
#include "Character.h"
#include "Bufitem.h"
#include "Factory.h"
#include "Inventory.h"
#include "Weapon.h"


CField::CField(CCharacter* _player, CFactory* _factory)
{
	m_pCharacter = _player;
	m_pFactory = _factory;
}


CField::~CField()
{
}

void CField::Process()
{
	int iSelect = 0;

	while (true)
	{
		system("cls");
		cout << "  __________________________________________   " << endl;
		cout << "<| ======           Dungeon          ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		m_pCharacter->PrintCharacter();
		cout << "1.�ʱ� 2.�߱� 3.��� 4.������" << endl;
		cout << "===================================================" << endl;
		cout << "�Է�: ";

		//��� �� ���ΰ�?
		int destiantion;
		cin >> destiantion;

		//������
		if (4 == destiantion)
			return;
		if (1 <= destiantion && 3 >= destiantion)
			EnterDungeon((HABITAT)destiantion);
	}
}




void CField::EnterDungeon(HABITAT habitat)
{

	CMonster* monster = m_pFactory->CreateMonster(habitat);

	COMBAT combat = Combat(m_pCharacter, monster);
	//����
	if (COMBAR_RUN == combat)
	{
		m_pCharacter->currExp -= monster->exp;
		m_pCharacter->gold -= monster->gold;
		m_pCharacter->currExp = m_pCharacter->currExp < 0 ? 0 : m_pCharacter->currExp;
		m_pCharacter->gold = m_pCharacter->gold < 0 ? 0 : m_pCharacter->gold;
		delete monster;
	}
	//�̱�
	else if (COMBAT_WIN == combat)
	{

		m_pCharacter->currExp += monster->exp;
		m_pCharacter->gold += monster->gold;
		m_pCharacter->OnGetExp();
		cout << "��ɿ� �����߽��ϴ�!" << '\n' << monster->gold << " ��带 ������ϴ�." << endl;
		cout << monster->exp << "��ŭ�� ����ġ�� ������ϴ�!" << endl;

		//������ ���. ��� ���ʹ� 30������ Ȯ���� �������� ����Ѵ�.
		int random = rand() % 100;
		int dropChance = 30;
		if (random <= dropChance)
		{

			CBufItem* dropItem = m_pFactory->CreateDropItem();
			m_pCharacter->inventory->InsertGem(dropItem);
			cout << dropItem->name << "��(��) ������ϴ�!" << endl;
		}



		delete monster;
		monster = nullptr;

		system("pause");
	}
	//��
	else if (combat == COMBAT_LOSE)
	{
		cout << "�÷��̾� ���!" << endl;
		m_pCharacter->currHealth = m_pCharacter->maxHealth;
		m_pCharacter->currExp >>= 1;
		m_pCharacter->gold >>= 1;
		m_pCharacter->currHealth = m_pCharacter->currHealth < 0 ? 0 : m_pCharacter->currHealth;
		m_pCharacter->currExp = m_pCharacter->currExp < 0 ? 0 : m_pCharacter->currExp;
		m_pCharacter->gold = m_pCharacter->gold < 0 ? 0 : m_pCharacter->gold;


		system("pause");
	}

}



COMBAT CField::Combat(CCharacter* character, CMonster* monster)
{
	while (true)
	{
		system("cls");
		character->PrintCharacter();
		cout << " " << endl;
		cout << "           /\\                            " << endl;
		cout << " _         )( ___________________________      " << endl;
		cout << "(_)///////(**)_______Fight!!!____________>     " << endl;
		cout << "           )(                          " << endl;
		cout << "           \\/                            " << endl;
		cout << " " << endl;
		cout << "================================================" << endl;

		monster->PrintMonster();

		cout << "================================================" << endl;
		cout << "1. ���� 2. ����" << endl;

		int iSelect_Behavior;
		cin >> iSelect_Behavior;

		if (2 == iSelect_Behavior)
		{
			return COMBAR_RUN;
		}

		ELEMENT element = character->inventory->currWeapon->element;

		int characterAttack = character->attack;
		int monsterAttack = monster->attack;

		if (ELEMENT_END != element)
		{
			int result = element - monster->element;

			//�� Ȯ��

			if (1 == result || -3 == result)
			{
				//��
				characterAttack *= 2;
			}
			else if (-1 == result || 3 == result)
			{
				//��
				monsterAttack *= 2;
			}
		}

		monster->currHealth -= characterAttack;
		character->currHealth -= monsterAttack;

		if (monster->currHealth <= 0)
		{
			return COMBAT_WIN;
		}
		if (character->currHealth <= 0)
		{
			return COMBAT_LOSE;
		}
	}

}


