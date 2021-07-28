#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
{
	sprite = new Sprite(Textures + L"Bullets.png", shaderFile, 173, 155, 183, 167);

	position = start;
	sprite->Position(position);

	float radian = Math::ToRadian(angle);
	//x는 cos, y는 sin으로 생각하면 편함 (3D에서 말고)
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);
	velocity *= speed; //해당 방향으로..
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position += velocity;
	//정해진 값으로 쭉 감

	sprite->Position(position);
	sprite->Update(V, P);
}

void Bullet::Render()
{
	sprite->Render();
}


