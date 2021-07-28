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
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	D3DXVECTOR2 TextureSize();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	
	/////////////////
	void StartJump();
	void EndJump();
	void BirdAutoMove(float speed, float num1, float num2);
	float xMin();
	float xMax();
	float yMin();
	float yMax();
	/////////////////

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	UINT currentClip;
	vector<Clip *> clips;

	/////////////////
	float velocity;
	float gravity;
	bool bOnGround;
	D3DXVECTOR2 start; //스타트 포지션
	/////////////////
};


