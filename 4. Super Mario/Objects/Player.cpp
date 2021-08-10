#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(300.0f), focusOffset(-180, -180), velocity(0.0f), gravity(-0.01f), 
	bOnGround(true), bUpgrade(false), bJump(false)
{
	animation = new Animation;

	wstring spriteFile = Textures + L"Mario3/All.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	
	{//idle 0 
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 82, 34, 94, 50), 1.3f);
		animation->AddClip(clip);
	}

	{//run 1
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 35, 111, 50), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 117, 34, 128, 50), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 34, 146, 50), 0.1f);
		animation->AddClip(clip);
	}

	{//jump 2 
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 166, 34, 180, 50), 1.3f);
		animation->AddClip(clip);
	}

	{//Upgrade idle 3
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 80, 1, 96, 33), 1.3f);
		animation->AddClip(clip);
	}

	{//Upgrade run 4 
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 3, 113, 33), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 115, 2, 129, 33), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 1, 147, 33), 0.1f);
		animation->AddClip(clip);
	}

	{//Upgrade jump 5
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 165, 1, 180, 33), 1.3f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->Position();

	velocity += gravity * 0.04f;

	bool bMove = false;
	//좌우 이동
	if (Key->Press('A'))
	{
		bMove = true;
		position.x -= moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D'))
	{
		bMove = true;
		position.x += moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 0, 0);
	}

	//점프
	if (Key->Down(VK_SPACE))
	{
		StartJump();
	}
	else if (Key->Up(VK_SPACE))
	{
		EndJump(0.5f);
	}

	if (bOnGround == false)
	{
		bJump = true;
		position.y += velocity;
		if (bJump==true && bUpgrade == false)
		{
			animation->Play(2);
		}
		else if (bJump == true && bUpgrade == true)
		{
			animation->Play(5);
		}
	}

	//마리오 땅으로 꺼지지 않게
	if (bUpgrade == false)
	{
		if (position.y <= 74)
		{
			position.y = 74; //마리오가 땅에 닿아있는 y 포지션
			bOnGround = true;
		}
	}
	else if (bUpgrade == true)
	{
		if (position.y <= 94)
		{
			position.y = 94; //마리오가 땅에 닿아있는 y 포지션
			bOnGround = true;
		}
	}

	animation->Position(position);

	//Play clips
	{
		if (bUpgrade == false)
		{
			animation->Play(bMove ? 1 : 0);
		}
		else if (bUpgrade == true)
		{
			animation->Play(bMove ? 4 : 3);
		}
	}

	animation->Update(V, P);
}

void Player::Render()
{
	//ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);

	animation->Render();
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;

	(*size) = D3DXVECTOR2(1, 1);
}
//////////////////////////////////
void Player::Velocity(float v)
{
	velocity = v;
}

float Player::PositionX()
{
	D3DXVECTOR2 position = animation->Position();

	return position.x;
}

float Player::PositionY()
{
	D3DXVECTOR2 position = animation->Position();

	return position.y;
}

float Player::ScaleX()
{
	D3DXVECTOR2 scale = animation->Scale();

	return scale.x;
}

float Player::ScaleY()
{
	D3DXVECTOR2 scale = animation->Scale();

	return scale.y;
}

void Player::SetPositionY(float y)
{
	animation->PositionY(y);
}

void Player::SetPositionX(float x)
{
	animation->PositionX(x);
}

void Player::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.4f;
		bOnGround = false;
	}
}

void Player::EndJump(float v)
{
	bJump = false;
	if (velocity > v)
		velocity = v;
}
//////////////////////////////////