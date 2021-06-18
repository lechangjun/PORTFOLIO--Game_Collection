#pragma once

class CMonster;
class CCharacter;
class CFactory;

class CField
{
public:
	CField(CCharacter* _player, CFactory* _factory);
	void Process();
	~CField();


private:
	COMBAT Combat(CCharacter* character, CMonster* monster);

private:
	CCharacter* m_pCharacter;
	CFactory* m_pFactory;
	void EnterDungeon(HABITAT habitat);
};

