#include "stdafx.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Bufitem.h" // 웨폰에 이미 있음.
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

	//한칸씩 앞으로 당기기
	for (int i = _index; i < potionIndex; ++i)
	{
		potions[i] = potions[i + 1];
	}
	//크기 줄이기
	--potionIndex;
}

void CInventory::DeleteWeapon(int _index)
{
	if (!isVaildIndex(weaponIndex, _index))
		return;
	//만약 지우면 웨폰포인터가 가리키는 웨폰이 사라진다. 나는 웨폰자체를 없애는게 아니라 인벤토리에서 포인터(아이템 항목)를 없애고 싶은 것이므로 지우지 않는다.
	//delete weapons[_index];

	//한칸씩 앞으로 당기기
	for (int i = _index; i < weaponIndex; ++i)
	{
		//대신, 덮어쓴다.
		weapons[i] = weapons[i + 1];
	}
	--weaponIndex;
}

void CInventory::DeleteGem(int _index)
{
	if (!isVaildIndex(gemIndex, _index))
		return;

	//한칸씩 앞으로 당기기
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

//경계값 검사
bool CInventory::isVaildIndex(int _invenIndex, int _factor)
{

	//factor가 인덱스 범위안에 있으면
	if (_factor <= _invenIndex && _factor >= 0)
	{
		//유효한 접근
		return true;
	}
	//아니면 유효하지 않음
	cout << "잘못된 인벤토리 항목 접근!" << endl;
	cout << "인벤토리 인덱스: " << _invenIndex << "들어온 값: :" << _factor << endl;
	system("pause");
	return false;

}

//해당 인벤토리 항목이 꽉차있는지
bool CInventory::isFull(int _invenIndex)
{
	if (_invenIndex + 1 >= MAX_INVENTORY_SIZE)
	{
		return true;
		cout << "인벤토리 사이즈 초과!" << endl;
		system("pause");
	}
	return false;
}




