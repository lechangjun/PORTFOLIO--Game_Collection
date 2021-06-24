#include "stdafx.h"
#include "Factory.h"
#include "Bufitem.h"
#include "Weapon.h"
#include "Potion.h"
#include "Monster.h"


int CFactory::GetInfo(char(**items)[CHAR_PER_LINE], char path[30])
{
	//아이템 목록에서 아이템의 수
	int itemCount = 0;

	FILE* fp = nullptr;

	char cnt[4] = "";
	int cntIndex = 0;

	errno_t err = fopen_s(&fp, path, "rt");
	if (0 == err)
	{
		//아이템 인덱스
		int col = 0;
		int row = 0;
		int c = 0;
		//정보를 읽어도 되나?
		bool infoStart = false;


		//파일이 끝날때까지 문자를 받아옴
		while (EOF != c)
		{

			//문자를 하나하나 가져옴
			c = getc(fp);

			if (EOF == c)
				continue;
			//주석 무시
			if ('*' == c)
			{
				//개행할때까지 읽는다.
				while ('\n' != c)
				{
					c = getc(fp);
				}
				//이제 다음 줄이지만 c는 여전히 '\n'이니 컨티뉴
				continue;
			}

			//첫행이면 총 아이템 수를 받아오고, 개행할때까지 무시
			if (col == 0 && !infoStart)
			{
				while ('\n' != c)
				{
					cnt[cntIndex] = c;
					++cntIndex;
					c = getc(fp);
				}

				CParser parser;
				itemCount = parser.StringToInt(cnt);
				//아이템 정보를 저장할 배열 동적생성
				*items = new char[itemCount][CHAR_PER_LINE];
				//널문자로 초기화
				memset(*items, '\0', (sizeof(char) * CHAR_PER_LINE) * itemCount);
				infoStart = true;
				continue;
			}

			//이제 아이템 정보 읽어오기 시작
			//개행할시 인덱스 초기화. 쉼표단위로 파싱할때 문장의 끝을 알리기 위해 개행문자도 넣는다.
			if ('\n' == c)
			{
				(*items)[col][row] = c;
				++col;
				row = 0;
			}
			//아니면 열을 증가시키며 받아온 문자 넣기. 
			else
			{
				(*items)[col][row] = c;
				++row;
			}

		}


		fclose(fp);

	}
	else
		cout << "파일 개방 실패!" << endl;



	return itemCount;

}

void CFactory::CreateAllWeapons()
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*weaponInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&weaponInfos, "../Data/weapon.txt");

	weapons = new CWeapon[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[7][DESCRIPTION_LENGTH] = {};

		int len = strlen(weaponInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//쉼표면 word의 다음 행을 채운다.
			if (',' == weaponInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == weaponInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = weaponInfos[i][j];
				++row;
			}
		}

		CParser parser;
		weapons[i].id = parser.StringToInt(word[0]);
		strcpy_s(weapons[i].GFX_PATH, GFX_PATH_LENGTH, word[1]);
		strcpy_s(weapons[i].name, 16, word[2]);
		weapons[i].attack = parser.StringToInt(word[3]);
		strcpy_s(weapons[i].description, DESCRIPTION_LENGTH, word[4]);
		weapons[i].price = parser.StringToInt(word[5]);
		weapons[i].occupation = (OCCUPATION)parser.StringToInt(word[6]);
		weapons[i].gem = new CBufItem;
		(*weapons[i].gem) = {};
		strcpy_s(weapons[i].gem->name, ITEM_NAME_LENGTH, "부착안함");
		weapons[i].element = ELEMENT_END;

	}

	delete[] weaponInfos;
	weaponInfos = nullptr;

	weaponCnt = itemCount;
}

void CFactory::CreateAllMonsters()
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*monsterInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&monsterInfos, "../Data/monster.txt");
	monsters = new CMonster[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[11][DESCRIPTION_LENGTH] = {};

		int len = strlen(monsterInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//쉼표면 word의 다음 행을 채운다.
			if (',' == monsterInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == monsterInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = monsterInfos[i][j];
				++row;
			}
		}

		CParser parser;
		monsters[i].id = parser.StringToInt(word[0]);
		strcpy_s(monsters[i].name, ITEM_NAME_LENGTH, word[1]);
		strcpy_s(monsters[i].GFX_PATH, GFX_PATH_LENGTH, word[2]);
		monsters[i].attack = parser.StringToInt(word[3]);
		monsters[i].maxHealth = parser.StringToInt(word[4]);
		monsters[i].currHealth = parser.StringToInt(word[5]);
		monsters[i].exp = parser.StringToInt(word[6]);
		monsters[i].gold = parser.StringToInt(word[7]);
		monsters[i].habitat = (HABITAT)parser.StringToInt(word[8]);
		monsters[i].spawnChance = parser.StringToFloat(word[9]);
		monsters[i].element = (ELEMENT)parser.StringToInt(word[10]);


	}

	delete[] monsterInfos;
	monsterInfos = nullptr;

	monsterCnt = itemCount;
}

