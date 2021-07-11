#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Inventory.h"
#include "Store.h"

class Game
{
private:
	Player* _User;
	Monster* _Enemy;
	ItemList* _ItemList;
	Inventory* _Bag;
	Store* _Shop;

	string P_Name;

	int select_GamePlay;
	int select_Inventory;
	int select_Inven_Equip;
	int select_Inven_Potion;
	int select_Inven_Other;

	int select_Battle;
	int select_Battle_Inven;
	int Used_Item;

	int select_Shop;
	int select_Shop_Do;
	int select_Shop_Equip;
	int select_Shop_Potion;
	int select_Shop_Other;
protected:

public:
	Game();
	~Game();

	void GamePlay();
	bool _GamePlay;
	void Game_Interface();

	void Inven();
	bool _Inven;

	void Battle();
	bool _Battle;
	void Drop_Item();

	void Shop();

	void Rest();
};