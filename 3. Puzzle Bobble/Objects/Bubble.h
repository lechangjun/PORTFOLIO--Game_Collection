#pragma once

class Bubble
{
public:
	Bubble(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed, int bubblecolor);
	~Bubble();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	int Color() { return color; }

	D3DXVECTOR2 Scale() { return bubble->Scale(); }

	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Velocity(D3DXVECTOR2& vec);
	D3DXVECTOR2 Velocity() { return velocity; }

	void Location(float x, float y);
	void Location(D3DXVECTOR2& vec);
	D3DXVECTOR2 Location() { return location; }

private:
	int color;

	D3DXVECTOR2 velocity;
	Sprite* bubble;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 location;
};