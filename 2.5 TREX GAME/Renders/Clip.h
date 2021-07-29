#pragma once

enum class PlayMode
{
	End = 0, Loop, Reverse
};

struct Frame
{
	float Time;
	Sprite* Image;

	Frame(Sprite* sprite, float time);
	~Frame();
};

class Clip
{
public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
	~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);
	D3DXVECTOR2 Position() { return frames[0]->Image->Position(); }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);
	D3DXVECTOR2 Scale() { return frames[0]->Image->Scale(); }

	D3DXVECTOR2 TextureSize();

	void Speed(float speed);
	float Speed();

	void StartJump();
	void EndJump();

	//void Go_Left();

	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	vector<Frame*> frames;

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	D3DXVECTOR2 Trex_position = D3DXVECTOR2(100, 170);

	float velocity = 0.0f;
	float gravity = -0.03f;
	bool bOnGround = true;

	float length;
	float speed;

	bool bPlay;
	UINT currentFrame;
	float playTime;

	PlayMode mode;

};