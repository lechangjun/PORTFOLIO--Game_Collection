#pragma once

enum class PlayMode //플레이 방식 정하기
{
	End = 0, //동작들을 한번 재생하고 말것인지
	Loop, //반복
	Reverse //역순
};

struct Frame //구조체도 생성자처럼 쓸수있음
{
	float Time; //프레임을 관리하기 위한 시간
	Sprite* Image;

	Frame(Sprite* sprite, float time);
	~Frame();
};

class Clip
{
public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f); //default parameter로 End
	~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	D3DXVECTOR2 TextureSize();

	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	float length; //해당 클립에 대한 전체 길이
	float speed;

	bool bPlay; //현재 클립이 재생 중인지 아닌지 판단하려는 bPlay
	UINT currentFrame; //재생되고 있는 현재 프레임이 무엇인지
	float playTime;

	PlayMode mode; //위에 만든 PlayMode

	vector<Frame *> frames; //프레임이 모여서 하나의 클립이 됨
};


