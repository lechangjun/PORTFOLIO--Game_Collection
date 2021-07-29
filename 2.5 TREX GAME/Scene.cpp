#include "stdafx.h"
#include "Device.h"

Animation* animation_T;
Animation* animation_B;

Sprite* Floor1;
Sprite* Floor2;
Sprite* Cloud;
Sprite* Cactus[4];

int randomCactus = -1;
bool bCactus[4] = { false };

void InitScene()
{
	animation_T = new Animation;
	animation_B = new Animation;

	wstring spriteFile = Textures + L"Trex_All.png";
	wstring shaderFile = L"../_Shaders/008_Sprite.fx";

	{//공룡
		Clip* Trex;
		{//기본
			Trex = new Clip(PlayMode::Loop);
			Trex->AddFrame(new Sprite(spriteFile, shaderFile, 936, 2, 980, 49), 0.3f);
			Trex->AddFrame(new Sprite(spriteFile, shaderFile, 980, 2, 1024, 49), 0.3f);
			animation_T->AddClip(Trex);
		}

		{//숙이고
			Trex = new Clip(PlayMode::Loop);
			Trex->AddFrame(new Sprite(spriteFile, shaderFile, 1112, 19, 1170, 49), 0.3f);
			Trex->AddFrame(new Sprite(spriteFile, shaderFile, 1170, 19, 1230, 49), 0.3f);
			animation_T->AddClip(Trex);
		}

		animation_T->Position(100, 170);
		animation_T->Scale(2.0f, 2.0f);
		animation_T->Play(0);
	}

	{//바닥
		Floor1 = new Sprite(Textures + L"Floor.png", shaderFile);
		Floor2 = new Sprite(Textures + L"Floor.png", shaderFile);

		Floor1->Position(0, 150);
		Floor1->Scale(Width, 40);
		Floor1->Speed(0.5f);
		Floor2->Position(Width, 150);
		Floor2->Scale(Width, 40);
		Floor2->Speed(0.5f);
	}

	{//새
		Clip* Bird;
		{
			Bird = new Clip(PlayMode::Loop);
			Bird->AddFrame(new Sprite(spriteFile, shaderFile, 134, 8, 180, 40), 0.2f);
			Bird->AddFrame(new Sprite(spriteFile, shaderFile, 182, 3, 225, 32), 0.2f);
			animation_B->AddClip(Bird);
		}
		animation_B->Position(Math::Random((float)Width + 30, (float)Width * 2 + 30), Math::Random(300, 700));
		animation_B->Scale(2.0f, 2.0f);
		animation_B->Play(0);
	}

	{//구름
		Cloud = new Sprite(Textures + L"Cloud.png", shaderFile);
		Cloud->Position(Math::Random((int)Width + 30, (int)Width * 2 + 30), Math::Random(400, 700));
		Cloud->Scale(120, 40);
		Cloud->Speed(Math::Random(0.1f, 0.4f));
	}

	{//선인장
		Cactus[0] = new Sprite(Textures + L"Cactus1.png", shaderFile);
		Cactus[0]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
		Cactus[0]->Scale(50, 100);
		Cactus[0]->Speed(0.5f);

		Cactus[1] = new Sprite(Textures + L"Cactus2.png", shaderFile);
		Cactus[1]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
		Cactus[1]->Scale(50, 100);
		Cactus[1]->Speed(0.5f);

		Cactus[2] = new Sprite(Textures + L"Cactus3.png", shaderFile);
		Cactus[2]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
		Cactus[2]->Scale(50, 100);
		Cactus[2]->Speed(0.5f);

		Cactus[3] = new Sprite(Textures + L"Cactus4.png", shaderFile);
		Cactus[3]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
		Cactus[3]->Scale(50, 100);
		Cactus[3]->Speed(0.5f);

		randomCactus = Math::Random(0, 3);
		switch (randomCactus)
		{
		case 0:
			//Cactus[0]->goLeft();
			bCactus[0] = true;
			break;
		case 1:
			//Cactus[1]->goLeft();
			bCactus[1] = true;
			break;
		case 2:
			//Cactus[2]->goLeft();
			bCactus[2] = true;
			break;
		case 3:
			//Cactus[3]->goLeft();
			bCactus[3] = true;
			break;
		}
	}
}

void DestroyScene()
{
	SAFE_DELETE(animation_T);
	SAFE_DELETE(animation_B);
	SAFE_DELETE(Floor1);
	SAFE_DELETE(Floor2);
	SAFE_DELETE(Cloud);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(Cactus[i]);
}

