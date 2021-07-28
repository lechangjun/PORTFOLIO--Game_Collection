#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
	:currentClip(-1), position(0, 0), scale(1,1),
	velocity(0.0f), gravity(-0.025f), bOnGround(true), start(100, 150)
{
}

Animation::~Animation()
{
	for (Clip* clip : clips)
		SAFE_DELETE(clip);
}

void Animation::AddClip(Clip * clip)
{
	clips.push_back(clip);
}

void Animation::Play(UINT clipNumber)
{
	if (clipNumber == currentClip)
		return;

	if (currentClip > -1)
		clips[currentClip]->Stop();
	
	currentClip = clipNumber;
	clips[currentClip]->Play();
}

void Animation::Stop()
{
	if (currentClip > -1)
		clips[currentClip]->Stop();
}

void Animation::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Animation::Position(D3DXVECTOR2 vec)
{
	for (Clip* clip : clips)
		clip->Position(vec);

	position = vec;
}

void Animation::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Animation::Scale(D3DXVECTOR2 & vec)
{
	for (Clip* clip : clips)
		clip->Scale(vec);

	scale = vec;
}

D3DXVECTOR2 Animation::TextureSize()
{
	if (currentClip < 0)
		return D3DXVECTOR2(0, 0);

	return clips[currentClip]->TextureSize();
}

void Animation::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (currentClip < 0)
		return;

	velocity += gravity * 0.01f;

	//มกวม
	if (bOnGround == false)
	{
		position.y += velocity;
		Position(position);
	}

	if (position.y < start.y)
	{
		position.y = start.y;
		velocity = 0.0f;
		bOnGround = true;
		Position(position);
	}

	clips[currentClip]->Update(V, P);
}

void Animation::Render()
{
	if (currentClip < 0)
		return;

	clips[currentClip]->Render();
}

void Animation::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.4f;
		bOnGround = false;
	}
}

void Animation::EndJump()
{
	if (velocity > 0.25f)
		velocity = 0.25f;
}

void Animation::BirdAutoMove(float speed, float num1, float num2)
{
	D3DXVECTOR2 position = Position();

	position.x -= speed;

	if (position.x < num1)
	{
		position.x = num2;
		position.x -= speed;
	}

	Position(position);
}

float Animation::xMin()
{
	return position.x - scale.x /2;
}

float Animation::xMax()
{
	return position.x + scale.x / 2;
}

float Animation::yMin()
{
	return position.y - scale.y / 2;
}

float Animation::yMax()
{
return position.y + scale.y / 2;
}


