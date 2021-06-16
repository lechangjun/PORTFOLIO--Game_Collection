#pragma once

#include<string>
#include<iostream>
class Armor
{
private:
	std::string	_aName;
	int			_aPrice; //������ ����
	int			_aLevel;//��� �䱸 ���� 
	int			_aSTR; //��� �䱸 �� ����
	int			_aDEX; //��� �䱸 ��ø ����
	int			_aINT; //��� �䱸���� ����
	int			_aLUK; //��� �䱸  �� ����
	int			_aMax; //�ִ� ����

public:

	Armor(const std::string& name="Armor", const int& price=0, const int& level=0, const int& str=0, const int& dex=0, const int& Int=0, const int& lux=0, const int& max=0);

	void setName(const std::string& name);

	void setPrice(const int& price);

	void setLevel(const int& level);

	void setSTR(const int& str);

	void setDEX(const int& dex);

	void setINT(const int& Int);

	void setLUX(const int& lux);

	void setMAX(const int& max);

	friend std::ostream& operator<< (std::ostream& out, const Armor& arm)
	{
		out << "Name:" << arm._aName << "\t" << "Price:" << arm._aPrice << "\t" << "required Level:" << arm._aLevel << "\t" << "required STR:" << arm._aSTR << "\t" << "required DEX:" << arm._aDEX << "\t"<<"required INT:" << arm._aINT << "\t" << "required LUX:" << arm._aLUK << "\t" << "Defense Max:" << arm._aMax << " ";
		return out;
	}

	~Armor() {}

};

