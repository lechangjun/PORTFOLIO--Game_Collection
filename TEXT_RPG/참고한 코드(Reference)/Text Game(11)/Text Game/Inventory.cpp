#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory()
{
	Equip_Count = 5;
	Potion_Count = 5;
	Other_Count = 5;
}

Inventory::~Inventory()
{
}

void Inventory::Equip_insert(int key, string value)
{
	Equip_Count--;
	if (_Equip.count(key) != 0 && _Equip.count(key + 3) != 0)
	{
		_Equip.insert(make_pair(key + 4, value));
	}
	else if (_Equip.count(key + 2) != 0)
	{
		_Equip.insert(make_pair(key + 3, value));
	}
	else if (_Equip.count(key + 1) != 0)
	{
		_Equip.insert(make_pair(key + 2, value));
	}
	else if (_Equip.count(key) != 0)
	{
		_Equip.insert(make_pair(key + 1, value));
	}
	if (_Equip.count(key) == 0)
	{
		_Equip.insert(make_pair(key, value));
	}
}

void Inventory::Equip_Erase(int key)
{
	Equip_Count++;
	_Equip.erase(key);
}

void Inventory::Potion_insert(int key, string value)
{
	Potion_Count--;
	if (_Potion.count(key) != 0 && _Potion.count(key + 3) != 0)
	{
		_Potion.insert(make_pair(key + 4, value));
	}
	else if (_Potion.count(key + 2) != 0)
	{
		_Potion.insert(make_pair(key + 3, value));
	}
	else if (_Potion.count(key + 1) != 0)
	{
		_Potion.insert(make_pair(key + 2, value));
	}
	else if (_Potion.count(key) != 0)
	{
		_Potion.insert(make_pair(key + 1, value));
	}
	if (_Potion.count(key) == 0)
	{
		_Potion.insert(make_pair(key, value));
	}
}

void Inventory::Potion_Erase(int key)
{
	Potion_Count++;
	_Potion.erase(key);
}

void Inventory::Other_insert(int key, string value)
{
	Other_Count--;
	if (_Other.count(key) != 0 && _Other.count(key + 3) != 0)
	{
		_Other.insert(make_pair(key + 4, value));
	}
	else if (_Other.count(key + 2) != 0)
	{
		_Other.insert(make_pair(key + 3, value));
	}
	else if (_Other.count(key + 1) != 0)
	{
		_Other.insert(make_pair(key + 2, value));
	}
	else if (_Other.count(key) != 0)
	{
		_Other.insert(make_pair(key + 1, value));
	}
	if (_Other.count(key) == 0)
	{
		_Other.insert(make_pair(key, value));
	}
}

void Inventory::Other_Erase(int key)
{
	Other_Count++;
	_Other.erase(key);
}

void Inventory::Show_Inventory_E()
{
	cout << ":: ��� ::" << endl;
	cout << endl;
	cout << "���� ���� ����: 5/" << Get_Equip_Count() << endl;

	if (_Equip.empty())
	{
		cout << "����ֽ��ϴ�." << endl;
	}
	else
	{
		for (auto iter = _Equip.begin(); iter != _Equip.end(); iter++)
		{
			cout << "[" << iter->first << "]: " << iter->second << endl;
		}
	}
}

void Inventory::Show_Inventory_P()
{
	cout << ":: ���� ::" << endl;
	cout << endl;
	cout << "���� ���� ����: 5/" << Get_Potion_Count() << endl;

	if (_Potion.empty())
	{
		cout << "����ֽ��ϴ�." << endl;
	}
	else
	{
		for (auto iter = _Potion.begin(); iter != _Potion.end(); iter++)
		{
			cout << "[" << iter->first << "]: " << iter->second << endl;
		}
	}
}

void Inventory::Show_Inventory_O()
{
	cout << ":: ����ǰ ::" << endl;
	cout << endl;
	cout << "���� ���� ����: 5/" << Get_Other_Count() << endl;

	if (_Other.empty())
	{
		cout << "����ֽ��ϴ�." << endl;
	}
	else
	{
		for (auto iter = _Other.begin(); iter != _Other.end(); iter++)
		{
			cout << "[" << iter->first << "]: " << iter->second << endl;
		}
	}
}