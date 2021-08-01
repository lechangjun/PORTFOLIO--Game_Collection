#include "stdafx.h"
#include "Factory.h"
#include "Bufitem.h"
#include "Weapon.h"
#include "Potion.h"
#include "Monster.h"


int CFactory::GetInfo(char(**items)[CHAR_PER_LINE], char path[30])
{
	//������ ��Ͽ��� �������� ��
	int itemCount = 0;

	FILE* fp = nullptr;

	char cnt[4] = "";
	int cntIndex = 0;

	errno_t err = fopen_s(&fp, path, "rt");
	if (0 == err)
	{
		//������ �ε���
		int col = 0;
		int row = 0;
		int c = 0;
		//������ �о �ǳ�?
		bool infoStart = false;


		//������ ���������� ���ڸ� �޾ƿ�
		while (EOF != c)
		{

			//���ڸ� �ϳ��ϳ� ������
			c = getc(fp);

			if (EOF == c)
				continue;
			//�ּ� ����
			if ('*' == c)
			{
				//�����Ҷ����� �д´�.
				while ('\n' != c)
				{
					c = getc(fp);
				}
				//���� ���� �������� c�� ������ '\n'�̴� ��Ƽ��
				continue;
			}

			//ù���̸� �� ������ ���� �޾ƿ���, �����Ҷ����� ����
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
				//������ ������ ������ �迭 ��������
				*items = new char[itemCount][CHAR_PER_LINE];
				//�ι��ڷ� �ʱ�ȭ
				memset(*items, '\0', (sizeof(char) * CHAR_PER_LINE) * itemCount);
				infoStart = true;
				continue;
			}

			//���� ������ ���� �о���� ����
			//�����ҽ� �ε��� �ʱ�ȭ. ��ǥ������ �Ľ��Ҷ� ������ ���� �˸��� ���� ���๮�ڵ� �ִ´�.
			if ('\n' == c)
			{
				(*items)[col][row] = c;
				++col;
				row = 0;
			}
			//�ƴϸ� ���� ������Ű�� �޾ƿ� ���� �ֱ�. 
			else
			{
				(*items)[col][row] = c;
				++row;
			}

		}


		fclose(fp);

	}
	else
		cout << "���� ���� ����!" << endl;



	return itemCount;

}

void CFactory::CreateAllWeapons()
{

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*weaponInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&weaponInfos, "../Data/weapon.txt");

	weapons = new CWeapon[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[7][DESCRIPTION_LENGTH] = {};

		int len = strlen(weaponInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{
			//��ǥ�� word�� ���� ���� ä���.
			if (',' == weaponInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == weaponInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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
		strcpy_s(weapons[i].gem->name, ITEM_NAME_LENGTH, "��������");
		weapons[i].element = ELEMENT_END;

	}

	delete[] weaponInfos;
	weaponInfos = nullptr;

	weaponCnt = itemCount;
}

void CFactory::CreateAllMonsters()
{

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*monsterInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&monsterInfos, "../Data/monster.txt");
	monsters = new CMonster[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[11][DESCRIPTION_LENGTH] = {};

		int len = strlen(monsterInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{
			//��ǥ�� word�� ���� ���� ä���.
			if (',' == monsterInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == monsterInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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

	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*potionInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&potionInfos, "../Data/potion.txt");
	potions = new CPotion[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[7][800] = {};

		int len = strlen(potionInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{
			//word�� ��谪�� �Ѿ�� ����
			if (col > 6 || row > 799)
			{
				continue;
			}
			//��ǥ�� word�� ���� ���� ä���.
			if (',' == potionInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == potionInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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
	//���⿡ ���� ������ ���� �������迭 �����͸� �غ��Ѵ�.
	char(*bufItemInfos)[CHAR_PER_LINE] = nullptr;

	//���������� �������� �Ҵ�޴´�.
	int itemCount = GetInfo(&bufItemInfos, "../Data/bufItem.txt");
	bufItems = new CBufItem[itemCount];


	//��ǥ�� �����鼭 ���� ����ü�� ���� ���� ����
	for (int i = 0; i < itemCount; ++i)
	{
		//word�� ��,��
		int col = 0, row = 0;
		//�ϳ��� ���� ����ü�� ���� ����.
		//description �׸񶧹��� ��� �׸��� 800���� ������ ��Ҵ�. ��ȿ������. ���� �ʿ�
		char word[12][800] = {};

		int len = strlen(bufItemInfos[i]);

		//��ǥ������ �Ľ��ϱ�
		for (int j = 0; j < len; ++j)
		{

			//��ǥ�� word�� ���� ���� ä���.
			if (',' == bufItemInfos[i][j])
			{
				++col;
				row = 0;
			}
			//���๮�ڸ� ����������.
			else if ('\n' == bufItemInfos[i][j])
			{
				break;
			}
			//�� ���� �ƴϸ� �����͸� word �� �ִ´�.
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
	//���� id�� 0�̸� �󲮵��� �����
	if (0 == id)
	{
		weapon = new CWeapon;
	}
	else
	{
		//id�� �ش��ϴ� ���� ����
		weapon = new CWeapon;
		//������ ���� ���� �����ͱ��� �����Ѵ�.(��������)
		memcpy(weapon, &(weapons[id - 1]), sizeof(CWeapon));
		//���� ���� �����͸� �̾Ƴ�
		CBufItem gemData = *(weapon->gem);
		//���ο� �ּҿ� ���� ����
		weapon->gem = new CBufItem;
		//�� �ּҿ� �� �����͸� ����.(��������)
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

	//���� �������� ��� ���͵��� id. �ִ� length(��� ������ ��)��ŭ �ִ�.
	int* family = new int[length];
	float* spawnChance = new float[length];
	*family = {};
	*spawnChance = {};

	float chanceSum = 0;
	//family�� �ε������� +1�� family�� ����
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


	//�������� ����
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


	// Ȯ���� ��Ÿ����

	//Ȯ�������� ���� ����
	int randomNum = (rand() % (int)chanceSum) + 1;

	//����Ȯ��
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
	//// family[0] family[1] 0 ~ index-1�� �������� �������� ���� ���̵�
	//int randomIndex = rand() % index;
	////�������� �� ������ ���̵�
	//int id = family[randomIndex];

	int idToSpawn = family[familyIndex];
	cout << "����Ȯ��: " << (spawnChance[familyIndex] / chanceSum) * 100 << endl;
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
	//�������� ����
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

	//Ȯ�������� ���� ����
	int randomNum = (rand() % (int)chanceSum) + 1;

	//����Ȯ��
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