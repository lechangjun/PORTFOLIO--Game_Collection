#pragma once

class Monster
{
public:
	Monster(wstring shaderFile, D3DXVECTOR2 position);
	~Monster();

	void Update(D3DXMATRIX V, D3DXMATRIX P);
	void Render();

	Sprite* GetSprite() { return animation->GetSprite(); }

	D3DXVECTOR2 Position();

	void Velocity(float v);
	float Velocity() { return velocity; }

	void SetbOnGround(bool bOnGround) { this->bOnGround = bOnGround; }
	bool GetbOnGround() { return bOnGround; }

	void SetbAutoUp(bool bAutoUp) { this->bAutoUp = bAutoUp; }
	bool GetbAutoUp() { return bAutoUp; }

	void SetbAutoRight(bool bAutoRight) { this->bAutoRight = bAutoRight; }
	bool GetbAutoRight() { return bAutoRight; }

	void SetbAutoLeft(bool bAutoLeft) { this->bAutoLeft = bAutoLeft; }
	bool GetbAutoLeft() { return bAutoLeft; }

	void AutoMoveLeft(float speed);
	void AutoMoveRight(float speed);
	void AutoMoveUp(float speed);

	float Left() { return animation->Left(); }
	float Right() { return animation->Right(); }
	float Top() { return animation->Top(); }
	float Bottom() { return animation->Bottom(); }

private:
	Animation* animation;

	bool bOnGround;
	bool bAutoUp;
	bool bAutoRight;
	bool bAutoLeft;
	float velocity;
	float gravity;

	D3DXVECTOR2 position;

};