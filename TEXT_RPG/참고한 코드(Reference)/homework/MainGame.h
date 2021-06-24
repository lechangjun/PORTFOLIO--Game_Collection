#pragma once

class CCharacter;
class CFactory;
class CInventoryMgr;
class CMonster;
class CField;

class CMainGame
{
private:
	void EnterForge();
	void EnterPharmacy();
	void EnhanceWeaponPage();
	bool SelectPlayer();
	void Release();
	void Load();
	void Save();
public:
	CMainGame();
	~CMainGame();
	void Progress();
private:
	CCharacter* m_pCharacter;
	CFactory* m_pFactory;
	CInventoryMgr* m_pInventoryMgr;
	CField* m_pField;

};