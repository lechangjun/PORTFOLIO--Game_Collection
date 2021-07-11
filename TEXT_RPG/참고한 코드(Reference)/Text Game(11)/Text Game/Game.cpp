#include "stdafx.h"
#include "Game.h"

Game::Game()
{	
	_User = new Player;
	_ItemList = new ItemList;
	_Bag = new Inventory;
	_Shop = new Store;

	_User->NickName(P_Name);
	GamePlay();
}

Game::~Game()
{
	delete _User;
	delete _ItemList;
	delete _Bag;
	delete _Shop;
}

void Game::GamePlay()
{
	_GamePlay = 1;
	while (_GamePlay)
	{
		system("cls");

		Game_Interface();

		switch (select_GamePlay)
		{
			case 1:
				cout << endl;
				cout << "������ �����մϴ�." << endl;
				for (int i = 0; i < 3; i++)
				{
					cout << "." << endl;
					Sleep(300);
				}
				Battle();
				break;
			case 2:
				Inven();
				break;
			case 3:
				Shop();
				break;
			case 4:
				Rest();
				break;
			case 0:
				_GamePlay = 0;
				cout << "������ �����մϴ�." << endl;
				Sleep(2000);
				break;
			default:
				cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
				Sleep(1000);
				break;
		}
	}
}

void Game::Game_Interface()
{
	_User->Profile();

	cout << "������ �Ͻðڽ��ϱ�?" << endl;
	cout << "[1]: ����, [2]: �κ��丮, [3]: ����, [4]: �޽�, [0]: ���� ����" << endl;
	cout << ">> ";
	cin >> select_GamePlay;
}

void Game::Inven()
{
	_Inven = 1;
	do
	{
		_User->Show_P_Inventory();
		cout << "������ �Ͻðڽ��ϱ�?" << endl;
		cout << "[1]: ��� ĭ�� ����, [2]: ���� ĭ�� ����, [3]: ����ǰ ĭ�� ����, [0]: ���� ȭ������" << endl;
		cout << ">> ";
		cin >> select_Inventory;

		switch (select_Inventory)
		{
		case 1:
			_Bag->Show_Inventory_E();
			cout << endl;
			cout << "[1]~[5]: ����, [0]: ���� ȭ������" << endl;
			cout << ">> ";
			cin >> select_Inven_Equip;
			switch (select_Inven_Equip)
			{
			case 0:
				break;
			default:
				if (_Bag->Get_Inven_Equip().empty())
				{
					cout << "�ƹ��͵� �����ϴ�." << endl;
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Equip().find(select_Inven_Equip)->second == "��ö ��")
				{
					if (_User->Get_Set_Item1() != 0)
					{
						cout << "�̹� ���� �������� �����ϰ� �ֽ��ϴ�." << endl;
						Sleep(1000);
						break;
					}
					cout << "�����߽��ϴ�." << endl;
					_User->Att_Plus(_ItemList->IronSword->Get_WeaponAtt());
					_Bag->Equip_Erase(select_Inven_Equip);
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Equip().find(select_Inven_Equip)->second == "��ö ����")
				{
					if (_User->Get_Set_Item2() != 0)
					{
						cout << "�̹� ���� �������� �����ϰ� �ֽ��ϴ�." << endl;
						Sleep(1000);
						break;
					}
					cout << "�����߽��ϴ�." << endl;
					_User->M_HP_Plus(_ItemList->IronArmor->Get_ArmorHp());
					_Bag->Equip_Erase(select_Inven_Equip);
					Sleep(1000);
					break;
				}
				else
				{
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
					Sleep(1000);
					break;
				}
			}
			break;
		case 2:
			_Bag->Show_Inventory_P();
			cout << endl;
			cout << "[1]~[5]: ���, [0]: ���� ȭ������" << endl;
			cout << ">> ";
			cin >> select_Inven_Potion;
			switch (select_Inven_Potion)
			{
			case 0:
				break;
			default:
				if (_Bag->Get_Inven_Potion().empty())
				{
					cout << "�ƹ��͵� �����ϴ�." << endl;
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Potion().find(select_Inven_Potion)->second == "Hp ȸ�� ����")
				{
					cout << "����߽��ϴ�." << endl;
					_User->HP_Heal(_ItemList->HpPotion->Get_PotionHp());
					_Bag->Potion_Erase(select_Inven_Potion);
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Potion().find(select_Inven_Potion)->second == "���ݷ� ���� ����")
				{
					cout << "���� �߿��� ����� �� �ֽ��ϴ�." << endl;
					Sleep(1000);
					break;
				}
				else
				{
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
					Sleep(1000);
					break;
				}
			}
			break;
		case 3:
			_Bag->Show_Inventory_O();
			cout << endl;
			cout << "[0]: ���� ȭ������" << endl;
			cout << ">> ";
			cin >> select_Inven_Other;
			switch (select_Inven_Other)
			{
			case 0:
				cout << "���� ȭ������ ���ư��ϴ�." << endl;
				Sleep(1000);
				break;
			default:
				cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
				Sleep(1000);
				break;
			}
			break;
		case 0:
			cout << "���� ȭ������ ���ư��ϴ�." << endl;
			Sleep(2000);
			_Inven = 0;
			break;
		default:
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
			Sleep(1000);
			break;
		}
	} while (_Inven != 0);
}

