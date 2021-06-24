#pragma once
#include "stdafx.h"

class CBufItem
{
public:
	int id = 0;
	char GFX_PATH[GFX_PATH_LENGTH];
	char name[ITEM_NAME_LENGTH];
	//���� �׸�
	int attackBuf;
	int maxHealthBuf;
	int levelBuf;
	int expBuf;
	//�������� �Ӽ�
	ELEMENT element;
	//�Ҹ� �������ΰ�?
	bool isConsumable;
	char description[DESCRIPTION_LENGTH];
	//��� Ȯ��
	float dropChance;
	//����
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

	std::vector<T> iarr; //���� ��ü�� �ڱ� ������ ������ ���� ���� ��

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
	iarr.resize(len); //�迭 ���̸̹� Ȯ���ϱ�
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


 ��� 


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
		std::cout << "�Ҹ��� ȣ��" << std::endl;
	}

};





*/