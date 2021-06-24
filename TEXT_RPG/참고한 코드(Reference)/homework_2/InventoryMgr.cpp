#include "stdafx.h"
#include "InventoryMgr.h"
#include "Character.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Bufitem.h"
#include "Potion.h"

CInventoryMgr::CInventoryMgr(CCharacter* _character)
{
	m_pCharacter = _character;
	m_pInventory = m_pCharacter->inventory;
}

CInventoryMgr::~CInventoryMgr()
{
	Release();
}

void CInventoryMgr::Process()
{
	ShowInventory();
}

void CInventoryMgr::Release()
{
	//��������� ĳ���Ϳ� �κ��丮 �ּ��� ���纻�̴� null�� ����� ���.
	m_pCharacter = nullptr;
	m_pInventory = nullptr;
}

void CInventoryMgr::ShowInventory()
{
	while (true)
	{
		system("cls");

		cout << "<������> " << endl;
		m_pCharacter->inventory->currWeapon->printWeaponInfo();

		cout << "  __________________________________________   " << endl;
		cout << "<| ======          Inventory         ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;


		cout << "0. ������ 1.���� 2.���� 3. �� " << endl;

		int whatBag = 0;
		cin >> whatBag;

		switch (whatBag)
		{
		case 0:
			return;
			break;
		case 1:
			ShowPotionBag();
			break;
		case 2:
			ShowWeaponBag();
			break;
		case 3:
			ShowGemBag();
			break;
		default:
			break;
		}



	}
}

void CInventoryMgr::ShowWeaponBag()
{
	while (true)
	{

		system("cls");


		cout << "<������> " << endl;
		m_pInventory->currWeapon->printWeaponInfo();
		cout << "\n\n";


		cout << "���� �κ��丮" << "\n\n";


		int weaponCnt = m_pInventory->GetWeaponSize();

		        
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			m_pInventory->GetWeapon(i)->printWeaponInfo();
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ��� 999.��������" << endl;
		unsigned int selection;
		cin >> selection;

		if (0 == selection)
		{
			return;
		}
		else if (999 == selection)
		{
			//���� ������� �κ��丮�� �ֱ�
			m_pInventory->InsertWeapon(m_pInventory->currWeapon);
			//��������
			m_pInventory->currWeapon = new CWeapon;
		}
		//selection 1 2 3 4 5
		//potion    0 1 2 3 4
		//�׸� ��ȣ�� ����� �Է�������
		else if (selection <= m_pInventory->GetWeaponSize())
		{
			cout << m_pInventory->GetWeapon(selection -1)->name<< "�� �����ߴ�!" << endl;
			system("pause");


			//�÷��̾ ���⸦ ���� �־��ٸ� �κ��丮�� �ִ´�.
			if (m_pInventory->currWeapon->id != 0)
			{
				m_pCharacter->attack -= m_pInventory->currWeapon->attack;
				m_pInventory->InsertWeapon(m_pInventory->currWeapon);
			}
			//�Ǽ��̾����� ��ü�� �ı��Ѵ�.
			else
			{
				delete m_pInventory->currWeapon;
				m_pInventory->currWeapon = nullptr;
			}

			//���⸦ �����Ѵ�.
			m_pInventory->currWeapon = m_pInventory->GetWeapon(selection - 1);
			m_pCharacter->attack += m_pInventory->currWeapon->attack;
			//������ ����� �κ��丮���� �����Ѵ�.
			m_pInventory->DeleteWeapon(selection - 1);



		}
	}
}

void CInventoryMgr::ShowPotionBag()
{
	while (true)
	{

		system("cls");

		cout << "���� �κ��丮" << "\n\n";

		int potionCnt = m_pInventory->GetPotionSize();
		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			m_pInventory->GetPotion(i)->printPotionInfo();
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ���" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		else if (selection <= m_pInventory->GetPotionSize())
		{
			if (m_pCharacter->currHealth >= m_pCharacter->maxHealth)
			{
				cout << "�̹� ü���� �� ���ֽ��ϴ�.";
				system("pause");
				continue;
			}

			cout << m_pInventory->GetPotion(selection -1)->name << "�� ����ߴ�!" << endl;
			system("pause");


			
			CPotion* potion = m_pInventory->GetPotion(selection - 1);
			//ĳ���� ü�� + ȸ������ �ִ�ü�º��� ������ �ִ�ü�±����� ä����. �ƴϸ� �׳� ������ ������ŭ ä��.
			int healAmount = ((m_pCharacter->currHealth + potion->healAmount) > m_pCharacter->maxHealth)
				? (m_pCharacter->maxHealth - m_pCharacter->currHealth) : potion->healAmount;
			//ü��ȸ��
			m_pCharacter->currHealth += healAmount;
			//���� �����
			delete potion;
			//�κ��丮 ���̱�
			m_pInventory->DeletePotion(selection - 1);
		}
	}
}

void CInventoryMgr::ShowGemBag()
{
	if (nullptr == m_pCharacter)
	{
		cout << "�κ��丮�� ���ʰ� �����ϴ�!" << endl;
		return;
	}

	while (true)
	{

		system("cls");

		cout << "���� ��" << "\n\n";

		int gemCount = m_pInventory->GetGemSize();
		for (int i = 0; i < gemCount; ++i)
		{
			cout << "<" << i + 1 << "��>" << endl;
			m_pInventory->GetGem(i)->PrintGemInfo();
			cout << "\n\n";
		}


		cout << "0. ������ �����۹�ȣ. ���" << endl;
		unsigned int gemSelection;
		cin >> gemSelection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == gemSelection)
		{
			return;
		}
		else if (gemSelection <= m_pInventory->GetGemSize())
		{
			//������ ���� ����ȭ��
			while (true)
			{
				system("cls");
				int weaponSize = m_pInventory->GetWeaponSize();
				if (0 == weaponSize)
				{
					cout << "���� �ɼ��� ������ �� ���� ���Ⱑ �����ϴ�. (�������� ����� �ɼ��� ������ �� �����ϴ�)" << endl;
					system("pause");
					break;
				}

				for (int i = 0; i < weaponSize; ++i)
				{
					cout << "<" << i + 1 << "��>" << endl;
					m_pInventory->GetWeapon(i)->printWeaponInfo();
					cout << "\n\n";
				}

				cout << "0. ������ �����۹�ȣ. ���" << endl;
				unsigned int weaponSelection;
				cin >> weaponSelection;

				if (0 == weaponSelection)
				{
					break;
				}
				else if (weaponSelection <= m_pInventory->GetWeaponSize())
				{
					//���⿡ �� �����ϱ�
					CWeapon* weapon = m_pInventory->GetWeapon(weaponSelection - 1);
					CBufItem* gem = m_pInventory->GetGem(gemSelection - 1);
					weapon->attack += gem->attackBuf;
					weapon->element = gem->element;
					m_pCharacter->maxHealth += gem->maxHealthBuf;
					m_pCharacter->currExp += gem->expBuf;
					//���� ������ ��ü
					if (weapon->gem->id != 0)
					{
						m_pInventory->InsertGem(weapon->gem);

					}
					//���⿡ �ɼ� ����
					weapon->gem = gem;
					//�κ��丮���� �¼� ����
					m_pInventory->DeleteGem(gemSelection - 1);
					cout << "�ɼ� ���� �Ϸ�!" << endl;
				}
			}
		}
	}
}