void CFactory::CreateAllPotions()
{

	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*potionInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&potionInfos, "../Data/potion.txt");
	potions = new CPotion[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[7][800] = {};

		int len = strlen(potionInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{
			//word의 경계값을 넘어가면 무시
			if (col > 6 || row > 799)
			{
				continue;
			}
			//쉼표면 word의 다음 행을 채운다.
			if (',' == potionInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == potionInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = potionInfos[i][j];
				++row;
			}
		}
		CParser parser;
		potions[i].id = parser.StringToInt(word[0]);
		strcpy_s(potions[i].GFX_PATH, GFX_PATH_LENGTH, word[1]);
		strcpy_s(potions[i].name, ITEM_NAME_LENGTH, word[2]);
		potions[i].healAmount = parser.StringToInt(word[3]);
		strcpy_s(potions[i].description, DESCRIPTION_LENGTH, word[4]);
		potions[i].price = parser.StringToInt(word[5]);

	}

	delete[] potionInfos;
	potionInfos = nullptr;

	potionCnt = itemCount;
}

void CFactory::CreateAllbufItems()
{
	//무기에 대한 정보를 받을 이차원배열 포인터를 준비한다.
	char(*bufItemInfos)[CHAR_PER_LINE] = nullptr;

	//무기정보를 동적으로 할당받는다.
	int itemCount = GetInfo(&bufItemInfos, "../Data/bufItem.txt");
	bufItems = new CBufItem[itemCount];


	//쉼표로 끊으면서 무기 구조체에 대한 정보 셋팅
	for (int i = 0; i < itemCount; ++i)
	{
		//word의 행,열
		int col = 0, row = 0;
		//하나의 무기 구조체에 대한 정보.
		//description 항목때문에 모든 항목을 800개의 방으로 잡았다. 비효율적임. 개선 필요
		char word[12][800] = {};

		int len = strlen(bufItemInfos[i]);

		//쉼표단위로 파싱하기
		for (int j = 0; j < len; ++j)
		{

			//쉼표면 word의 다음 행을 채운다.
			if (',' == bufItemInfos[i][j])
			{
				++col;
				row = 0;
			}
			//개행문자면 빠져나간다.
			else if ('\n' == bufItemInfos[i][j])
			{
				break;
			}
			//이 모든게 아니면 데이터를 word 에 넣는다.
			else
			{
				word[col][row] = bufItemInfos[i][j];
				++row;
			}
		}
		CParser parser;
		bufItems[i].id = parser.StringToInt(word[0]);
		strcpy_s(bufItems[i].GFX_PATH, GFX_PATH_LENGTH, word[1]);
		strcpy_s(bufItems[i].name, ITEM_NAME_LENGTH, word[2]);
		bufItems[i].attackBuf = parser.StringToInt(word[3]);
		bufItems[i].maxHealthBuf = parser.StringToInt(word[4]);
		bufItems[i].levelBuf = parser.StringToInt(word[5]);
		bufItems[i].expBuf = parser.StringToInt(word[6]);
		bufItems[i].element = (ELEMENT)parser.StringToInt(word[7]);
		bufItems[i].isConsumable = parser.StringToBool(word[8]);
		strcpy_s(bufItems[i].description, DESCRIPTION_LENGTH, word[9]);
		bufItems[i].dropChance = parser.StringToFloat(word[10]);
		bufItems[i].price = parser.StringToInt(word[11]);

	}

	delete[] bufItemInfos;
	bufItemInfos = nullptr;

	bufItemCnt = itemCount;
}

void CFactory::Release()
{
	if (weapons)
	{
		delete[] weapons;
	}
	if (potions)
	{
		delete[] potions;
	}
	if (monsters)
	{
		delete[] monsters;
	}
	if (bufItems)
	{
		delete[] bufItems;
	}
}

CFactory::CFactory()
{
	CreateAllWeapons();
	CreateAllPotions();
	CreateAllMonsters();
	CreateAllbufItems();
}

CFactory::~CFactory()
{
	Release();
}

const CWeapon * const CFactory::GetWeapons() const
{

	return weapons;
}

const CMonster * const CFactory::GetMonsters() const
{
	return monsters;
}

const CPotion * const CFactory::GetPotions() const
{
	return potions;
}

const CBufItem * const CFactory::GetBufitems() const
{
	return bufItems;
}



int CFactory::GetWeaponsSize() const
{
	return weaponCnt;
}

int CFactory::GetMonstersSize() const
{
	return monsterCnt;
}

