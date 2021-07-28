#pragma once

class Bullet
{
public:
	Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed);
	~Bullet();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	D3DXVECTOR2 velocity; //총알 속력
	Sprite* sprite; //이미지
	
	D3DXVECTOR2 position; //위치
};

