#include"Green_Snail.h"
#include"Armor.h"
#include"Weapon.h"
#include"Potion.h"
#include"Item.h"
#include"STORE_MENU.h"
#include"JOBS.h"
#include"SYSTEM_MENU.h"
#include "Warrior.h"
#include<limits>
int main()
{

	using namespace std;

	/*==============================Create the item================================*/
	const int Weapon_Number = 5;
	const int Armor_Number = 5;
	const int Potion_Number = 2;

	/*************Weapon 객체 저장********************/
	Item<Weapon> weaponArr(Weapon_Number); //기본 생성자가 없어서 그런거였군
	//값을 넣어준다. 여기 인수가 9개다
	weaponArr[0] = Weapon("초보전사의 검", 1000, 10, 35, 0, 0, 0, 10, 30);
	weaponArr[1] = Weapon("글라디우스", 2000, 20, 65, 0, 0, 0, 15, 47);
	weaponArr[2] = Weapon("일룬", 3000, 25, 80, 0, 0, 0, 25, 42);
	weaponArr[3] = Weapon("메이플 우산", 4000, 30, 0, 0, 0, 0, 30, 45);
	weaponArr[4] = Weapon("커틀러스", 5000, 35, 110, 0, 0, 0, 30, 70);

	/************************Armor 객체 저장**********************/

	Item<Armor> armorArr(Armor_Number);
	armorArr[0] = Armor("사각나무 방패", 100, 5, 0, 0, 0, 0, 5);
	armorArr[1] = Armor("냄비 뚜껑", 200, 10, 0, 0, 0, 0, 10);
	armorArr[2] = Armor("강철방패", 300, 15, 40, 0, 0, 0, 15);
	armorArr[3] = Armor("미스릴 버클러", 400, 20, 55, 0, 0, 0, 20);
	armorArr[4] = Armor("빨간 삼각 방패", 500, 25, 70, 0, 0, 0, 25);

	/************************Potion 객체 저장**********************/
	Item<Potion> potionArr(Potion_Number);
	potionArr[0] = Potion("체력 포션", 300, 0, 1);
	potionArr[1] = Potion("마나 포션", 0, 300, 1);
	Warrior W1;
	
	while (true)
	{
		//system("cls");
		cout << "=================Welcome to Text RPG==========================" << endl;
		cout << "Choose the JOBS" << endl;
		cout << "1. Warrior 2.Wizard 3.Archer 4. Thief 5. Exit" << endl;
		int inumber; //input number
		cin >> inumber;
		
		//cin 오류 처리
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Wrong input Please try again" << endl;
		}

		//게임 종료
		if (static_cast<JOBS>(inumber) == JOBS::JOB_EXIT)
		{
			cout << "End the program" << endl;
			break;
		}

		string iname; //input name
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); //cin 때문에 버퍼에 남아있던 엔터키 거르는 장치
		//캐릭터 선택 switch문
		switch (static_cast<JOBS>(inumber))
		{
			case JOBS::JOB_WARRIOR :
		
			
				cout << "캐릭터 이름을 입력해 주세요" << endl;
				getline(cin, iname);
				W1.setName(iname);
				cout << "전사 캐릭터가 생성 완료 되었습니다!" << endl;
				
			break;
		
		case JOBS::JOB_WIZARD:
			
			cout << "마법사 캐릭터가 생성 완료 되었습니다!" << endl;

			break;

		case JOBS::JOB_ARCHER:
			
			cout << "궁수 캐릭터가 생성 완료 되었습니다!" << endl;

			break;
			
		case JOBS::JOB_THIEF:
			
			cout << "도적 캐릭터가 생성 완료 되었습니다!" << endl;

			break;
			
		}

		break;
	}//캐릭터 생성 while문 
	W1.ShowInventory(W1.getInventory());

	while (true) //Making Menu while
	{

		//system("cls");
		std::cout << "==========================Lobby================================" << std::endl;
		std::cout << "1. Map" << std::endl;
		std::cout << "2. Store" << std::endl;
		std::cout << "3. Inventory" << std::endl;
		std::cout << "5. END Game " << std::endl;
		int iMenu; //input Menu
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767,'\n');
			cout << "Wrong input please try again" << endl;
		}

		//게임 종료
		if (static_cast<SYSTEM_MENU>(iMenu) == SYSTEM_MENU::SYSTEM_EXIT)
		{
			cout << "END GAME" << endl;
			break; 
		}
		//선택 창
		
		switch (static_cast<SYSTEM_MENU>(iMenu))
		{
		case SYSTEM_MENU::SYSTEM_MAP :




			break;

		case SYSTEM_MENU::SYSTEM_STORE:

			break;



		case SYSTEM_MENU::SYSTEM_INVENTORY:

			break;




		}//switch 끝

	
	} //Making Menu while

		

	return 0;
}