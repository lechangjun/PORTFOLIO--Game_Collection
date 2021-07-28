#include "stdafx.h"
#include "Clip.h"

//----------------------------------------------------
// Frame
//----------------------------------------------------

Frame::Frame(Sprite* sprite, float time)
{
	Image = sprite;
	Time = time;
}

Frame::~Frame()
{
	SAFE_DELETE(Image);
}

//----------------------------------------------------
// Clip
//----------------------------------------------------

Clip::Clip(PlayMode mode, float speed)
	: mode(mode), speed(speed)
	, length(0), playTime(0), bPlay(false), currentFrame(0)
{
}

Clip::~Clip()
{
	for (Frame* frame : frames)
		SAFE_DELETE(frame);
}

void Clip::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Clip::Position(D3DXVECTOR2 vec)
{
	for (Frame* frame : frames)
		frame->Image->Position(vec);
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 vec)
{
	for (Frame* frame : frames)
	{
		D3DXVECTOR2 scale = frame->Image->Scale();

		frame->Image->Scale(scale.x * vec.x, scale.y * vec.y); //원래 이미지 스케일의 배수니까
	}
}

D3DXVECTOR2 Clip::TextureSize()
{
	return frames[currentFrame]->Image->TextureSize();
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	playTime = 0.0f;
	currentFrame = 0;

	bPlay = true; //플레이 중
}

void Clip::Play(UINT startFrame)
{
	//우리가 원하는 프레임에서 시작하게 하기
	playTime = 0.0f;
	currentFrame = startFrame;

	bPlay = true;
}

void Clip::Stop()
{
	bPlay = false;
	currentFrame = 0;
}

void Clip::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	Frame* frame = frames[currentFrame];
	frame->Image->Update(V, P);
	
	if (bPlay == false) //false면 update 돌릴 필요가 없음
		return; 

	float time = frame->Time * speed; //시간은 계속 돌아감
	playTime += Timer->Elapsed();

	//**분석**
	if (playTime < time)
		return;

	switch (mode)
	{
		case PlayMode::End: //End는 프레임 늘어나면서 끝나면 됌. 한 바퀴만 도는거라서
		{
			currentFrame++;

			if (currentFrame >= frames.size())
				Stop();
		}
			break;
		case PlayMode::Loop:
		{
			currentFrame++;
			currentFrame %= frames.size(); //**분석**
		}
			break;
	}

	playTime = 0.0f;
}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}


