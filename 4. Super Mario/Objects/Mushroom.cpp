#include "stdafx.h"
#include "Mushroom.h"

Mushroom::Mushroom(wstring shaderFile, D3DXVECTOR2 position)
	: velocity(0.0f), gravity(-0.35f), bOnGround(true), bAutoUp(false),
	bAutoRight(false), bAutoLeft(false), bHit(false)
{
	wstring spriteFile = Textures + L"Mario3/Object.png";

	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 0, 16, 16), 1.3f);

	clip->Position(position);
	clip->Scale(2.5f, 2.7f);
	clip->Play();
}

Mushroom::~Mushroom()
{
	SAFE_DELETE(clip);
}

void Mushroom::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = clip->Position();

	velocity += gravity * 0.01f;

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

	if (position.y > 247)
	{
		bAutoUp = false;
		bAutoRight = true;
	}

	if (bHit == true)
	{
		clip->Scale(0.0f, 0.0f);
		bAutoLeft = false;
	}

	clip->Position(position);
	clip->Update(V, P);
}

void Mushroom::Render()
{
	clip->Render();
}

void Mushroom::Velocity(float v)
{
	velocity = v;
}

void Mushroom::AutoMoveLeft()
{
	D3DXVECTOR2 position = clip->Position();
	position.x -= 0.2f;

	clip->Position(position);
}

void Mushroom::AutoMoveRight()
{
	D3DXVECTOR2 position = clip->Position();
	position.x += 0.2f;

	clip->Position(position);
}

void Mushroom::AutoMoveUp()
{
	D3DXVECTOR2 position = clip->Position();
	position.y += 0.2f;

	clip->Position(position);
}