void Game::Battle()
{
	system("cls");
	_Enemy = new Monster();

	Used_Item = 0;

	_Battle = 1;
	while (_Battle == 1)
	{
		system("cls");
		_User->Profile();
		cout << "\tVS" << endl;
		_Enemy->Show_M_Profile();

		cout << "������ �Ͻðڽ��ϱ�?" << endl;
		cout << "[1]: ����, [2]: ���, [3]: �κ��丮-����, [0]: ��������" << endl;
		cout << ">> ";
		cin >> select_Battle;

		switch (select_Battle)
		{
			case 1:
			{
				system("cls");
				_Enemy->Damage(_User->GetP_ATT());

				_User->Profile();
				cout << "\tVS" << endl;
				_Enemy->Show_M_Profile();

				cout << "�÷��̾��� ����!" << endl;
				cout << "���ʹ� " << _User->GetP_ATT() << "��ŭ�� �������� �Ծ���." << endl;
				cout << endl;
				Sleep(1000);
				if (_Enemy->GetM_HP() > 0)
				{
					_User->Damage(_Enemy->GetM_ATT());

					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << "�÷��̾��� ����!" << endl;
					cout << "���ʹ� " << _User->GetP_ATT() << "��ŭ�� �������� �Ծ���." << endl;
					cout << endl;
					
					cout << "������ ����!" << endl;
					cout << "�÷��̾�� " << _Enemy->GetM_ATT() << "��ŭ�� �������� �Ծ���." << endl;
					cout << endl;
					Sleep(1000);
				}
				else if (_Enemy->GetM_HP() <= 0)
				{
					cout << "���� ���������ϴ�. ������ �����մϴ�." << endl;
					_User->PlusGold(_User->Get_GOLD());
					Drop_Item();
					Sleep(2000);
					delete _Enemy;
					if (Used_Item == 1)
					{
						_User->Att_Return(_ItemList->AttPorion->Get_PotionAtt());
					}
					_Battle = 0;
				}
				if (_User->GetP_HP() <= 0)
				{
					cout << "�÷��̾ ���������ϴ�. ������ �����մϴ�." << endl;
					Sleep(2000);
					delete _User;
					_GamePlay = 0;
				}
			}
			break;
			case 2:
				cout << "�÷��̾�� ��� �¼��� ���մϴ�." << endl;
				Sleep(500);

				int a;
				for (int i = 0; i < 10; i++)
				{
					a = rand() % 100;
				}
				if (a <= 33)
				{
					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << ":: �÷��̾�� �� �����߽��ϴ�. ::" << endl;
					cout << ":: ���� ���� ::" << endl;
					cout << endl;
				}
				else if (a > 33 && a <= 66)
				{
					_User->Damage(_Enemy->GetM_ATT());

					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << ":: �÷��̾�� �� �����߽��ϴ�. ::" << endl;
					cout << endl;
					cout << "������ ����!" << endl;
					cout << "�÷��̾�� " << _Enemy->GetM_ATT() << "��ŭ�� �������� �Ծ���." << endl;
					cout << endl;
					if (_User->GetP_HP() <= 0)
					{
						cout << "�÷��̾ ���������ϴ�. ������ �����մϴ�." << endl;
						delete _User;
						_GamePlay = 0;
					}
				}
				else
				{
					_Enemy->Damage(_User->GetP_ATT());

					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << ":: �÷��̾�� ���� ������ ���Ƴ��� �ݰ��߽��ϴ�. ::" << endl;
					cout << endl;
					cout << "�÷��̾��� �ݰ�!" << endl;
					cout << "���ʹ� " << _User->GetP_ATT() << "��ŭ�� �������� �Ծ���." << endl;
					cout << endl;
					if (_Enemy->GetM_HP() <= 0)
					{
						cout << "���� ���������ϴ�. ������ �����մϴ�." << endl;
						_User->PlusGold(_User->Get_GOLD());
						Drop_Item();
						Sleep(2000);
						delete _Enemy;
						if (Used_Item == 1)
						{
							_User->Att_Return(_ItemList->AttPorion->Get_PotionAtt());
						}
						_Battle = 0;
					}
				}
				Sleep(1000);
				break;
			case 3:
				_Bag->Show_Inventory_P();
				cout << endl;
				cout << "[1]~[5]: ���, [0]: ���� ȭ������" << endl;
				cout << ">> ";
				cin >> select_Battle_Inven;
				switch (select_Battle_Inven)
				{
				case 0:
					break;
				default:
					if (_Bag->Get_Inven_Potion().empty())
					{
						cout << "�ƹ��͵� �����ϴ�." << endl;
						Sleep(1000);
						break;
					}
					else if (_Bag->Get_Inven_Potion().find(select_Battle_Inven)->second == "Hp ȸ�� ����")
					{
						cout << "����߽��ϴ�." << endl;
						_User->HP_Heal(_ItemList->HpPotion->Get_PotionHp());
						_Bag->Potion_Erase(select_Battle_Inven);
						Sleep(1000);
						break;
					}
					else if (_Bag->Get_Inven_Potion().find(select_Battle_Inven)->second == "���ݷ� ���� ����")
					{
						cout << "����߽��ϴ�." << endl;
						Used_Item++;
						_User->Att_Plus(_ItemList->AttPorion->Get_PotionAtt());
						_Bag->Potion_Erase(select_Battle_Inven);
						Sleep(1000);
						break;
					}
					else
					{
						cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
						Sleep(1000);
						break;
					}
				}
				break;
			case 0:
				int b;
				for (int i = 0; i < 10; i++)
				{
					b = rand() % 100;
				}
				if (b >= 50)
				{
					cout << "����ġ�µ� �����߽��ϴ�." << endl;
					Sleep(2000);
					delete _Enemy;
					_Battle = 0;
				}
				else
				{
					_User->Damage(_Enemy->GetM_ATT());
					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << "����ġ�µ� �����߽��ϴ�." << endl;
					cout << endl;
					cout << "������ ����!" << endl;
					cout << "�÷��̾�� " << _Enemy->GetM_ATT() << "��ŭ�� �������� �Ծ���." << endl;
					if (_User->GetP_HP() <= 0)
					{
						cout << "�÷��̾ ���������ϴ�. ������ �����մϴ�." << endl;
						delete _User;
						_GamePlay = 0;
					}
					Sleep(1000);
				}
				break;
			default:
				cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
				Sleep(1000);
				break;
		}
	}
}

