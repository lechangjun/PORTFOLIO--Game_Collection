#include "stdafx.h"
#include "Background.h"

Background::Background(wstring shaderFile)
{
	wstring textureFile = L"";

	textureFile = L"../_Textures/PuzzleBobble/Background.png";
	background = new Sprite(textureFile, shaderFile, 16, 15, 335, 240);
}

Background::~Background()
{
	SAFE_DELETE(background);
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	background->Update(V, P);
}

void Background::Render()
{
	background->Position(Width/2, Height/2);
	background->Scale(Width, Height);
	background->Render();
}
