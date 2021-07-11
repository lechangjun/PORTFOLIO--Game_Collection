#pragma once
#include "stdafx.h"

class Inventory
{
private:
	map<int, string> _Equip;
	int Equip_Count;
	map<int, string> _Potion;
	int Potion_Count;
	map<int, string> _Other;
	int Other_Count;
protected:

public:
	Inventory();
	~Inventory();

	map<int, string>& Get_Inven_Equip() { return _Equip; }
	int Get_Equip_Count() { return Equip_Count; }
	void Equip_insert(int key, string value);
	void Equip_Erase(int key);
	
	map<int, string>& Get_Inven_Potion() { return _Potion; }
	int Get_Potion_Count() { return Potion_Count; }
	void Potion_insert(int key, string value);
	void Potion_Erase(int key);

	map<int, string>& Get_Inven_Other() { return _Other; }
	int Get_Other_Count() { return Other_Count; }
	void Other_insert(int key, string value);
	void Other_Erase(int key);

	void Show_Inventory_E();
	void Show_Inventory_P();
	void Show_Inventory_O();
};