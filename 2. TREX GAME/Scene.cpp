#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Bullet.h"

#include <time.h>

Animation* Trex;
Sprite* Floor;
Sprite* Cloud[2];
Sprite* Cactus[4];
Animation* Bird;
Sprite* GG;



bool bAutoMove = true;
bool bScore = true;
int Score = 0;

void InitScene()
{
	wstring shaderFile = Shaders + L"008_Sprites.fx";

	Trex = new Animation();
	Clip* TrexClip;
	//Trex클립0(기본)
	{

		wstring spriteFile1 = Textures + L"Trex/newTrex1.png";
		wstring spriteFile2 = Textures + L"Trex/newTrex2.png";
		wstring spriteFile3 = Textures + L"Trex/newTrex3.png";

		TrexClip = new Clip(PlayMode::Loop);
		TrexClip->AddFrame(new Sprite(spriteFile1, shaderFile), 0.2f);
		TrexClip->AddFrame(new Sprite(spriteFile2, shaderFile), 0.2f);
		TrexClip->AddFrame(new Sprite(spriteFile3, shaderFile), 0.2f);

		Trex->AddClip(TrexClip);
		Trex->Position(100, 150);
		Trex->Scale(0.75f, 0.65f);
		Trex->Play(0);
	}

	//Trex클립1(숙이는 모션)
	{
		wstring spriteFile4 = Textures + L"Trex/newTrexDown1.png";
		wstring spriteFile5 = Textures + L"Trex/newTrexDown2.png";

		TrexClip = new Clip(PlayMode::Loop);
		TrexClip->AddFrame(new Sprite(spriteFile4, shaderFile), 0.2f);
		TrexClip->AddFrame(new Sprite(spriteFile5, shaderFile), 0.2f);

		Trex->AddClip(TrexClip);
		Trex->Position(100, 150);
		Trex->Scale(0.45f, 0.55f);
	}

	//땅
	Floor = new Sprite(Textures + L"Trex/Floor.png", shaderFile);
	Floor->Position(600, 130);
	Floor->Scale(1200, 12);

	//구름
	Cloud[0] = new Sprite(Textures + L"Trex/Cloud.png", shaderFile);
	Cloud[1] = new Sprite(Textures + L"Trex/Cloud.png", shaderFile);

	Cloud[0]->Position(300, 500);
	Cloud[1]->Position(600, 450);

	Cloud[0]->Scale(80, 30);
	Cloud[1]->Scale(70, 35);

	//선인장
	Cactus[0] = new Sprite(Textures + L"Trex/Cactus3.png", shaderFile);
	Cactus[1] = new Sprite(Textures + L"Trex/Cactus4.png", shaderFile);
	Cactus[2] = new Sprite(Textures + L"Trex/Cactus2.png", shaderFile);
	Cactus[3] = new Sprite(Textures + L"Trex/Cactus1.png", shaderFile);

	Cactus[0]->Position(500, 150);
	Cactus[1]->Position(1500, 150);
	Cactus[2]->Position(2000, 150);
	Cactus[3]->Position(2300, 150);

	for (int i = 0; i < 4; i++)
		Cactus[i]->Scale(55, 50);

	//새 클립0
	Bird = new Animation();
	Clip* BirdClip;
	{
		wstring spriteFile6 = Textures + L"Trex/BirdMove1.png";
		wstring spriteFile7 = Textures + L"Trex/BirdMove2.png";

		BirdClip = new Clip(PlayMode::Loop);
		BirdClip->AddFrame(new Sprite(spriteFile6, shaderFile), 0.2f);
		BirdClip->AddFrame(new Sprite(spriteFile7, shaderFile), 0.2f);

		Bird->AddClip(BirdClip);
		Bird->Position(600, 350);
		Bird->Scale(0.5f, 0.4f);
		Bird->Play(0);
	}

	//게임오버 - 스케일 0,0으로 맞추고 충돌하면 500,50으로 바꿈
	GG = new Sprite(Textures + L"Trex/TrexSprite.png", shaderFile, 655, 15, 847, 30);
	GG->Position(400, 300);
	GG->Scale(0, 0);
}

void DestroyScene()
{
	SAFE_DELETE(Floor);
	SAFE_DELETE(Trex);
	SAFE_DELETE(Cloud[0]);
	SAFE_DELETE(Cloud[1]);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(Cactus[i]);
	SAFE_DELETE(Bird);
	SAFE_DELETE(GG);
}

D3DXMATRIX V, P;

void Update()
{
	//스페이스바로 점프함
	if (Key->Down(VK_SPACE))
		Trex->StartJump();
	else if (Key->Up(VK_SPACE))
		Trex->EndJump();

	//아래 방향키로 엎드림
	if (Key->Down(VK_DOWN))
		Trex->Play(1);
	else if (Key->Up(VK_DOWN))
		Trex->Play(0);

	srand(float(time(NULL)));

	//왼쪽으로 움직임
	if (bAutoMove == true)
	{
		Floor->AutoMove(0.08f, 400.0f, 550.0f);
		Cloud[0]->AutoMove(0.03f, 0.0f, 1100.0f);
		Cloud[1]->AutoMove(0.03f, 0.0f, 1100.0f);
		for (int i = 0; i < 4; i++)
			Cactus[i]->AutoMove(0.08f, 0.0f, rand() % 1000 + 1500.0f);
		Bird->BirdAutoMove(0.12f, 0.0f, 1100.0f);
	}

	//선인장 충돌시 게임종료
	for (int i = 0; i < 4; i++)
	{
		if (Trex->xMin() <= Cactus[i]->xMax() &&
			Trex->xMax() >= Cactus[i]->xMin() &&
			Trex->yMin() <= Cactus[i]->yMax() &&
			Trex->yMax() >= Cactus[i]->yMin())
		{
			bAutoMove = false;
			bScore = false;
			GG->Scale(500, 50);
		}
	}

	//새 충돌시 게임종료
	if (Trex->xMin() <= Bird->xMax() &&
		Trex->xMax() >= Bird->xMin() &&
		Trex->yMin() >= Bird->yMax())
	{
		bAutoMove = false;
		bScore = false;
		GG->Scale(500, 50);
	}

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	Trex->Update(V, P);
	Floor->Update(V, P);
	Cloud[0]->Update(V, P);
	Cloud[1]->Update(V, P);
	for (int i = 0; i < 4; i++)
		Cactus[i]->Update(V, P);
	Bird->Update(V, P);
	GG->Update(V, P);
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{ 
		Trex->Render();
		Floor->Render();
		Cloud[0]->Render();
		Cloud[1]->Render();
		for (int i = 0; i < 4; i++)
			Cactus[i]->Render();
		Bird->Render();
		GG->Render();

		//점수 카운트
		if (bScore)
			for (int i = 0; i < 4; i++)
				if (Trex->xMax() > Cactus[i]->xMin() &&
					Trex->yMin() > Cactus[i]->yMax())
				{
					Score++;
				}
		ImGui::Text("Trex Game");
		ImGui::InputInt("Score", &Score);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}