#pragma once

#include<array>
#include<iostream>
#include<vector>

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
