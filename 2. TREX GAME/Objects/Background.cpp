#include "stdafx.h"
#include "Background.h"

Background::Background(wstring shaderFile)
{
	wstring textureFile = L"";

	textureFile = L"../_Textures/Mario/Cloud.png";
	cloud[0] = new Sprite(textureFile, shaderFile, 126, 128);
	cloud[1] = new Sprite(textureFile, shaderFile, 144, 0, 336, 128);


	textureFile = L"../_Textures/Mario/Bush.png";
	bush[0] = new Sprite(textureFile, shaderFile);

	textureFile = L"../_Textures/Mario/Bush2.png";
	bush[1] = new Sprite(textureFile, shaderFile);


	textureFile = L"../_Textures/Mario/Tile.png";
	tile[0] = new Sprite(textureFile, shaderFile);
	tile[1] = new Sprite(textureFile, shaderFile, 0, 66, 0, 0);
}


Background::~Background()
{
	SAFE_DELETE(cloud[0]);
	SAFE_DELETE(cloud[1]);

	SAFE_DELETE(bush[0]);
	SAFE_DELETE(bush[1]);

	SAFE_DELETE(tile[0]);
	SAFE_DELETE(tile[1]);
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	cloud[0]->Update(V, P);
	cloud[1]->Update(V, P);

	bush[0]->Update(V, P);
	bush[1]->Update(V, P);

	tile[0]->Update(V, P);
	tile[1]->Update(V, P);
}

void Background::Render()
{
	cloud[0]->Position(200, 420);
	cloud[0]->Render();

	cloud[0]->Position(40, 420);
	cloud[0]->Render();

	cloud[1]->Position(500, 420);
	cloud[1]->Render();

	bush[1]->Position(-50, 170);
	bush[1]->Render();

	bush[1]->Position(300, 170);
	bush[1]->Render();

	bush[1]->Position(680, 170);
	bush[1]->Render();

	bush[0]->Position(100, 128);
	bush[0]->Render();

	bush[0]->Position(650, 128);
	bush[0]->Render();


	float tileWidth = tile[0]->Scale().x;
	float tileWidth2 = tile[1]->Scale().x;

	for (int i = 0; i < 7; i++)
	{
		tile[0]->Position((float)i * tileWidth, 45);
		tile[0]->Render();

		tile[1]->Position((float)i * tileWidth2, 25);
		tile[1]->Render();
	}
}