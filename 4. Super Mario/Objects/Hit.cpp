#include "stdafx.h"
#include "Hit.h"

Hit::Hit(wstring shaderFile, D3DXVECTOR2 position)
	: bHit(false)
{
	wstring spriteFile = Textures + L"MarioBros/Brick.png";

	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(L"../_Textures/Mario3/Stage1.png", shaderFile, 272, 112, 288, 128), 1.3f);

	clip->Position(position);
	clip->Scale(0.0f, 0.0f);
	clip->Play();
}

Hit::~Hit()
{
	SAFE_DELETE(clip);
}

void Hit::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (bHit == true)
	{
		clip->Scale(2.5f, 2.7f);
	}

	clip->Update(V, P);
}

void Hit::Render()
{
	clip->Render();
}