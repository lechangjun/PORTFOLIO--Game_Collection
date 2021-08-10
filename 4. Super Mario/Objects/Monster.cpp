#include "stdafx.h"
#include "Monster.h"

Monster::Monster(wstring shaderFile, D3DXVECTOR2 position)
	: velocity(0.0f), gravity(-0.015f), bOnGround(true), bAutoUp(false), bAutoRight(false), bAutoLeft(true)
{
	animation = new Animation();

	wstring spriteFile = Textures + L"Mario3/Enemy.png";
	Clip* clip;

	{//idle
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 16, 16, 32), 0.15f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 16, 16, 32, 32), 0.15f);
		animation->AddClip(clip);
	}

	{//die
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 32, 24, 48, 32), 1.3f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(2.5f, 2.7f);
	animation->Play(0);
}

Monster::~Monster()
{
	SAFE_DELETE(animation);
}

void Monster::Update(D3DXMATRIX V, D3DXMATRIX P)
{
	D3DXVECTOR2 position = animation->Position();

	velocity += gravity * 0.035f;

	bool bMove = false;

	if (bOnGround == false)
	{
		position.y += velocity;
	}

	if (position.y <= 74)
	{
		position.y = 74;
		bOnGround = true;
	}

	if (bAutoLeft == false)
	{
		animation->Play(1);
	}

	animation->Position(position);
	animation->Update(V, P);
}

void Monster::Render()
{
	animation->Render();
}

D3DXVECTOR2 Monster::Position()
{
	D3DXVECTOR2 position = animation->Position();
	return position;
}

void Monster::Velocity(float v)
{
	velocity = v;
}

void Monster::AutoMoveLeft(float speed)
{
	D3DXVECTOR2 position = animation->Position();
	position.x -= speed;

	animation->Position(position);
}

void Monster::AutoMoveRight(float speed)
{
	D3DXVECTOR2 position = animation->Position();
	position.x += speed;

	animation->Position(position);
}

void Monster::AutoMoveUp(float speed)
{
	D3DXVECTOR2 position = animation->Position();
	position.y += speed;

	animation->Position(position);
}