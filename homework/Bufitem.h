#pragma once
#include "stdafx.h"

class CBufItem
{
public:
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	//버프 항목
	int attackBuf;
	int maxHealthBuf;
	int levelBuf;
	int expBuf;
	//아이템의 속성
	ELEMENT element;
	//소모성 아이템인가?
	bool isConsumable;
	char description[DESCRIPTION_LENGTH];
	//드롭 확률
	float dropChance;
	//가격
	int price;
public:
	CBufItem();
	~CBufItem();
	void PrintGemInfo() const;
};
/*

template<typename T>
class Item
{
private:

	std::vector<T> iarr; //지금 객체가 자기 내용을 가지고 직접 들어가는 중

public:

	Item(int len=0);

	T& operator [] (int idx);
	T operator [] (int idx) const;
	int GetArrLen() const;
	fixed_vector() {}
	~Item() {};

	friend std::ostream& operator << ( std::ostream& out, const std::vector<T>& iarr )
	{
		out << iarr;

		return out;
	}

	std::vector<T> getiarr() const;
	void setiarr();


};

template<typename T>
Item<T>::Item(int len)
{
	iarr.resize(len); //배열 길이미리 확보하기
}

template<typename T>
T& Item<T>::operator [] (int idx)
{
	if (idx < 0 || idx >= iarr.size())
	{
		std::cout << "Resize the vecotr" << std::endl;
		iarr.resize(idx);
	}

	return iarr[idx];
}

template<typename T>
T Item<T>::operator [] (int idx) const
{
	if (idx < 0 || idx >= iarr.size())
	{
		std::cout << "Resize the vecotr" << std::endl;
		iarr.resize(idx);
	}

	return iarr[idx];
}

template<typename T>
int Item<T>::GetArrLen() const
{
	return  iarr.size();
}

template<typename T>
 std::vector<T> Item<T>::getiarr() const
{
	return iarr;
}

 template<typename T>
void Item<T>::setiarr()
 {

 }


 상속 


class Warrior : public Player
{

public:

	Warrior(std::string name="warrior", int hp = 500, int hpmax = 500, int mp = 100, int mpmax = 100, int level = 1, int str = 20, int dex = 5, int Int = 5, int luk = 10,
		int physicalattackmin = 5, int physicalattackmax = 10, int magicalattackmin = 0, int magicalattackmax = 0,
		double physicaldefenserate = 0.2, double magicaldefenserate = 0.1, int exp = 0, int expmax = 100) :
		Player(name, hp, hpmax, mp, mpmax, level, str, dex, Int, luk,
			physicalattackmin, physicalattackmax, magicalattackmin, magicalattackmax,
			physicaldefenserate, magicaldefenserate, exp, expmax)
	{}

	~Warrior()
	{
		std::cout << "소멸자 호출" << std::endl;
	}

};





*/