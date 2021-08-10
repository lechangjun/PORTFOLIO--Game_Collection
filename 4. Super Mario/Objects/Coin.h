#pragma once

class Coin
{
public:
	Coin(wstring shaderFile, D3DXVECTOR2 position);
	~Coin();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Clip* GetClip() { return clip; }
	D3DXVECTOR2 SetScale(float x, float y)
	{
		scale.x = x;
		scale.y = y;
		return scale;
	}
	D3DXVECTOR2 Position() { return position; }
	D3DXVECTOR2 Scale() { return scale; }

	float Left() { return clip->Left(); }
	float Right() { return clip->Right(); }
	float Top() { return clip->Top(); }
	float Bottom() { return clip->Bottom(); }

	void SetbAutoUp(bool bAutoUp) { this->bAutoUp = bAutoUp; }
	bool GetbAutoUp() { return bAutoUp; }
	void SetbHit(bool bHit) { this->bHit = bHit; }
	bool GetbHit() { return bHit; }

	void AutoMoveUp();

private:
	bool bAutoUp;
	bool bHit;

	Clip* clip;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
};