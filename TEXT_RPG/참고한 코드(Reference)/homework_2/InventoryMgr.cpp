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
	//멤버변수는 캐릭터와 인벤토리 주소의 복사본이니 null로 만들면 충분.
	m_pCharacter = nullptr;
	m_pInventory = nullptr;
}

void CInventoryMgr::ShowInventory()
{
	while (true)
	{
		system("cls");

		cout << "<장착중> " << endl;
		m_pCharacter->inventory->currWeapon->printWeaponInfo();

		cout << "  __________________________________________   " << endl;
		cout << "<| ======          Inventory         ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;


		cout << "0. 나가기 1.포션 2.무기 3. 젬 " << endl;

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


		cout << "<장착중> " << endl;
		m_pInventory->currWeapon->printWeaponInfo();
		cout << "\n\n";


		cout << "무기 인벤토리" << "\n\n";


		int weaponCnt = m_pInventory->GetWeaponSize();

		        
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			m_pInventory->GetWeapon(i)->printWeaponInfo();
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용 999.장착해제" << endl;
		unsigned int selection;
		cin >> selection;

		if (0 == selection)
		{
			return;
		}
		else if (999 == selection)
		{
			//현재 착용장비 인벤토리에 넣기
			m_pInventory->InsertWeapon(m_pInventory->currWeapon);
			//장착해제
			m_pInventory->currWeapon = new CWeapon;
		}
		//selection 1 2 3 4 5
		//potion    0 1 2 3 4
		//항목 번호를 제대로 입력했으면
		else if (selection <= m_pInventory->GetWeaponSize())
		{
			cout << m_pInventory->GetWeapon(selection -1)->name<< "을 장착했다!" << endl;
			system("pause");


			//플레이어가 무기를 끼고 있었다면 인벤토리에 넣는다.
			if (m_pInventory->currWeapon->id != 0)
			{
				m_pCharacter->attack -= m_pInventory->currWeapon->attack;
				m_pInventory->InsertWeapon(m_pInventory->currWeapon);
			}
			//맨손이었으면 빈객체를 파괴한다.
			else
			{
				delete m_pInventory->currWeapon;
				m_pInventory->currWeapon = nullptr;
			}

			//무기를 장착한다.
			m_pInventory->currWeapon = m_pInventory->GetWeapon(selection - 1);
			m_pCharacter->attack += m_pInventory->currWeapon->attack;
			//장착한 무기는 인벤토리에서 삭제한다.
			m_pInventory->DeleteWeapon(selection - 1);



		}
	}
}

void CInventoryMgr::ShowPotionBag()
{
	while (true)
	{

		system("cls");

		cout << "포션 인벤토리" << "\n\n";

		int potionCnt = m_pInventory->GetPotionSize();
		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			m_pInventory->GetPotion(i)->printPotionInfo();
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용" << endl;
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
				cout << "이미 체력이 꽉 차있습니다.";
				system("pause");
				continue;
			}

			cout << m_pInventory->GetPotion(selection -1)->name << "을 사용했다!" << endl;
			system("pause");


			
			CPotion* potion = m_pInventory->GetPotion(selection - 1);
			//캐릭터 체력 + 회복량이 최대체력보다 높으면 최대체력까지만 채워줌. 아니면 그냥 포션의 힐량만큼 채움.
			int healAmount = ((m_pCharacter->currHealth + potion->healAmount) > m_pCharacter->maxHealth)
				? (m_pCharacter->maxHealth - m_pCharacter->currHealth) : potion->healAmount;
			//체력회복
			m_pCharacter->currHealth += healAmount;
			//포션 지우기
			delete potion;
			//인벤토리 줄이기
			m_pInventory->DeletePotion(selection - 1);
		}
	}
}

void CInventoryMgr::ShowGemBag()
{
	if (nullptr == m_pCharacter)
	{
		cout << "인벤토리의 오너가 없습니다!" << endl;
		return;
	}

	while (true)
	{

		system("cls");

		cout << "구상 중" << "\n\n";

		int gemCount = m_pInventory->GetGemSize();
		for (int i = 0; i < gemCount; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			m_pInventory->GetGem(i)->PrintGemInfo();
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 사용" << endl;
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
			//조합할 무기 선택화면
			while (true)
			{
				system("cls");
				int weaponSize = m_pInventory->GetWeaponSize();
				if (0 == weaponSize)
				{
					cout << "현재 옵션을 부착할 수 없는 무기가 없습니다. (착용중인 무기는 옵션을 부착할 수 없습니다)" << endl;
					system("pause");
					break;
				}

				for (int i = 0; i < weaponSize; ++i)
				{
					cout << "<" << i + 1 << "번>" << endl;
					m_pInventory->GetWeapon(i)->printWeaponInfo();
					cout << "\n\n";
				}

				cout << "0. 나가기 아이템번호. 사용" << endl;
				unsigned int weaponSelection;
				cin >> weaponSelection;

				if (0 == weaponSelection)
				{
					break;
				}
				else if (weaponSelection <= m_pInventory->GetWeaponSize())
				{
					//무기에 젬 조합하기
					CWeapon* weapon = m_pInventory->GetWeapon(weaponSelection - 1);
					CBufItem* gem = m_pInventory->GetGem(gemSelection - 1);
					weapon->attack += gem->attackBuf;
					weapon->element = gem->element;
					m_pCharacter->maxHealth += gem->maxHealthBuf;
					m_pCharacter->currExp += gem->expBuf;
					//젬이 있으면 교체
					if (weapon->gem->id != 0)
					{
						m_pInventory->InsertGem(weapon->gem);

					}
					//무기에 옵션 부착
					weapon->gem = gem;
					//인벤토리에서 온션 삭제
					m_pInventory->DeleteGem(gemSelection - 1);
					cout << "옵션 부착 완료!" << endl;
				}
			}
		}
	}
}
