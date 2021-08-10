#include "stdafx.h"
#include "Block.h"

Block::Block(wstring shaderFile, D3DXVECTOR2 position)
	: bHit(false)
{
	animation = new Animation();

	wstring spriteFile = Textures + L"Mario3/Block.png";
	Clip* clip;

	{//idle 0
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 80, 112, 96, 128), 0.15f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 96, 112, 112, 128), 0.15f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 112, 112, 128, 128), 0.15f);
		animation->AddClip(clip);
	}

	{//hit 1
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 144, 112, 160, 128), 0.15f);
		animation->AddClip(clip);
	}
	animation->Position(position);
	animation->Scale(2.5f, 2.7f);
	animation->Play(0);
}

Block::~Block()
{
	SAFE_DELETE(animation);
}

void Block::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->Position();

	if (bHit == true)
	{
		animation->Play(1);
	}
	animation->Position(position);
	animation->Update(V, P);
}

void Block::Render()
{
	animation->Render();
}

D3DXVECTOR2 Block::Position()
{
	D3DXVECTOR2 position = animation->Position();
	return position;
}