#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Damage(int val);
	void Phase1();

	
	int GetHp() { return hp; }
	int GetAttack() { return attack; }


private:
	int hp;
	int attack;
	int deffense;
	string name;
};