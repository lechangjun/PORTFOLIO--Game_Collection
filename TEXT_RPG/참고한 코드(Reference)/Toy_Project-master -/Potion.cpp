#include "Potion.h"

 Potion::Potion(const std::string& name, const int& h_value, const int& m_value, const int& price)
{
	setName(name);
	setHpUp(h_value);
	setMpUp(m_value);
	setPrice(price);
}

  void Potion::setName(const std::string name)
 {
	 _pName = name;
 }

 void Potion::setHpUp(const int& h_value)
 {
	 _pHpUp = h_value;
 }

 void Potion::setMpUp(const int& m_value)
 {
	 _pMpUp = m_value;
 }

  void Potion::setPrice(const int& price)
 {
	 _pPrice = price;
 }
