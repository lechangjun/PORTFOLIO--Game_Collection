#pragma once


class CCharacter;
class CInventory;

class CInventoryMgr
{
private:
	CCharacter* m_pCharacter;
	CInventory* m_pInventory;
public:
	CInventoryMgr(CCharacter* _character);
	~CInventoryMgr();
	void Process();
	void Release();
private:
	void ShowInventory();
	void ShowWeaponBag();
	void ShowPotionBag();
	void ShowGemBag();
		
};