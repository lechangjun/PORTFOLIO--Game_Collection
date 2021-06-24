#pragma once

#include<string>
#include<iostream>

class Weapon
{
private:
	std::string _wName; //장비 이름	
	int			_wPrice; //장비 가격
	int			_wLevel;//장비 요구 레벨 
	int			_wSTR; //장비 요구 힘 스텟
	int			_wDEX; //장비 요구 민첩 스텟
	int			_wINT; //장비 요구지능 스텟
	int			_wLUK; //장비 요구  럭 스텟
	int			_wMin; //최소 공격력
	int			_wMax; //최대 공격력

public:

	Weapon(const std::string& name="weapon", const int& price=0, const int& level=0, const int& str=0, const int& dex=0, const int& Int=0, const int& lux=0, const int& min=0, 
		const int& max=0);

	void setName(const std::string& name);

	void setPrice(const int& price);

	void setLevel(const int& level);

	void setSTR(const int& str);

	void setDEX(const int& dex);

	void setINT(const int& Int);

	void setLUX(const int& lux);

	void setMIN(const int& min);

	void setMAX(const int& max);

	friend std::ostream& operator<< (std::ostream& out, const Weapon& wea)
	{
		out <<"Name:"<<wea._wName<<"\t"<<"Price:"<<wea._wPrice <<" \t"<<"required Level:"<<wea._wLevel <<" \t"<<"required STR:"<<wea._wSTR<<" \t"<< "required DEX:" << wea._wDEX << "\t "
			"required INT:" << wea._wINT << " \t"<<"required LUX:" << wea._wLUK << "\t " << "Damage Min:" << wea._wMin << "\t " << "required Max:" << wea._wMax << " ";
		return out;
	}

	~Weapon(){}

};

