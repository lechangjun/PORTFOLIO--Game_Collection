#include "stdafx.h"
#include "Background.h"

Background::Background(wstring shaderFile)
{
	wstring textureFile = L"";

	textureFile = L"../_Textures/Mario3/Stage1.png";
	map = new Sprite(textureFile, shaderFile);

	map->Position(4369, -30);
	map->Scale(2.5f, 2.7f);
}

Background::~Background()
{
	SAFE_DELETE(map);
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	map->Update(V, P);
}

void Background::Render()
{
	map->Render();
}
