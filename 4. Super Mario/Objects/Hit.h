#pragma once

class Hit
{
public:
	Hit(wstring shaderFile, D3DXVECTOR2 start);
	~Hit();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Clip* GetClip() { return clip; }
	void SetPosition(float x, float y)
	{
		x = position.x;
		y = position.y;
	}
	D3DXVECTOR2 SetScale(float x, float y)
	{
		scale.x = x;
		scale.y = y;
		return scale;
	}
	D3DXVECTOR2 Position() { return position; }
	D3DXVECTOR2 Scale() { return scale; }

	void SetbHit(bool bHit) { this->bHit = bHit; }
	bool GetbHit() { return bHit; }

private:
	bool bHit;

	Clip* clip;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
};