int CFactory::GetPotionsSize() const
{
	return potionCnt;
}

int CFactory::GetBufItemsSize() const
{
	return bufItemCnt;
}


CWeapon* CFactory::CreateWeapon(int id)
{
	CWeapon* weapon;
	//만약 id가 0이면 빈껍데기 만들기
	if (0 == id)
	{
		weapon = new CWeapon;
	}
	else
	{
		//id에 해당하는 무기 리턴
		weapon = new CWeapon;
		//원본의 젬에 대한 포인터까지 복사한다.(얕은복사)
		memcpy(weapon, &(weapons[id - 1]), sizeof(CWeapon));
		//원본 젬의 데이터만 뽑아냄
		CBufItem gemData = *(weapon->gem);
		//새로운 주소에 젬을 생성
		weapon->gem = new CBufItem;
		//그 주소에 젬 데이터를 복사.(깊은복사)
		*(weapon->gem) = gemData;
	}
	
	return weapon;

}


CMonster* CFactory::CreateMonster(int id)
{
	CMonster* monster = new CMonster;
	memcpy(monster, &(monsters[id - 1]), sizeof(CMonster));
	return monster;

}


CMonster* CFactory::CreateMonster(HABITAT habitat)
{

	int length = monsterCnt;

	//같은 서식지에 사는 몬스터들의 id. 최대 length(모든 몬스터의 수)만큼 있다.
	int* family = new int[length];
	float* spawnChance = new float[length];
	*family = {};
	*spawnChance = {};

	float chanceSum = 0;
	//family의 인덱스이자 +1은 family의 길이
	int index = 0;
	for (int i = 0; i < length; ++i)
	{
		if (monsters[i].habitat == habitat)
		{
			family[index] = monsters[i].id;
			spawnChance[index] = monsters[i].spawnChance;
			chanceSum += spawnChance[index];
			++index;
		}
	}


	//오름차순 정렬
	for (int i = 0; i < index; ++i)
	{
		for (int j = 0; j < index - 1 - i; ++j)
		{
			if (spawnChance[j] > spawnChance[j + 1])
			{
				float tmp = spawnChance[j + 1];
				spawnChance[j + 1] = spawnChance[j];
				spawnChance[j] = tmp;
				int tmp2 = family[j + 1];
				family[j + 1] = family[j];
				family[j] = tmp2;
			}
		}
	}


	// 확률로 나타나기

	//확률적으로 뽑은 숫자
	int randomNum = (rand() % (int)chanceSum) + 1;

	//누적확률
	float sum = 0.0f;
	int familyIndex = 0;
	for (int i = 0; i < index; ++i)
	{
		sum += spawnChance[i];
		if (sum >= randomNum)
		{
			familyIndex = i;
			break;
		}

	}

	//// index = 2
	//// 0 1 2 3
	//// 1 3
	//// family[0] family[1] 0 ~ index-1의 범위에서 랜덤으로 뽑은 아이디
	//int randomIndex = rand() % index;
	////랜덤으로 고른 몬스터의 아이디
	//int id = family[randomIndex];

	int idToSpawn = family[familyIndex];
	cout << "출현확률: " << (spawnChance[familyIndex] / chanceSum) * 100 << endl;
	system("pause");
	delete[] family;
	delete[] spawnChance;

	return CreateMonster(idToSpawn);

}

CPotion* CFactory::CreatePotion(int id)
{
	CPotion* potion = new CPotion;
	memcpy(potion, &(potions[id - 1]), sizeof(CPotion));
	return potion;

}


CBufItem* CFactory::CreateBufItem(int id)
{
	CBufItem* item = new CBufItem;
	memcpy(item, &(bufItems[id - 1]), sizeof(CBufItem));
	return item;
}


CBufItem* CFactory::CreateDropItem()
{
	float chanceSum = 0;

	int length = bufItemCnt;
	//오름차순 정렬
	for (int i = 0; i < length; ++i)
	{
		chanceSum += bufItems[i].dropChance;

		for (int j = 0; j < length - 1; ++j)
		{
			if (bufItems[j].dropChance > bufItems[j + 1].dropChance)
			{
				CBufItem tmp = bufItems[j];
				bufItems[j] = bufItems[j + 1];
				bufItems[j + 1] = tmp;

			}
		}
	}

	//확률적으로 뽑은 숫자
	int randomNum = (rand() % (int)chanceSum) + 1;

	//누적확률
	float sum = 0.0f;

	int toCreate = 0;
	for (int i = 0; i < length; ++i)
	{
		sum += bufItems[i].dropChance;
		if (sum >= randomNum)
		{
			toCreate = i;
			break;
		}

	}


	CBufItem* item = new CBufItem;
	memcpy(item, &(bufItems[toCreate]), sizeof(CBufItem));
	return item;
}