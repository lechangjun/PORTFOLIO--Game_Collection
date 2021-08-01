#include "stdafx.h"
#include "MainGame.h"
#include <time.h>
#include "Character.h"
#include "Factory.h"
#include "InventoryMgr.h"
#include "Inventory.h"
#include "Monster.h"
#include "Potion.h"
#include "Weapon.h"
#include "Bufitem.h"
#include "Field.h"




CMainGame::CMainGame()
{
	m_pCharacter = nullptr;
	m_pFactory = new CFactory;
}

CMainGame::~CMainGame()
{
	Release();
}


bool CMainGame::SelectPlayer()
{

	srand(unsigned(time(NULL)));

	//ĳ���� ����ȭ��
	while (true)
	{
		CParser parser;
		system("cls");
		//�ΰ� ���
		parser.PrintFile("../GFX/logo.txt");
		cout << " " << endl;
		cout << "           /\\                            " << endl;
		cout << " _         )( ___________________________      " << endl;
		cout << "(_)///////(**)___________________________>     " << endl;
		cout << "           )(                          " << endl;
		cout << "           \\/                            " << endl;
		cout << " " << endl;
		cout << "  __________________________________________   " << endl;
		cout << "<| ========       WHAT JOBS        ======== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "(0): [EXIT] ������." << endl;
		cout << "(1): [View] ����." << endl;
		cout << "(2): [View] ������." << endl;
		cout << "(3): [View] ����." << endl;
		cout << "(4): [View] �ε�." << endl;
		cout << " " << endl;
		cout << "---------------------------------------------" << endl;
		cout << " " << endl;


		int characterToCreate;
		cin >> characterToCreate;

		//����
		if (characterToCreate == 0)
		{
			_CrtDumpMemoryLeaks(); // �޸𸮴��� üũ(������)
			return false;
		}
		//���̺� �����ͷε�
		if (characterToCreate == 4)
		{
			Load();
			
			return true;

			if (m_pCharacter == nullptr)
			{	
				return false;
			}
		}
		else
		{
			//ĳ���ʹ� ���ý� �ѹ� ����
			m_pCharacter = new CCharacter;
			(*m_pCharacter).CreateCharacter(characterToCreate);
			return true;

		}

	}
	return false;
}

void CMainGame::Progress()
{

	//�÷��̾ �������� �ʾҴٸ� ����.
	if (!SelectPlayer())
		return;

	m_pCharacter->gold = 3000;

	//�κ��丮 �Ŵ��� �ʱ�ȭ
	m_pInventoryMgr = new CInventoryMgr(m_pCharacter);
	//�ʵ� �ʱ�ȭ
	m_pField = new CField(m_pCharacter, m_pFactory);
	

	//ĳ������ �ൿ���� ȭ��
	while (true)
	{

		system("cls");
		//ĳ���� ���� ���
		m_pCharacter->PrintCharacter();
		cout << "  __________________________________________   " << endl;
		cout << "<| ========        Main Menu       ======== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "(0): [EXIT] ������." << endl;
		cout << "(1): [view] ���� ����." << endl;
		cout << "(2): [View] ���尣." << endl;
		cout << "(3): [View] �޽�ó." << endl;
		cout << "(4): [View] �κ��丮." << endl;
		cout << "(5): [SAVE] ���̺�." << endl;
		cout << "(6): [View] ���� -> �̿ϼ�" << endl;
		cout << "================================================" << endl;



		//��� �� ���ΰ�?
		int destiantion;
		cin >> destiantion;


		if (destiantion == 0)
		{
			_CrtDumpMemoryLeaks(); // �޸𸮴��� üũ(������)
			return;
		}
		//��������
		else if (1 == destiantion)
		{
			m_pField->Process();
		}

		//���尣 ����
		else if (2 == destiantion)
		{
			EnterForge();
		}
		//������ ����
		else if (3 == destiantion)
		{
			EnterPharmacy();
		}
		//�κ��丮 ����
		else if (4 == destiantion)
		{
			m_pInventoryMgr->Process();
		}
		//���̺�
		else if (5 == destiantion)
		{
			Save();
		}
		else
			cout << "�߸��� �Է��Դϴ�" << endl;

	}
}


void CMainGame::Release()
{
	if(m_pCharacter)
		delete m_pCharacter;
	if(m_pFactory)
		delete m_pFactory;
	if(m_pInventoryMgr)
		delete m_pInventoryMgr;
	if (m_pField)
		delete m_pField;

	cout << "������ �����մϴ�." << endl;
}


