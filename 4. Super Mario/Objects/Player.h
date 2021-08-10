#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);
	//////////////////////////////////
	void Velocity(float v);
	float Velocity() { return velocity; }

	float Left() { return animation->Left(); }
	float Right() { return animation->Right(); }
	float Top() { return animation->Top(); }
	float Bottom() { return animation->Bottom(); }

	float PositionX();
	float PositionY();
	float ScaleX();
	float ScaleY();

	void SetPositionY(float y);
	void SetPositionX(float x);

	void StartJump();
	void EndJump(float v);

	void SetbOnGround(bool bOnGround) { this->bOnGround = bOnGround; }
	bool GetbOnGround() { return bOnGround; }
	void SetbUpgrade(bool bUpgrade) { this->bUpgrade = bUpgrade; }
	bool GetbUpgrade() { return bUpgrade; }
	//////////////////////////////////
private:
	float moveSpeed;
	Animation* animation;

	D3DXVECTOR2 focusOffset;

	//////////////////////////////////
	bool bOnGround;
	bool bUpgrade;
	bool bJump;
	float velocity;
	float gravity;
	//////////////////////////////////
};