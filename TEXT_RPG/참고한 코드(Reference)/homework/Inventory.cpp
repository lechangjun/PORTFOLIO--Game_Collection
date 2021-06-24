#include "stdafx.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Bufitem.h" // ������ �̹� ����.
#include "Potion.h"

CInventory::CInventory()
{
	potionIndex = -1;
	weaponIndex = -1;
	gemIndex = -1;
	currWeapon = new CWeapon;
}

CInventory::~CInventory()
{
	delete currWeapon;

	for (int i = 0; i < potionIndex + 1; ++i)
	{
		delete potions[i];
	}

	for (int i = 0; i < weaponIndex + 1; ++i)
	{
		delete weapons[i];
	}

	for (int i = 0; i < gemIndex + 1; ++i)
	{
		delete gems[i];
	}
}


CPotion* CInventory::GetPotion(int _index)
{
	if (isVaildIndex(potionIndex, _index))
		return potions[_index];
	return nullptr;
}

CWeapon * CInventory::GetWeapon(int _index)
{
	if (isVaildIndex(weaponIndex, _index))
		return weapons[_index];
	return nullptr;
}

CBufItem * CInventory::GetGem(int _index)
{
	if (isVaildIndex(gemIndex, _index))
		return gems[_index];
	return nullptr;
}

void CInventory::DeletePotion(int _index)
{
	if (!isVaildIndex(potionIndex, _index))
		return;

	//��ĭ�� ������ ����
	for (int i = _index; i < potionIndex; ++i)
	{
		potions[i] = potions[i + 1];
	}
	//ũ�� ���̱�
	--potionIndex;
}

void CInventory::DeleteWeapon(int _index)
{
	if (!isVaildIndex(weaponIndex, _index))
		return;
	//���� ����� ���������Ͱ� ����Ű�� ������ �������. ���� ������ü�� ���ִ°� �ƴ϶� �κ��丮���� ������(������ �׸�)�� ���ְ� ���� ���̹Ƿ� ������ �ʴ´�.
	//delete weapons[_index];

	//��ĭ�� ������ ����
	for (int i = _index; i < weaponIndex; ++i)
	{
		//���, �����.
		weapons[i] = weapons[i + 1];
	}
	--weaponIndex;
}

void CInventory::DeleteGem(int _index)
{
	if (!isVaildIndex(gemIndex, _index))
		return;

	//��ĭ�� ������ ����
	for (int i = _index; i < gemIndex; ++i)
	{
			gems[i] = gems[i + 1];
	}
	--gemIndex;
}

void CInventory::InsertPotion(CPotion* _potion)
{
	if(!isFull(potionIndex))
		potions[++potionIndex] = _potion;
}

void CInventory::InsertWeapon(CWeapon* _weapon)
{
	if(!isFull(weaponIndex))
		weapons[++weaponIndex] = _weapon;
}

void CInventory::InsertGem(CBufItem* _gem)
{
	if(!isFull(gemIndex))
		gems[++gemIndex] = _gem;
}




int CInventory::GetInventorySize()
{
	int size = (potionIndex + 1) + (weaponIndex + 1) + (gemIndex + 1);
	return size;
}


int CInventory::GetPotionSize() const
{

	return potionIndex + 1;
}

int CInventory::GetWeaponSize() const
{
	return weaponIndex + 1;
}

int CInventory::GetGemSize() const
{
	return gemIndex + 1;
}

bool CInventory::isPotionEmpty()
{
	return potionIndex == -1;
}

bool CInventory::isWeaponEmpty()
{
	return weaponIndex == -1;
}

bool CInventory::isGemEmpty()
{
	return gemIndex == -1;
}

//��谪 �˻�
bool CInventory::isVaildIndex(int _invenIndex, int _factor)
{

	//factor�� �ε��� �����ȿ� ������
	if (_factor <= _invenIndex && _factor >= 0)
	{
		//��ȿ�� ����
		return true;
	}
	//�ƴϸ� ��ȿ���� ����
	cout << "�߸��� �κ��丮 �׸� ����!" << endl;
	cout << "�κ��丮 �ε���: " << _invenIndex << "���� ��: :" << _factor << endl;
	system("pause");
	return false;

}

//�ش� �κ��丮 �׸��� �����ִ���
bool CInventory::isFull(int _invenIndex)
{
	if (_invenIndex + 1 >= MAX_INVENTORY_SIZE)
	{
		return true;
		cout << "�κ��丮 ������ �ʰ�!" << endl;
		system("pause");
	}
	return false;
}