void CMainGame::EnterPharmacy()
{


	while (true)
	{
		system("cls");
		cout << "���� ���� ��������!" << endl;
		cout << "\n\n\n";

		int potionCnt = m_pFactory->GetPotionsSize();
		const CPotion* potions = m_pFactory->GetPotions();

		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			potions[i].printPotionInfo();
		}

		cout << "�ܾ�: " << m_pCharacter->gold << endl;
		cout << "\n\n";
		cout << "0. ������" << endl;
		int itemSelect = 0;
		cin >> itemSelect;

		if (itemSelect == 0)
		{
			break;
		}
		if (itemSelect <0 || itemSelect > potionCnt)
		{
			cout << "�߸��� �Է��Դϴ�" << endl;
			system("pause");

		}
		//�߸��� �Է��� �ƴϸ�
		//1 1
		else
		{
			if (m_pCharacter->gold >= potions[itemSelect - 1].price)
			{
				CPotion* potion = m_pFactory->CreatePotion(itemSelect);
				//�÷��̾� �κ��丮�� ���ǳֱ�
				m_pCharacter->inventory->InsertPotion(potion);
				m_pCharacter->gold -= potion->price;
				cout << potion->name << "�� �����Ͽ����ϴ�!" << endl;
			}
			else
				cout << "���� �����մϴ�!" << endl;

			system("pause");
		}

	}

}

void CMainGame::EnterForge()
{



	while (true)
	{
		system("cls");

		cout << "�ְ��� ���Ⱑ ���ֽ��ϴ�." << endl;
		cout << "\n\n\n";

		int weaponsCount = m_pFactory->GetWeaponsSize();
		const CWeapon* const weapons = m_pFactory->GetWeapons();

		for (int i = 0; i < weaponsCount; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			weapons[i].printWeaponInfo();
		}

		cout << "�ܾ�: " << m_pCharacter->gold << endl;
		cout << "\n\n";
		cout << "0. ������ �׸��ȣ. �����ϱ� 999. ��ȭ�ϱ�" << '\n';
		int itemSelect = 0;
		cin >> itemSelect;

		if (0 == itemSelect)
		{
			break;
		}
		else if (999 == itemSelect)
		{
			EnhanceWeaponPage();

		}
		else if (itemSelect <0 || itemSelect > weaponsCount)
		{
			cout << "�߸��� �Է��Դϴ�" << endl;
			system("pause");

		}
		//�߸��� �Է��� �ƴϸ�
		else
		{
			//���� ������ ����
			//CWeapon weaponToBuy = weapons[itemSelect - 1];
			CWeapon* weaponToBuy = m_pFactory->CreateWeapon(itemSelect);


			if (m_pCharacter->occupation != weaponToBuy->occupation)
			{
				cout << "������ �� ���� Ŭ������ �����Դϴ�!" << endl;
				delete weaponToBuy;
				system("pause");
				continue;

			}
			else if (m_pCharacter->gold >= weaponToBuy->price)
			{

				cout << weaponToBuy->name << "��(��) �����Ͽ����ϴ�!" << endl;
				//�κ��丮�� �ִ´�.
				m_pCharacter->inventory->InsertWeapon(weaponToBuy);
				m_pCharacter->gold -= weaponToBuy->price;
			}
			else
			{
				delete weaponToBuy;
				cout << "���� �����մϴ�!" << endl;
			}

			system("pause");
		}


	}
}


void CMainGame::EnhanceWeaponPage()
{
	while (true)
	{

		system("cls");

		cout << "���� �κ��丮" << "\n\n";

		cout << "<������> " << endl;
		cout << "���������� ����� ��ȭ�� �Ұ��մϴ�." << endl;
		m_pCharacter->inventory->currWeapon->printWeaponInfo();
		cout << "\n\n";

		int weaponCnt = m_pCharacter->inventory->GetWeaponSize();
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			m_pCharacter->inventory->GetWeapon(i)->printWeaponInfo();
			cout << "��ȭȮ��: " << BASE_ENHANCE_CHANCE - (m_pCharacter->inventory->GetWeapon(i)->level * 5.2f) << endl;
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ��ȭ�ϱ�" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		//�׸� ��ȣ�� ����� �Է�������
		else if (selection <= m_pCharacter->inventory->GetWeaponSize())
		{
			//��ȭ��
			int cost = m_pCharacter->inventory->GetWeapon(selection-1)->price / 5;
			//���� ����ϸ�
			if (m_pCharacter->gold >= cost)
			{
				m_pCharacter->gold -= cost;
				//��ȭ�õ�
				m_pCharacter->inventory->GetWeapon(selection -1)->EnhanceWeapon();
			}
		}
	}
}



void CMainGame::Load()
{

	FILE* fp;
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "rb");
	if (0 == err)
	{
		CWeapon* weapon = new CWeapon;
		CCharacter* character = new CCharacter;
		//ĳ���� ���� �о����
		fread(character, sizeof(CCharacter), 1, fp);
		//�������� ��������
		fread(weapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		m_pCharacter = character;
		m_pCharacter->inventory->currWeapon = weapon;
		cout << "�ε� ����!" << endl;
		system("pause");


	}
	else
		cout << "�ε� ����! ������ ������ �� �����ϴ�." << endl;

}

void CMainGame::Save()
{
	FILE* fp;
	//���� ��Ʈ�� ����
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "wb");

	if (0 == err)
	{
		//ĳ���� ���� ����
		fwrite(m_pCharacter, sizeof(CCharacter), 1, fp);
		//�������� ����
		fwrite(m_pCharacter->inventory->currWeapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		cout << "���̺꼺��!" << endl;
		system("pause");
	}
	else
		cout << "���̺� ����! ������ ������ �� �����ϴ�." << endl;
}




