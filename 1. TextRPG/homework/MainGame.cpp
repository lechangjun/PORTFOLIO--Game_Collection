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

	//캐릭터 생성화면
	while (true)
	{
		CParser parser;
		system("cls");
		//로고 출력
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
		cout << "(0): [EXIT] 나가기." << endl;
		cout << "(1): [View] 전사." << endl;
		cout << "(2): [View] 마법사." << endl;
		cout << "(3): [View] 도적." << endl;
		cout << "(4): [View] 로드." << endl;
		cout << " " << endl;
		cout << "---------------------------------------------" << endl;
		cout << " " << endl;


		int characterToCreate;
		cin >> characterToCreate;

		//종료
		if (characterToCreate == 0)
		{
			_CrtDumpMemoryLeaks(); // 메모리누수 체크(디버깅용)
			return false;
		}
		//세이브 데이터로드
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
			//캐릭터는 선택시 한번 생성
			m_pCharacter = new CCharacter;
			(*m_pCharacter).CreateCharacter(characterToCreate);
			return true;

		}

	}
	return false;
}

void CMainGame::Progress()
{

	//플레이어가 생성되지 않았다면 리턴.
	if (!SelectPlayer())
		return;

	m_pCharacter->gold = 3000;

	//인벤토리 매니저 초기화
	m_pInventoryMgr = new CInventoryMgr(m_pCharacter);
	//필드 초기화
	m_pField = new CField(m_pCharacter, m_pFactory);
	

	//캐릭터의 행동선택 화면
	while (true)
	{

		system("cls");
		//캐릭터 정보 출력
		m_pCharacter->PrintCharacter();
		cout << "  __________________________________________   " << endl;
		cout << "<| ========        Main Menu       ======== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "(0): [EXIT] 나가기." << endl;
		cout << "(1): [view] 던전 접근." << endl;
		cout << "(2): [View] 대장간." << endl;
		cout << "(3): [View] 휴식처." << endl;
		cout << "(4): [View] 인벤토리." << endl;
		cout << "(5): [SAVE] 세이브." << endl;
		cout << "(6): [View] 상점 -> 미완성" << endl;
		cout << "================================================" << endl;



		//어디를 갈 것인가?
		int destiantion;
		cin >> destiantion;


		if (destiantion == 0)
		{
			_CrtDumpMemoryLeaks(); // 메모리누수 체크(디버깅용)
			return;
		}
		//던전진입
		else if (1 == destiantion)
		{
			m_pField->Process();
		}

		//대장간 진입
		else if (2 == destiantion)
		{
			EnterForge();
		}
		//힐러집 진입
		else if (3 == destiantion)
		{
			EnterPharmacy();
		}
		//인벤토리 진입
		else if (4 == destiantion)
		{
			m_pInventoryMgr->Process();
		}
		//세이브
		else if (5 == destiantion)
		{
			Save();
		}
		else
			cout << "잘못된 입력입니다" << endl;

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

	cout << "게임을 종료합니다." << endl;
}


void CMainGame::EnterPharmacy()
{


	while (true)
	{
		system("cls");
		cout << "좋은 포션 보고가세요!" << endl;
		cout << "\n\n\n";

		int potionCnt = m_pFactory->GetPotionsSize();
		const CPotion* potions = m_pFactory->GetPotions();

		for (int i = 0; i < potionCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			potions[i].printPotionInfo();
		}

		cout << "잔액: " << m_pCharacter->gold << endl;
		cout << "\n\n";
		cout << "0. 나가기" << endl;
		int itemSelect = 0;
		cin >> itemSelect;

		if (itemSelect == 0)
		{
			break;
		}
		if (itemSelect <0 || itemSelect > potionCnt)
		{
			cout << "잘못된 입력입니다" << endl;
			system("pause");

		}
		//잘못된 입력이 아니면
		//1 1
		else
		{
			if (m_pCharacter->gold >= potions[itemSelect - 1].price)
			{
				CPotion* potion = m_pFactory->CreatePotion(itemSelect);
				//플레이어 인벤토리에 포션넣기
				m_pCharacter->inventory->InsertPotion(potion);
				m_pCharacter->gold -= potion->price;
				cout << potion->name << "을 구입하였습니다!" << endl;
			}
			else
				cout << "돈이 부족합니다!" << endl;

			system("pause");
		}

	}

}

void CMainGame::EnterForge()
{



	while (true)
	{
		system("cls");

		cout << "최고의 무기가 모여있습니다." << endl;
		cout << "\n\n\n";

		int weaponsCount = m_pFactory->GetWeaponsSize();
		const CWeapon* const weapons = m_pFactory->GetWeapons();

		for (int i = 0; i < weaponsCount; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			weapons[i].printWeaponInfo();
		}

		cout << "잔액: " << m_pCharacter->gold << endl;
		cout << "\n\n";
		cout << "0. 나가기 항목번호. 구입하기 999. 강화하기" << '\n';
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
			cout << "잘못된 입력입니다" << endl;
			system("pause");

		}
		//잘못된 입력이 아니면
		else
		{
			//만들 무기의 정보
			//CWeapon weaponToBuy = weapons[itemSelect - 1];
			CWeapon* weaponToBuy = m_pFactory->CreateWeapon(itemSelect);


			if (m_pCharacter->occupation != weaponToBuy->occupation)
			{
				cout << "착용할 수 없는 클래스의 무기입니다!" << endl;
				delete weaponToBuy;
				system("pause");
				continue;

			}
			else if (m_pCharacter->gold >= weaponToBuy->price)
			{

				cout << weaponToBuy->name << "을(를) 구입하였습니다!" << endl;
				//인벤토리에 넣는다.
				m_pCharacter->inventory->InsertWeapon(weaponToBuy);
				m_pCharacter->gold -= weaponToBuy->price;
			}
			else
			{
				delete weaponToBuy;
				cout << "돈이 부족합니다!" << endl;
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

		cout << "무기 인벤토리" << "\n\n";

		cout << "<장착중> " << endl;
		cout << "※장착중인 무기는 강화가 불가합니다." << endl;
		m_pCharacter->inventory->currWeapon->printWeaponInfo();
		cout << "\n\n";

		int weaponCnt = m_pCharacter->inventory->GetWeaponSize();
		for (int i = 0; i < weaponCnt; ++i)
		{
			cout << "<" << i + 1 << "번>" << endl;
			m_pCharacter->inventory->GetWeapon(i)->printWeaponInfo();
			cout << "강화확률: " << BASE_ENHANCE_CHANCE - (m_pCharacter->inventory->GetWeapon(i)->level * 5.2f) << endl;
			cout << "\n\n";
		}


		cout << "0. 나가기 아이템번호. 강화하기" << endl;
		unsigned int selection;
		cin >> selection;

		//selection 1 2 3 4 5
		//potion    0 1 2 3 4

		if (0 == selection)
		{
			return;
		}
		//항목 번호를 제대로 입력했으면
		else if (selection <= m_pCharacter->inventory->GetWeaponSize())
		{
			//강화비
			int cost = m_pCharacter->inventory->GetWeapon(selection-1)->price / 5;
			//돈이 충분하면
			if (m_pCharacter->gold >= cost)
			{
				m_pCharacter->gold -= cost;
				//강화시도
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
		//캐릭터 정보 읽어오기
		fread(character, sizeof(CCharacter), 1, fp);
		//무기정보 가져오기
		fread(weapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		m_pCharacter = character;
		m_pCharacter->inventory->currWeapon = weapon;
		cout << "로드 성공!" << endl;
		system("pause");


	}
	else
		cout << "로드 실패! 파일을 가져올 수 없습니다." << endl;

}

void CMainGame::Save()
{
	FILE* fp;
	//파일 스트림 생성
	errno_t err = fopen_s(&fp, "../Save/save1.txt", "wb");

	if (0 == err)
	{
		//캐릭터 정보 저장
		fwrite(m_pCharacter, sizeof(CCharacter), 1, fp);
		//무기정보 저장
		fwrite(m_pCharacter->inventory->currWeapon, sizeof(CWeapon), 1, fp);
		fclose(fp);
		cout << "세이브성공!" << endl;
		system("pause");
	}
	else
		cout << "세이브 실패! 파일을 저장할 수 없습니다." << endl;
}




