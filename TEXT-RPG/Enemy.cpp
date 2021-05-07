#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	hp = 100;
	attack = 10;
	deffense = 10;
	name = "Monster";
}

Enemy::~Enemy()
{

}

void Enemy::Damage(int val)
{
	hp -= val;
	cout << val << "의 데미지를 입었다" << endl;
}

void Enemy::Phase1()
{
	attack *= 2;
	hp *= 2;
}
