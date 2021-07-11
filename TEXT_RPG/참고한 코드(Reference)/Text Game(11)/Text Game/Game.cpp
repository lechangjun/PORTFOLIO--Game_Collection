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
				cout << "전투에 돌입합니다." << endl;
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
				cout << "게임을 종료합니다." << endl;
				Sleep(2000);
				break;
			default:
				cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
				Sleep(1000);
				break;
		}
	}
}

void Game::Game_Interface()
{
	_User->Profile();

	cout << "무엇을 하시겠습니까?" << endl;
	cout << "[1]: 전투, [2]: 인벤토리, [3]: 상점, [4]: 휴식, [0]: 게임 종료" << endl;
	cout << ">> ";
	cin >> select_GamePlay;
}

void Game::Inven()
{
	_Inven = 1;
	do
	{
		_User->Show_P_Inventory();
		cout << "무엇을 하시겠습니까?" << endl;
		cout << "[1]: 장비 칸을 본다, [2]: 포션 칸을 본다, [3]: 전리품 칸을 본다, [0]: 이전 화면으로" << endl;
		cout << ">> ";
		cin >> select_Inventory;

		switch (select_Inventory)
		{
		case 1:
			_Bag->Show_Inventory_E();
			cout << endl;
			cout << "[1]~[5]: 착용, [0]: 이전 화면으로" << endl;
			cout << ">> ";
			cin >> select_Inven_Equip;
			switch (select_Inven_Equip)
			{
			case 0:
				break;
			default:
				if (_Bag->Get_Inven_Equip().empty())
				{
					cout << "아무것도 없습니다." << endl;
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Equip().find(select_Inven_Equip)->second == "강철 검")
				{
					if (_User->Get_Set_Item1() != 0)
					{
						cout << "이미 같은 아이템을 착용하고 있습니다." << endl;
						Sleep(1000);
						break;
					}
					cout << "착용했습니다." << endl;
					_User->Att_Plus(_ItemList->IronSword->Get_WeaponAtt());
					_Bag->Equip_Erase(select_Inven_Equip);
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Equip().find(select_Inven_Equip)->second == "강철 갑옷")
				{
					if (_User->Get_Set_Item2() != 0)
					{
						cout << "이미 같은 아이템을 착용하고 있습니다." << endl;
						Sleep(1000);
						break;
					}
					cout << "착용했습니다." << endl;
					_User->M_HP_Plus(_ItemList->IronArmor->Get_ArmorHp());
					_Bag->Equip_Erase(select_Inven_Equip);
					Sleep(1000);
					break;
				}
				else
				{
					cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
					Sleep(1000);
					break;
				}
			}
			break;
		case 2:
			_Bag->Show_Inventory_P();
			cout << endl;
			cout << "[1]~[5]: 사용, [0]: 이전 화면으로" << endl;
			cout << ">> ";
			cin >> select_Inven_Potion;
			switch (select_Inven_Potion)
			{
			case 0:
				break;
			default:
				if (_Bag->Get_Inven_Potion().empty())
				{
					cout << "아무것도 없습니다." << endl;
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Potion().find(select_Inven_Potion)->second == "Hp 회복 포션")
				{
					cout << "사용했습니다." << endl;
					_User->HP_Heal(_ItemList->HpPotion->Get_PotionHp());
					_Bag->Potion_Erase(select_Inven_Potion);
					Sleep(1000);
					break;
				}
				else if (_Bag->Get_Inven_Potion().find(select_Inven_Potion)->second == "공격력 증가 포션")
				{
					cout << "전투 중에만 사용할 수 있습니다." << endl;
					Sleep(1000);
					break;
				}
				else
				{
					cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
					Sleep(1000);
					break;
				}
			}
			break;
		case 3:
			_Bag->Show_Inventory_O();
			cout << endl;
			cout << "[0]: 이전 화면으로" << endl;
			cout << ">> ";
			cin >> select_Inven_Other;
			switch (select_Inven_Other)
			{
			case 0:
				cout << "이전 화면으로 돌아갑니다." << endl;
				Sleep(1000);
				break;
			default:
				cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
				Sleep(1000);
				break;
			}
			break;
		case 0:
			cout << "이전 화면으로 돌아갑니다." << endl;
			Sleep(2000);
			_Inven = 0;
			break;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
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

		cout << "무엇을 하시겠습니까?" << endl;
		cout << "[1]: 공격, [2]: 방어, [3]: 인벤토리-포션, [0]: 도망간다" << endl;
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

				cout << "플레이어의 공격!" << endl;
				cout << "몬스터는 " << _User->GetP_ATT() << "만큼의 데미지를 입었다." << endl;
				cout << endl;
				Sleep(1000);
				if (_Enemy->GetM_HP() > 0)
				{
					_User->Damage(_Enemy->GetM_ATT());

					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << "플레이어의 공격!" << endl;
					cout << "몬스터는 " << _User->GetP_ATT() << "만큼의 데미지를 입었다." << endl;
					cout << endl;
					
					cout << "몬스터의 공격!" << endl;
					cout << "플레이어는 " << _Enemy->GetM_ATT() << "만큼의 데미지를 입었다." << endl;
					cout << endl;
					Sleep(1000);
				}
				else if (_Enemy->GetM_HP() <= 0)
				{
					cout << "적이 쓰러졌습니다. 전투를 종료합니다." << endl;
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
					cout << "플레이어가 쓰러졌습니다. 전투를 종료합니다." << endl;
					Sleep(2000);
					delete _User;
					_GamePlay = 0;
				}
			}
			break;
			case 2:
				cout << "플레이어는 방어 태세를 취합니다." << endl;
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

					cout << ":: 플레이어는 방어에 성공했습니다. ::" << endl;
					cout << ":: 피해 없음 ::" << endl;
					cout << endl;
				}
				else if (a > 33 && a <= 66)
				{
					_User->Damage(_Enemy->GetM_ATT());

					system("cls");
					_User->Profile();
					cout << "\tVS" << endl;
					_Enemy->Show_M_Profile();

					cout << ":: 플레이어는 방어에 실패했습니다. ::" << endl;
					cout << endl;
					cout << "몬스터의 공격!" << endl;
					cout << "플레이어는 " << _Enemy->GetM_ATT() << "만큼의 데미지를 입었다." << endl;
					cout << endl;
					if (_User->GetP_HP() <= 0)
					{
						cout << "플레이어가 쓰러졌습니다. 전투를 종료합니다." << endl;
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

					cout << ":: 플레이어는 적의 공격을 막아내고 반격했습니다. ::" << endl;
					cout << endl;
					cout << "플레이어의 반격!" << endl;
					cout << "몬스터는 " << _User->GetP_ATT() << "만큼의 데미지를 입었다." << endl;
					cout << endl;
					if (_Enemy->GetM_HP() <= 0)
					{
						cout << "적이 쓰러졌습니다. 전투를 종료합니다." << endl;
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
				cout << "[1]~[5]: 사용, [0]: 이전 화면으로" << endl;
				cout << ">> ";
				cin >> select_Battle_Inven;
				switch (select_Battle_Inven)
				{
				case 0:
					break;
				default:
					if (_Bag->Get_Inven_Potion().empty())
					{
						cout << "아무것도 없습니다." << endl;
						Sleep(1000);
						break;
					}
					else if (_Bag->Get_Inven_Potion().find(select_Battle_Inven)->second == "Hp 회복 포션")
					{
						cout << "사용했습니다." << endl;
						_User->HP_Heal(_ItemList->HpPotion->Get_PotionHp());
						_Bag->Potion_Erase(select_Battle_Inven);
						Sleep(1000);
						break;
					}
					else if (_Bag->Get_Inven_Potion().find(select_Battle_Inven)->second == "공격력 증가 포션")
					{
						cout << "사용했습니다." << endl;
						Used_Item++;
						_User->Att_Plus(_ItemList->AttPorion->Get_PotionAtt());
						_Bag->Potion_Erase(select_Battle_Inven);
						Sleep(1000);
						break;
					}
					else
					{
						cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
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
					cout << "도망치는데 성공했습니다." << endl;
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

					cout << "도망치는데 실패했습니다." << endl;
					cout << endl;
					cout << "몬스터의 공격!" << endl;
					cout << "플레이어는 " << _Enemy->GetM_ATT() << "만큼의 데미지를 입었다." << endl;
					if (_User->GetP_HP() <= 0)
					{
						cout << "플레이어가 쓰러졌습니다. 전투를 종료합니다." << endl;
						delete _User;
						_GamePlay = 0;
					}
					Sleep(1000);
				}
				break;
			default:
				cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
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
			cout << "가방이 가득 찼습니다." << endl;
			Sleep(1000);
		}
		else
		{
			if (_Enemy->GetM_Name() == "들쥐")
			{
				cout << "전리품으로 " << _ItemList->Item1->Get_DropName() << "을 얻었습니다." << endl;
				_Bag->Other_insert(1, _ItemList->Item1->Get_DropName());

			}
			else if (_Enemy->GetM_Name() == "골렘")
			{
				cout << "전리품으로 " << _ItemList->Item2->Get_DropName() << "을 얻었습니다." << endl;
				_Bag->Other_insert(1, _ItemList->Item2->Get_DropName());
			}
			else if (_Enemy->GetM_Name() == "스켈레톤")
			{
				cout << "전리품으로 " << _ItemList->Item3->Get_DropName() << "을 얻었습니다." << endl;
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
			cout << "구매하실 아이템의 종류를 선택하여주십시오." << endl;
			cout << "[1]: 장비, [2]: 포션, [0]: 이전 화면으로" << endl;
			cout << ">> ";
			cin >> select_Shop_Do;
			switch (select_Shop_Do)
			{
			case 1: //장비
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
							cout << "가방이 가득 차 구매할 수 없습니다." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->IronSword->Get_WeaponPrice())
						{
							cout << "소지금이 부족합니다." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "장비 " << _ItemList->IronSword->Get_WeaponName() << "을 구매하셨습니다." << endl;
							cout << "-" << _ItemList->IronSword->Get_WeaponPrice() << "G" << endl;
							_User->PayGold(_ItemList->IronSword->Get_WeaponPrice());
							_Bag->Equip_insert(1, _ItemList->IronSword->Get_WeaponName());
							Sleep(1000);
							break;
						}
					case 2:
						if (_Bag->Get_Equip_Count() == 0)
						{
							cout << "가방이 가득 차 구매할 수 없습니다." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->IronArmor->Get_ArmorPrice())
						{
							cout << "소지금이 부족합니다." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "장비 " << _ItemList->IronArmor->Get_ArmorName() << "을 구매하셨습니다." << endl;
							cout << "-" << _ItemList->IronArmor->Get_ArmorPrice() << "G" << endl;
							_User->PayGold(_ItemList->IronArmor->Get_ArmorPrice());
							_Bag->Equip_insert(1, _ItemList->IronArmor->Get_ArmorName());
							Sleep(1000);
							break;
						}
						//case 3:
					case 0:
						cout << "이전 화면으로 돌아갑니다." << endl;
						Sleep(1000);
						break;
					default:
						cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
						Sleep(1000);
						break;
					}
				} while (select_Shop_Equip != 0);
				break;
			case 2: //포션
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
							cout << "가방이 가득 차 구매할 수 없습니다." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->HpPotion->Get_PotionPrice())
						{
							cout << "소지금이 부족합니다." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "포션 " << _ItemList->HpPotion->Get_PotionName() << "을 구매하셨습니다." << endl;
							cout << "-" << _ItemList->HpPotion->Get_PotionPrice() << "G" << endl;
							_User->PayGold(_ItemList->HpPotion->Get_PotionPrice());
							_Bag->Potion_insert(1, _ItemList->HpPotion->Get_PotionName());
							Sleep(1000);
							break;
						}
					case 2:
						if (_Bag->Get_Potion_Count() == 0)
						{
							cout << "가방이 가득 차 구매할 수 없습니다." << endl;
							Sleep(1000);
							break;
						}
						if (_User->Get_GOLD() < _ItemList->AttPorion->Get_PotionPrice())
						{
							cout << "소지금이 부족합니다." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "포션 " << _ItemList->AttPorion->Get_PotionName() << "을 구매하셨습니다." << endl;
							cout << "-" << _ItemList->AttPorion->Get_PotionPrice() << "G" << endl;
							_User->PayGold(_ItemList->AttPorion->Get_PotionPrice());
							_Bag->Potion_insert(1, _ItemList->AttPorion->Get_PotionName());
							Sleep(1000);
							break;
						}
						//case 3:
					case 0:
						cout << "이전 화면으로 돌아갑니다." << endl;
						Sleep(1000);
						break;
					default:
						cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
						Sleep(1000);
						break;
					}
				} while (select_Shop_Potion != 0);
				break;
			}//구입
			break;
		case 2:
			cout << "판매하실 아이템의 종류를 선택해주십시오." << endl;
			cout << "[1]: 장비, [2]: 포션, [3]: 전리품, [0]: 이전 화면으로" << endl;
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
					cout << "무엇을 판매하시겠습니까?" << endl;
					cout << "판매가는 구입가의 70%" << endl;
					cout << "[1]~[5]: 판매, [0]: 이전 화면으로" << endl;
					cout << ">> ";
					cin >> select_Shop_Equip;
					switch (select_Shop_Equip)
					{
					case 0:
						cout << "이전 화면으로 돌아갑니다." << endl;
						Sleep(1000);
						break;
					default:
						if (_Bag->Get_Inven_Equip().empty())
						{
							cout << "아무것도 없습니다." << endl;
							Sleep(1000);
							break;
						}
						else
						{
							if (_Bag->Get_Inven_Equip().find(select_Shop_Equip)->second == "강철 검")
							{
								cout << "장비 " << _ItemList->IronSword->Get_WeaponName() << "을 판매하셨습니다." << endl;
								cout << "+" << _ItemList->IronSword->Get_WeaponSPrice() << "G" << endl;
								_User->ReceiveGold(_ItemList->IronSword->Get_WeaponSPrice());
								_Bag->Equip_Erase(select_Shop_Equip);
								Sleep(1000);
								break;
							}
							else if (_Bag->Get_Inven_Equip().find(select_Shop_Equip)->second == "강철 갑옷")
							{
								cout << "장비 " << _ItemList->IronArmor->Get_ArmorName() << "을 판매하셨습니다." << endl;
								cout << "+" << _ItemList->IronArmor->Get_ArmorSPrice() << "G" << endl;
								_User->ReceiveGold(_ItemList->IronArmor->Get_ArmorSPrice());
								_Bag->Equip_Erase(select_Shop_Equip);
								Sleep(1000);
								break;
							}
							else
							{
								cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
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
					cout << "무엇을 판매하시겠습니까?" << endl;
					cout << "판매가는 구입가의 70%" << endl;
					cout << "[1]~[5]: 판매, [0]: 이전 화면으로" << endl;
					cout << ">> ";
					cin >> select_Shop_Potion;
					switch (select_Shop_Potion)
					{
					case 0:
						cout << "이전 화면으로 돌아갑니다." << endl;
						Sleep(1000);
						break;
					default:
						if (_Bag->Get_Inven_Potion().empty())
						{
							cout << "아무것도 없습니다." << endl;
							Sleep(1000);
							break;
						}
						if (_Bag->Get_Inven_Potion().find(select_Shop_Potion)->second == "Hp 회복 포션")
						{
							cout << "장비 " << _ItemList->HpPotion->Get_PotionName() << "을 판매하셨습니다." << endl;
							cout << "+" << _ItemList->HpPotion->Get_PotionSPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->HpPotion->Get_PotionSPrice());
							_Bag->Potion_Erase(select_Shop_Potion);
							Sleep(1000);
							break;
						}
						else if (_Bag->Get_Inven_Potion().find(select_Shop_Potion)->second == "공격력 증가 포션")
						{
							cout << "장비 " << _ItemList->AttPorion->Get_PotionName() << "을 판매하셨습니다." << endl;
							cout << "+" << _ItemList->AttPorion->Get_PotionSPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->AttPorion->Get_PotionSPrice());
							_Bag->Potion_Erase(select_Shop_Potion);
							Sleep(1000);
							break;
						}
						else
						{
							cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
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
					cout << "무엇을 판매하시겠습니까?" << endl;
					cout << "[1]~[5]: 판매, [0]: 이전 화면으로" << endl;
					cout << ">> ";
					cin >> select_Shop_Other;
					switch (select_Shop_Other)
					{
					case 0:
						cout << "이전 화면으로 돌아갑니다." << endl;
						Sleep(1000);
						break;
					default:
						if (_Bag->Get_Inven_Other().empty())
						{
							cout << "아무것도 없습니다." << endl;
							Sleep(1000);
							break;
						}
						if (_Bag->Get_Inven_Other().find(select_Shop_Other)->second == "들쥐의 꼬리")
						{
							cout << "전리품 " << _ItemList->Item1->Get_DropName() << "을 판매하셨습니다." << endl;
							cout << "+" << _ItemList->Item1->Get_DropPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->Item1->Get_DropPrice());
							_Bag->Other_Erase(select_Shop_Other);
							Sleep(1000);
							break;
						}
						else if (_Bag->Get_Inven_Other().find(select_Shop_Other)->second == "골렘의 돌 조각")
						{
							cout << "전리품 " << _ItemList->Item2->Get_DropName() << "을 판매하셨습니다." << endl;
							cout << "+" << _ItemList->Item2->Get_DropPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->Item2->Get_DropPrice());
							_Bag->Other_Erase(select_Shop_Other);
							Sleep(1000);
							break;
						}
						else if (_Bag->Get_Inven_Other().find(select_Shop_Other)->second == "스켈레톤의 뼛조각")
						{
							cout << "전리품 " << _ItemList->Item3->Get_DropName() << "을 판매하셨습니다." << endl;
							cout << "+" << _ItemList->Item3->Get_DropPrice() << "G" << endl;
							_User->ReceiveGold(_ItemList->Item3->Get_DropPrice());
							_Bag->Other_Erase(select_Shop_Other);
							Sleep(1000);
							break;
						}
						else
						{
							cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
							Sleep(1000);
							break;
						}
					break;
					}
				} while (select_Shop_Other != 0);
				break;
			case 0:
				cout << "이전 화면으로 돌아갑니다." << endl;
				Sleep(1000);
				break;
			default:
				cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
				Sleep(1000);
				break;
			}
			break;
		case 0:
			cout << "상점을 나섭니다." << endl;
			Sleep(2000);
			break;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주십시오." << endl;
			Sleep(1000);
			break;
		}
	} while (select_Shop != 0);
}

void Game::Rest()
{
	cout << ":: 휴식 ::" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "." << endl;
		Sleep(500);
	}
	_User->Rest(_User->GetP_HP());

	Sleep(1000);
}