#pragma once

class Mushroom
{
public:
	Mushroom(wstring shaderFile, D3DXVECTOR2 position);
	~Mushroom();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Clip* GetClip() { return clip; }
	Sprite* GetSprite() { return clip->GetSprite(); }

	D3DXVECTOR2 Position() { return position; }

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

	void AutoMoveLeft();
	void AutoMoveRight();
	void AutoMoveUp();

	float Left() { return clip->Left(); }
	float Right() { return clip->Right(); }
	float Top() { return clip->Top(); }
	float Bottom() { return clip->Bottom(); }

	void SetbHit(bool bHit) { this->bHit = bHit; }
	bool GetbHit() { return bHit; }

private:
	Clip* clip;

	bool bHit;
	bool bOnGround;
	bool bAutoUp;
	bool bAutoRight;
	bool bAutoLeft;
	float velocity;
	float gravity;

	D3DXVECTOR2 position;
};