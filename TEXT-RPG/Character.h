#pragma once


class Character
{

public:
	Character();

	Character(int hp, int attack,int def, string name);

	Character(const Character& src);
	//Character(const Character& src) = default;
	//Character(const Character& src) = delete;


	Character& operator=(const Character& rhs);
	//Character& operator=(const Character& rhs) = default;
	//Character& operator=(const Character& rhs) = delete;

	Character& operator+(const string& rhs);




	//friend 클래스명

	~Character();

	void Func();

	int GetHp() { return hp; }
	int GetAttack() { return attack; }
	string GetName() { return name; }

	void SetHp(int val) { hp = val; }

	void Damage(int val) { hp -= val; }

private:
	int hp;
	int attack;
	int def;
	string name;

	/*const int temp;
	int& temp2;*/

	int size;
	int* ptrInt;

public:
	static int global;

	//class Character player

};

