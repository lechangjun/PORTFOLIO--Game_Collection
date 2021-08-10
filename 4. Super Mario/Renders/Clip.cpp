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
	,position(0,0),scale(1,1), rotation(0,0,0)
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
	position = vec;

	//for (Frame* frame : frames)
	//	frame->Image->Position(vec);
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
	//for (Frame* frame : frames)
	//{
	//	D3DXVECTOR2 scale = frame->Image->Scale();
	//
	//	frame->Image->Scale(scale.x * vec.x, scale.y * vec.y);
	//}
}

void Clip::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Clip::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
	//for (Frame* frame : frames)
	//	frame->Image->Rotation(vec);
}

void Clip::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));
}

void Clip::RotationDegree(D3DXVECTOR3 & vec)
{
	D3DXVECTOR3 temp;
	temp.x = Math::ToRadian(vec.x);
	temp.y = Math::ToRadian(vec.y);
	temp.z = Math::ToRadian(vec.z);

	Rotation(temp);

	//for (Frame* frame : frames)
	//	frame->Image->RotationDegree(vec);
}

D3DXVECTOR3 Clip::RotationDegree()
{
	D3DXVECTOR3 temp;
	temp.x = Math::ToRadian(temp.x);
	temp.y = Math::ToRadian(temp.y);
	temp.z = Math::ToRadian(temp.z);

	return temp;
	//return frames[currentFrame]->Image->textureSize();
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

	frames[currentFrame]->Image->Position(position);
	frames[currentFrame]->Image->Scale(scale);
	frames[currentFrame]->Image->Rotation(rotation);
	
	frames[currentFrame]->Image->Update(V, P);
}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}
//////////////////////////////////
Sprite * Clip::GetSprite()
{
	return frames[currentFrame]->Image;
}

float Clip::Left()
{
	left = position.x - scale.x * frames[currentFrame]->Image->TextureSize().x * 0.5f;
	return left;
}

float Clip::Right()
{
	right = position.x + scale.x * frames[currentFrame]->Image->TextureSize().x * 0.5f;
	return right;
}

float Clip::Bottom()
{
	bottom = position.y - scale.y * frames[currentFrame]->Image->TextureSize().y * 0.5f;
	return bottom;
}

float Clip::Top()
{
	bottom = position.y + scale.y * frames[currentFrame]->Image->TextureSize().y * 0.5f;
	return bottom;
}
//////////////////////////////////