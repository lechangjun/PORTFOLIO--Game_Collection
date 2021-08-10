#pragma once

class Brick
{
public:
	Brick(wstring shaderFile, D3DXVECTOR2 position);
	~Brick();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Clip* GetClip() { return clip; }
	Sprite* GetSprite() { return clip->GetSprite(); }

	D3DXVECTOR2 Position() { return position; }

	float Left() { return clip->Left(); }
	float Right() { return clip->Right(); }
	float Top() { return clip->Top(); }
	float Bottom() { return clip->Bottom(); }

	void SetbHit(bool bHit) { this->bHit = bHit; }
	bool GetbHit() { return bHit; }

private:
	bool bHit;

	Clip* clip;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
};