#include "Weapon.h"

 Weapon::Weapon(const std::string& name, const int& price, const int& level, const int& str, const int& dex, const int& Int, const int& lux, const int& min, const int& max)
{
	setName(name);
	setPrice(price);
	setLevel(level);
	setSTR(str);
	setDEX(dex);
	setINT(Int);
	setLUX(lux);
	setMIN(min);
	setMAX(max);
}

  void Weapon::setName(const std::string& name)
 {
	 _wName = name;
 }

   void Weapon::setPrice(const int& price)
  {
	  _wPrice = price;
  }

   void Weapon::setLevel(const int& level)
  {
	  _wLevel = level;
  }

   void Weapon::setSTR(const int& str)
  {
	  _wSTR = str;
  }

   void Weapon::setDEX(const int& dex)
  {
	  _wDEX = dex;
  }

   void Weapon::setINT(const int& Int)
  {
	  _wINT = Int;
  }

   void Weapon::setLUX(const int& lux)
  {
	  _wLUK = lux;
  }

   void Weapon::setMIN(const int& min)
  {
	  _wMin = min;
  }

   void Weapon::setMAX(const int& max)
  {
	  _wMax = max;
  }
