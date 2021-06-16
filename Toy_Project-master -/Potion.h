#pragma once

#include<iostream>
#include<string>
class Potion
{
private:
	std::string _pName;
	int			_pHpUp; //potion hp up
	int			_pMpUp;
	int			_pPrice;

public:

	Potion(const std::string& name="Æ÷¼Ç",const int& h_value=0, const int& m_value=0,const int& price=0);

	void setName(const std::string name);

	void setHpUp(const int& h_value);

	void setMpUp(const int& m_value);

	void setPrice(const int& price);

	friend std::ostream& operator<< (std::ostream& out, const Potion& potion)
	{
		out << "Name:" << potion._pName << "\t" << "Price:" << potion._pPrice << "\t" << "_pHpUp:" << potion._pHpUp << "\t" << "_pMpUp:" << potion._pMpUp;
		return out;
	}

	~Potion() {}
};