void Game::Drop_Item()
{
	int z;
	for (int i = 0; i < 10; i++)
	{
		z = rand() % 100;
	}
	if (z < 70)
	{
		if (_Bag->Get_Other_Count() == 0)
		{
			cout << "������ ���� á���ϴ�." << endl;
			Sleep(1000);
		}
		else
		{
			if (_Enemy->GetM_Name() == "����")
			{
				cout << "����ǰ���� " << _ItemList->Item1->Get_DropName() << "�� ������ϴ�." << endl;
				_Bag->Other_insert(1, _ItemList->Item1->Get_DropName());

			}
			else if (_Enemy->GetM_Name() == "��")
			{
				cout << "����ǰ���� " << _ItemList->Item2->Get_DropName() << "�� ������ϴ�." << endl;
				_Bag->Other_insert(1, _ItemList->Item2->Get_DropName());
			}
			else if (_Enemy->GetM_Name() == "���̷���")
			{
				cout << "����ǰ���� " << _ItemList->Item3->Get_DropName() << "�� ������ϴ�." << endl;
				_Bag->Other_insert(1, _ItemList->Item3->Get_DropName());
			}
		}
	}
}

void Game::Shop()
{
	do
	{
		_User->Show_P_Inventory();
		_Shop->Show_Store();

		cin >> select_Shop;
		cout << endl;
		switch (select_Shop)
		{
		case 1:
			cout << "�����Ͻ� �������� ������ �����Ͽ��ֽʽÿ�." << endl;
			cout << "[1]: ���, [2]: ����, [0]: ���� ȭ������" << endl;
			cout << ">> ";
			cin >> select_Shop_Do;
			switch (select_Shop_Do)
			{
			case 1: //���
				do
				{
					system("cls");
					_User->Show_P_Inventory();
					_Shop->Show_Equip();
					cin >> select_Shop_Equip;
					switch (select_Shop_Equip)
					{
					case 1:
						if (_Bag->Get_Equip_Count() == 0)
						{
							cout << "������ ���� �� ������ �� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->IronSword->Get_WeaponPrice())
						{
							cout << "�������� �����մϴ�." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "��� " << _ItemList->IronSword->Get_WeaponName() << "�� �����ϼ̽��ϴ�." << endl;
							cout << "-" << _ItemList->IronSword->Get_WeaponPrice() << "G" << endl;
							_User->PayGold(_ItemList->IronSword->Get_WeaponPrice());
							_Bag->Equip_insert(1, _ItemList->IronSword->Get_WeaponName());
							Sleep(1000);
							break;
						}
					case 2:
						if (_Bag->Get_Equip_Count() == 0)
						{
							cout << "������ ���� �� ������ �� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->IronArmor->Get_ArmorPrice())
						{
							cout << "�������� �����մϴ�." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "��� " << _ItemList->IronArmor->Get_ArmorName() << "�� �����ϼ̽��ϴ�." << endl;
							cout << "-" << _ItemList->IronArmor->Get_ArmorPrice() << "G" << endl;
							_User->PayGold(_ItemList->IronArmor->Get_ArmorPrice());
							_Bag->Equip_insert(1, _ItemList->IronArmor->Get_ArmorName());
							Sleep(1000);
							break;
						}
						//case 3:
					case 0:
						cout << "���� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1000);
						break;
					default:
						cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
						Sleep(1000);
						break;
					}
				} while (select_Shop_Equip != 0);
				break;
			case 2: //����
				do
				{
					system("cls");
					_User->Show_P_Inventory();
					_Shop->Show_Potion();
					cin >> select_Shop_Potion;
					switch (select_Shop_Potion)
					{
					case 1:
						if (_Bag->Get_Potion_Count() == 0)
						{
							cout << "������ ���� �� ������ �� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->HpPotion->Get_PotionPrice())
						{
							cout << "�������� �����մϴ�." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "���� " << _ItemList->HpPotion->Get_PotionName() << "�� �����ϼ̽��ϴ�." << endl;
							cout << "-" << _ItemList->HpPotion->Get_PotionPrice() << "G" << endl;
							_User->PayGold(_ItemList->HpPotion->Get_PotionPrice());
							_Bag->Potion_insert(1, _ItemList->HpPotion->Get_PotionName());
							Sleep(1000);
							break;
						}
					case 2:
						if (_Bag->Get_Potion_Count() == 0)
						{
							cout << "������ ���� �� ������ �� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->AttPorion->Get_PotionPrice())
						{
							cout << "�������� �����մϴ�." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "���� " << _ItemList->AttPorion->Get_PotionName() << "�� �����ϼ̽��ϴ�." << endl;
							cout << "-" << _ItemList->AttPorion->Get_PotionPrice() << "G" << endl;
							_User->PayGold(_ItemList->AttPorion->Get_PotionPrice());
							_Bag->Potion_insert(1, _ItemList->AttPorion->Get_PotionName());
							Sleep(1000);
							break;
						}
						//case 3:
					case 0:
						cout << "���� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1000);
						break;
					default:
						cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
						Sleep(1000);
						break;
					}
				} while (select_Shop_Potion != 0);
				break;
			}//����
			break;
		case 2:
			cout << "�Ǹ��Ͻ� �������� ������ �������ֽʽÿ�." << endl;
			cout << "[1]: ���, [2]: ����, [3]: ����ǰ, [0]: ���� ȭ������" << endl;
			cout << ">> ";
			cin >> select_Shop_Do;
			switch (select_Shop_Do)
			{
			case 1:
				do
				{
					system("cls");
					_User->Show_P_Inventory();
					_Bag->Show_Inventory_E();
					cout << endl;
					cout << "������ �Ǹ��Ͻðڽ��ϱ�?" << endl;
					cout << "�ǸŰ��� ���԰��� 70%" << endl;
					cout << "[1]~[5]: �Ǹ�, [0]: ���� ȭ������" << endl;
					cout << ">> ";
					cin >> select_Shop_Equip;
					switch (select_Shop_Equip)
					{
					case 0:
						cout << "���� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1000);
						break;
					default:
						if (_Bag->Get_Inven_Equip().empty())
						{
							cout << "�ƹ��͵� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							if (_Bag->Get_Inven_Equip().find(select_Shop_Equip)->second == "��ö ��")
							{
								cout << "��� " << _ItemList->IronSword->Get_WeaponName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
								cout << "+" << _ItemList->IronSword->Get_WeaponSPrice() << "G" << endl;
								_User->ReceiveGold(_ItemList->IronSword->Get_WeaponSPrice());
								_Bag->Equip_Erase(select_Shop_Equip);
								Sleep(1000);
								break;
							}
							else if (_Bag->Get_Inven_Equip().find(select_Shop_Equip)->second == "��ö ����")
							{
								cout << "��� " << _ItemList->IronArmor->Get_ArmorName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
								cout << "+" << _ItemList->IronArmor->Get_ArmorSPrice() << "G" << endl;
								_User->ReceiveGold(_ItemList->IronArmor->Get_ArmorSPrice());
								_Bag->Equip_Erase(select_Shop_Equip);
								Sleep(1000);
								break;
							}
							else
							{
								cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
								Sleep(1000);
								break;
							}
						}
						break;
					}
				} while (select_Shop_Equip != 0);
				break;
			case 2:
				do
				{
					system("cls");
					_User->Show_P_Inventory();
					_Bag->Show_Inventory_P();
					cout << endl;
					cout << "������ �Ǹ��Ͻðڽ��ϱ�?" << endl;
					cout << "�ǸŰ��� ���԰��� 70%" << endl;
					cout << "[1]~[5]: �Ǹ�, [0]: ���� ȭ������" << endl;
					cout << ">> ";
					cin >> select_Shop_Potion;
					switch (select_Shop_Potion)
					{
					case 0:
						cout << "���� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1000);
						break;
					default:
						if (_Bag->Get_Inven_Potion().empty())
						{
							cout << "�ƹ��͵� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						if (_Bag->Get_Inven_Potion().find(select_Shop_Potion)->second == "Hp ȸ�� ����")
						{
							cout << "��� " << _ItemList->HpPotion->Get_PotionName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
							cout << "+" << _ItemList->HpPotion->Get_PotionSPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->HpPotion->Get_PotionSPrice());
							_Bag->Potion_Erase(select_Shop_Potion);
							Sleep(1000);
							break;
						}
						else if (_Bag->Get_Inven_Potion().find(select_Shop_Potion)->second == "���ݷ� ���� ����")
						{
							cout << "��� " << _ItemList->AttPorion->Get_PotionName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
							cout << "+" << _ItemList->AttPorion->Get_PotionSPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->AttPorion->Get_PotionSPrice());
							_Bag->Potion_Erase(select_Shop_Potion);
							Sleep(1000);
							break;
						}
						else
						{
							cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
							Sleep(1000);
							break;
						}
					break;
					}
				} while (select_Shop_Potion != 0);
				break;
			case 3:
				do
				{
					system("cls");
					_User->Show_P_Inventory();
					_Bag->Show_Inventory_O();
					cout << endl;
					cout << "������ �Ǹ��Ͻðڽ��ϱ�?" << endl;
					cout << "[1]~[5]: �Ǹ�, [0]: ���� ȭ������" << endl;
					cout << ">> ";
					cin >> select_Shop_Other;
					switch (select_Shop_Other)
					{
					case 0:
						cout << "���� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1000);
						break;
					default:
						if (_Bag->Get_Inven_Other().empty())
						{
							cout << "�ƹ��͵� �����ϴ�." << endl;
							Sleep(1000);
							break;
						}
						if (_Bag->Get_Inven_Other().find(select_Shop_Other)->second == "������ ����")
						{
							cout << "����ǰ " << _ItemList->Item1->Get_DropName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
							cout << "+" << _ItemList->Item1->Get_DropPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->Item1->Get_DropPrice());
							_Bag->Other_Erase(select_Shop_Other);
							Sleep(1000);
							break;
						}
						else if (_Bag->Get_Inven_Other().find(select_Shop_Other)->second == "���� �� ����")
						{
							cout << "����ǰ " << _ItemList->Item2->Get_DropName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
							cout << "+" << _ItemList->Item2->Get_DropPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->Item2->Get_DropPrice());
							_Bag->Other_Erase(select_Shop_Other);
							Sleep(1000);
							break;
						}
						else if (_Bag->Get_Inven_Other().find(select_Shop_Other)->second == "���̷����� ������")
						{
							cout << "����ǰ " << _ItemList->Item3->Get_DropName() << "�� �Ǹ��ϼ̽��ϴ�." << endl;
							cout << "+" << _ItemList->Item3->Get_DropPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->Item3->Get_DropPrice());
							_Bag->Other_Erase(select_Shop_Other);
							Sleep(1000);
							break;
						}
						else
						{
							cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
							Sleep(1000);
							break;
						}
					break;
					}
				} while (select_Shop_Other != 0);
				break;
			case 0:
				cout << "���� ȭ������ ���ư��ϴ�." << endl;
				Sleep(1000);
				break;
			default:
				cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
				Sleep(1000);
				break;
			}
			break;
		case 0:
			cout << "������ �����ϴ�." << endl;
			Sleep(2000);
			break;
		default:
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
			Sleep(1000);
			break;
		}
	} while (select_Shop != 0);
}

void Game::Rest()
{
	cout << ":: �޽� ::" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "." << endl;
		Sleep(500);
	}
	_User->Rest(_User->GetP_HP());

	Sleep(1000);
}