D3DXMATRIX V, P;
void Update()
{
	//<<쪽으로 이동
	Floor1->goLeft();
	Floor2->goLeft();
	animation_B->Go_Left(Math::Random(0.08f, 0.4f));
	Cloud->goLeft();
	for (int i = 0; i < 4; i++)
	{
		if (bCactus[i] == true)
			Cactus[i]->goLeft();
	}

	//위치 재조정
	if (Cloud->Position().x + Cloud->Scale().x / 2 <= 0)
	{
		Cloud->Position(D3DXVECTOR2(Math::Random((float)Width + 30, (float)Width * 2 + 30), Math::Random(400, 700)));
		Cloud->Speed(Math::Random(0.1f, 0.4f));
	}

	if (animation_B->Position().x + animation_B->Scale().x / 2 <= 0)
	{
		animation_B->Position(D3DXVECTOR2(Math::Random((float)Width + 30, (float)Width * 2 + 30), Math::Random(300, 700)));
		animation_B->Speed(Math::Random(0.08f, 0.3f));
	}

	for (int i = 0; i < 4; i++)
	{
		if (Cactus[i]->Position().x + Cactus[i]->Scale().x / 2 <= 0)
		{
			bCactus[i] = false;
			Cactus[i]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
			Cactus[i]->Speed(0.5f);
		}
	}

	//새와 충돌
	if (animation_T->Position().x + animation_T->Scale().x / 2 >= animation_B->Position().x - animation_B->Scale().x / 2 &&
		animation_T->Position().x - animation_T->Scale().x / 2 <= animation_B->Position().x + animation_B->Scale().x / 2 &&
		animation_T->Position().y + animation_T->Scale().y / 2 >= animation_B->Position().y - animation_B->Scale().y / 2 &&
		animation_T->Position().y - animation_T->Scale().y / 2 <= animation_B->Position().y + animation_B->Scale().y / 2)
	{
		MessageBox(Hwnd, L"Game Over", L"Game Over!", MB_OK);

		animation_T->Play(0);

		//바닥초기화
		Floor1->Position(D3DXVECTOR2(0, 150));
		Floor2->Position(D3DXVECTOR2(Width, 150));
		animation_B->Position(D3DXVECTOR2(Math::Random((float)Width + 30, (float)Width * 2 + 30), Math::Random(300, 700)));
		animation_B->Speed(Math::Random(0.08f, 0.4f));
		for (int i = 0; i < 4; i++)
		{
			bCactus[i] = false;
			Cactus[i]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
			Cactus[i]->Speed(0.5f);
		}
	}
	//선인장과 충돌
	for (int i = 0; i < 4; i++)
	{
		if (animation_T->Position().x + animation_T->Scale().x / 2 >= Cactus[i]->Position().x - Cactus[i]->Scale().x / 2 &&
			animation_T->Position().x - animation_T->Scale().x / 2 <= Cactus[i]->Position().x + Cactus[i]->Scale().x / 2 &&
			animation_T->Position().y + animation_T->Scale().y / 2 >= Cactus[i]->Position().y - Cactus[i]->Scale().y / 2 &&
			animation_T->Position().y - animation_T->Scale().y / 2 <= Cactus[i]->Position().y + Cactus[i]->Scale().y / 2)
		{
			MessageBox(Hwnd, L"Game Over", L"Game Over!", MB_OK);

			animation_T->Play(0);

			//바닥초기화
			Floor1->Position(D3DXVECTOR2(0, 150));
			Floor2->Position(D3DXVECTOR2(Width, 150));
			animation_B->Position(D3DXVECTOR2(Math::Random((float)Width + 30, (float)Width * 2 + 30), Math::Random(300, 700)));
			animation_B->Speed(Math::Random(0.08f, 0.4f));
			for (int i = 0; i < 4; i++)
			{
				bCactus[i] = false;
				Cactus[i]->Position(Math::Random((float)Width + 25, (float)Width * 2 - 25), 150);
				Cactus[i]->Speed(0.5f);
			}
		}
	}

	D3DXVECTOR2 setFloor = D3DXVECTOR2(Width, 150);
	if (Floor1->Position().x + Floor1->Scale().x <= 0)
	{
		Floor1->Position(setFloor);
		randomCactus = Math::Random(0, 3);
		switch (randomCactus)
		{
		case 0:
			bCactus[0] = true;
			break;
		case 1:
			bCactus[1] = true;
			break;
		case 2:
			bCactus[2] = true;
			break;
		case 3:
			bCactus[3] = true;
			break;
		}
	}
	if (Floor2->Position().x + Floor2->Scale().x <= 0)
	{
		Floor2->Position(setFloor);
		randomCactus = Math::Random(0, 3);
		switch (randomCactus)
		{
		case 0:
			bCactus[0] = true;
			break;
		case 1:
			bCactus[1] = true;
			break;
		case 2:
			bCactus[2] = true;
			break;
		case 3:
			bCactus[3] = true;
			break;
		}
	}

	if (Key->Down(VK_SPACE))
	{
		animation_T->StartJump();
	}
	else if (Key->Up(VK_SPACE))
	{
		animation_T->EndJump();
	}

	if (Key->Press(VK_DOWN))
	{
		animation_T->Play(1);
	}
	else if (Key->Up(VK_DOWN))
	{
		animation_T->Play(0);
	}

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	Floor1->Update(V, P);
	Floor2->Update(V, P);
	Cloud->Update(V, P);
	animation_T->Update(V, P);
	animation_B->Update(V, P);
	for (int i = 0; i < 4; i++)
		Cactus[i]->Update(V, P);
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		Floor1->Render();
		Floor2->Render();
		Cloud->Render();
		animation_T->Render();
		animation_B->Render();
		for (int i = 0; i < 4; i++)
			Cactus[i]->Render();
		
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}