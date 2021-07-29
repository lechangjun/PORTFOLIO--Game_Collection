#include "stdafx.h"
#include "Clip.h"
//-----------------------------------------------------------------------------
// Frame
//-----------------------------------------------------------------------------
Frame::Frame(Sprite * sprite, float time)
{
	Image = sprite;
	Time = time;
}

Frame::~Frame()
{
	SAFE_DELETE(Image);
}

//-----------------------------------------------------------------------------
// Clip
//-----------------------------------------------------------------------------

Clip::Clip(PlayMode mode, float speed)
	: mode(mode), speed(speed)
	,length(0),playTime(0),bPlay(false),currentFrame(0)
	,position(0, 0), scale(1, 1)
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

		frame->Image->Scale(scale.x * vec.x, scale.y * vec.y);
	}
}

D3DXVECTOR2 Clip::TextureSize()
{
	return frames[currentFrame]->Image->TextureSize();
}

void Clip::Speed(float speed)
{
	for (Frame* frame : frames)
	{
		frame->Image->Speed(speed);
	}
}

float Clip::Speed()
{
	return frames[0]->Image->Speed();
}

void Clip::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.5f;
		bOnGround = false;
	}
}

void Clip::EndJump()
{
	if (velocity > 0.4f)
		velocity = 0.3f;
}

void Clip::Go_Left()
{
	D3DXVECTOR2 position = Position();
	position.x -= speed * 1;

	Position(position);
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	playTime = 0.0f;
	currentFrame = 0;

	bPlay = true;

}

void Clip::Play(UINT startFrame)
{
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

	//D3DXVECTOR2 position = Position();

	velocity += gravity * 0.01;
	if (bOnGround == false)
	{
		position.y += velocity;

		Position(position);
	}
	if (position.y < Trex_position.y)
	{
		position.y = Trex_position.y;
		velocity = 0.0f;

		bOnGround = true;

		Position(position);
	}

	if (bPlay == true)
	{
		float time = frame->Time * speed;
		playTime += Timer->Elapsed();

		if (playTime >= time)
		{
			switch (mode)
			{
				case PlayMode::End:
				{
					currentFrame++;

					if (currentFrame >= frames.size())
						Stop();
				}
				break;

				case PlayMode::Loop:
				{
					currentFrame++;

					currentFrame %= frames.size();
				}
				break;
				case PlayMode::Reverse:
					break;
				default:
					break;
			}

			playTime = 0.0f;
		}//if(playTime)
	}//if(bPlay)

	//frames[currentFrame]->Image->Position(position);
	//frames[currentFrame]->Image->Scale(scale);

}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}
