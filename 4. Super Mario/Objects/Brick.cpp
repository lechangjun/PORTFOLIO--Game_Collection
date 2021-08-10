#include "stdafx.h"
#include "Brick.h"

Brick::Brick(wstring shaderFile, D3DXVECTOR2 position)
	: bHit(false)
{
	wstring spriteFile = Textures + L"Mario3/Block.png";

	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 272, 112, 288, 128), 1.3f);

	clip->Position(position);
	clip->Scale(2.5f, 2.7f);
	clip->Play(0);
}

Brick::~Brick()
{
	SAFE_DELETE(clip);
}

void Brick::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (bHit == true)
	{
		clip->Scale(0.0f, 0.0f);
	}
	clip->Update(V, P);
}

void Brick::Render()
{
	clip->Render();
}
