#pragma once
#include "stdafx.h"
#include "Inventory.h"

class Player
{
	string Name;
	int P_MAXHP = 100;
	int P_HP = 100;
	int P_ATT = 20;

	int GOLD = 1000;

	int Set_Item1 = 0;
	int Set_Item2 = 0;
protected:
public:
	Player();
	~Player();

	void NickName(string P_Name);

	int GetP_MAXHP() { return P_MAXHP; }
	int GetP_HP() { return P_HP; }
	int GetP_ATT() { return P_ATT; }
	int Get_GOLD() { return GOLD; }
	int Get_Set_Item1() { return Set_Item1; }
	int Get_Set_Item2(){ return Set_Item2; }

	void Profile();
	void Show_P_Inventory(); 

	void Damage(int val);
	void Rest(int val);
	void PlusGold(int val);
	void PayGold(int val);
	void ReceiveGold(int val);

	void Att_Plus(int val);
	void Att_Return(int val);
	void M_HP_Plus(int val);

	void HP_Heal(int val);
};
