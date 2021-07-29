#pragma once

class Animation
{
public:
	Animation();
	~Animation();

	void AddClip(Clip* clip);
	void Play(UINT clipNumber);
	void Stop();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Speed(float speed);
	float Speed();

	void StartJump();
	void EndJump();

	void Go_Left(float speed);

	D3DXVECTOR2 TextureSize();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	D3DXVECTOR2 Trex_position = D3DXVECTOR2(100, 170);

	float length;
	float speed;

	float velocity = 0.0f;
	float gravity = -0.03f;
	bool bOnGround = true;

	UINT currentClip;
	vector<Clip*> clips;
};