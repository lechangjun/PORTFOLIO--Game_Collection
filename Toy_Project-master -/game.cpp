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

	/*************Weapon ��ü ����********************/
	Item<Weapon> weaponArr(Weapon_Number); //�⺻ �����ڰ� ��� �׷��ſ���
	//���� �־��ش�. ���� �μ��� 9����
	weaponArr[0] = Weapon("�ʺ������� ��", 1000, 10, 35, 0, 0, 0, 10, 30);
	weaponArr[1] = Weapon("�۶��콺", 2000, 20, 65, 0, 0, 0, 15, 47);
	weaponArr[2] = Weapon("�Ϸ�", 3000, 25, 80, 0, 0, 0, 25, 42);
	weaponArr[3] = Weapon("������ ���", 4000, 30, 0, 0, 0, 0, 30, 45);
	weaponArr[4] = Weapon("ĿƲ����", 5000, 35, 110, 0, 0, 0, 30, 70);

	/************************Armor ��ü ����**********************/

	Item<Armor> armorArr(Armor_Number);
	armorArr[0] = Armor("�簢���� ����", 100, 5, 0, 0, 0, 0, 5);
	armorArr[1] = Armor("���� �Ѳ�", 200, 10, 0, 0, 0, 0, 10);
	armorArr[2] = Armor("��ö����", 300, 15, 40, 0, 0, 0, 15);
	armorArr[3] = Armor("�̽��� ��Ŭ��", 400, 20, 55, 0, 0, 0, 20);
	armorArr[4] = Armor("���� �ﰢ ����", 500, 25, 70, 0, 0, 0, 25);

	/************************Potion ��ü ����**********************/
	Item<Potion> potionArr(Potion_Number);
	potionArr[0] = Potion("ü�� ����", 300, 0, 1);
	potionArr[1] = Potion("���� ����", 0, 300, 1);
	Warrior W1;
	
	while (true)
	{
		//system("cls");
		cout << "=================Welcome to Text RPG==========================" << endl;
		cout << "Choose the JOBS" << endl;
		cout << "1. Warrior 2.Wizard 3.Archer 4. Thief 5. Exit" << endl;
		int inumber; //input number
		cin >> inumber;
		
		//cin ���� ó��
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Wrong input Please try again" << endl;
		}

		//���� ����
		if (static_cast<JOBS>(inumber) == JOBS::JOB_EXIT)
		{
			cout << "End the program" << endl;
			break;
		}

		string iname; //input name
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); //cin ������ ���ۿ� �����ִ� ����Ű �Ÿ��� ��ġ
		//ĳ���� ���� switch��
		switch (static_cast<JOBS>(inumber))
		{
			case JOBS::JOB_WARRIOR :
		
			
				cout << "ĳ���� �̸��� �Է��� �ּ���" << endl;
				getline(cin, iname);
				W1.setName(iname);
				cout << "���� ĳ���Ͱ� ���� �Ϸ� �Ǿ����ϴ�!" << endl;
				
			break;
		
		case JOBS::JOB_WIZARD:
			
			cout << "������ ĳ���Ͱ� ���� �Ϸ� �Ǿ����ϴ�!" << endl;

			break;

		case JOBS::JOB_ARCHER:
			
			cout << "�ü� ĳ���Ͱ� ���� �Ϸ� �Ǿ����ϴ�!" << endl;

			break;
			
		case JOBS::JOB_THIEF:
			
			cout << "���� ĳ���Ͱ� ���� �Ϸ� �Ǿ����ϴ�!" << endl;

			break;
			
		}

		break;
	}//ĳ���� ���� while�� 
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

		//���� ����
		if (static_cast<SYSTEM_MENU>(iMenu) == SYSTEM_MENU::SYSTEM_EXIT)
		{
			cout << "END GAME" << endl;
			break; 
		}
		//���� â
		
		switch (static_cast<SYSTEM_MENU>(iMenu))
		{
		case SYSTEM_MENU::SYSTEM_MAP :




			break;

		case SYSTEM_MENU::SYSTEM_STORE:

			break;



		case SYSTEM_MENU::SYSTEM_INVENTORY:

			break;




		}//switch ��

	
	} //Making Menu while

		

	return 0;
}