#pragma once

class Block
{
public:
	Block(wstring shaderFile, D3DXVECTOR2 position);
	~Block();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Sprite* GetSprite() { return animation->GetSprite(); }

	D3DXVECTOR2 Position();

	float Left() { return animation->Left(); }
	float Right() { return animation->Right(); }
	float Top() { return animation->Top(); }
	float Bottom() { return animation->Bottom(); }

	void SetbHit(bool bHit) { this->bHit = bHit; }
	bool GetbHit() { return bHit; }

private:
	bool bHit;

	Animation* animation;

	Clip* clip;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
};