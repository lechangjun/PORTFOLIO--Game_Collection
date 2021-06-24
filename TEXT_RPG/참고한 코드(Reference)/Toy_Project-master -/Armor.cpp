#include "Armor.h"

 Armor::Armor(const std::string& name, const int& price, const int& level, const int& str, const int& dex, const int& Int, const int& lux, const int& max)
{
	setName(name);
	setPrice(price);
	setLevel(level);
	setSTR(str);
	setDEX(dex);
	setINT(Int);
	setLUX(lux);
	setMAX(max);
}

  void Armor::setName(const std::string& name)
 {
	 _aName = name;
 }

   void Armor::setPrice(const int& price)
  {
	  _aPrice = price;
  }

    void Armor::setLevel(const int& level)
   {
	   _aLevel = level;
   }

	void Armor::setSTR(const int& str)
	{
		_aSTR = str;
	}

	void Armor::setDEX(const int& dex)
	 {
		 _aDEX = dex;
	 }

	void Armor::setINT(const int& Int)
	  {
		  _aINT = Int;
	  }

	 void Armor::setLUX(const int& lux)
	   {
		   _aLUK = lux;
	   }

	void Armor::setMAX(const int& max)
		 {
			 _aMax = max;
		 }
