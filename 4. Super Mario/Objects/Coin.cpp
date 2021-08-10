#include "stdafx.h"
#include "Coin.h"

Coin::Coin(wstring shaderFile, D3DXVECTOR2 position)
	: bAutoUp(false), bHit(false)
{
	wstring spriteFile = Textures + L"Mario3/Object.png";

	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 98, 13, 112), 0.15f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 6, 113, 10, 127), 0.15f);

	clip->Position(position);
	clip->Scale(2.5f, 2.7f);
	clip->Play();
}

Coin::~Coin()
{
	SAFE_DELETE(clip);
}

void Coin::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	clip->Update(V, P);
}

void Coin::Render()
{
	clip->Render();
}

void Coin::AutoMoveUp()
{
	D3DXVECTOR2 position = clip->Position();

	if (position.y < 247)
	{
		position.y += 0.6f;
	}

	if (bHit == true)
	{
		clip->Scale(0.0f, 0.0f);
	}

	clip->Position(position);
}
