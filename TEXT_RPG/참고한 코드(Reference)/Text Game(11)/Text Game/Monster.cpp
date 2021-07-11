#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
{
	M_Create();
}

Monster::~Monster()
{
	
}

void Monster::M_Create()
{
	M_Select();
	M_Profile(MonsterType(M_Num));
}

int Monster::M_Select()
{
	srand(size_t(time(NULL)));
	M_Num = rand() % 3;
	return M_Num;
}

void Monster::M_Profile(MonsterType(Num))
{
	srand(size_t(time(NULL)));

	switch (Num)
	{
		case MonsterType::Rat:
			M_Name = "µÈ¡„";
			M_MAXHP = 10;
			M_HP = 10;
			M_ATT = 5;
			break;
		case MonsterType::Golem:
			M_Name = "∞Ò∑Ω";
			M_MAXHP = 25;
			M_HP = 25;
			M_ATT = 10;
			break;
		case MonsterType::Skeleton:
			M_Name = "Ω∫ƒÃ∑π≈Ê";
			M_MAXHP = 30;
			M_HP = 30;
			M_ATT = 15;
			break;
	}
}

void Monster::Show_M_Profile()
{
	if (M_HP <= 0)
	{
		M_HP = 0;
	}
	cout << ":: ∏ÛΩ∫≈Õ " << M_Name << "::" << endl;
	cout << "√º∑¬: " << this->GetM_MAXHP() << "/" << this->GetM_HP() << endl;
	cout << "∞¯∞›∑¬: " << this->GetM_ATT() << endl;
	cout << "==================================" << endl;
}

void Monster::Damage(int val)
{
	M_HP -= val;
}