#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background.h"
#include "Objects/Player.h"
#include "Objects/Block.h"
#include "Objects/Brick.h"
#include "Objects/Hit.h"
#include "Objects/Coin.h"
#include "Objects/Monster.h"
#include "Objects/Mushroom.h"
#include "Viewer/Following.h"

Background* bg;
Player* player;
Camera* camera;
Block* block[4];
Brick* brick[3];
Hit* hit[3];
Coin* coin[3];
Monster* mon;
Mushroom* mush;

void InitScene()
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	//¹è°æ
	bg = new Background(shaderFile);

	//mario
	player = new Player(D3DXVECTOR2(400, 74), D3DXVECTOR2(2.5f, 2.5f));
	camera = new Following(player);

	//Block
	block[0] = new Block(shaderFile, D3DXVECTOR2(790, 203));
	block[1] = new Block(shaderFile, D3DXVECTOR2(990, 203));
	block[2] = new Block(shaderFile, D3DXVECTOR2(1029, 376)); //2Ãþ
	block[3] = new Block(shaderFile, D3DXVECTOR2(1069, 203)); //¹ö¼¸ ³ª¿È

	//Brick
	brick[0] = new Brick(shaderFile, D3DXVECTOR2(950, 203));
	brick[1] = new Brick(shaderFile, D3DXVECTOR2(1029, 203));
	brick[2] = new Brick(shaderFile, D3DXVECTOR2(1108.5, 203));

	//Hit
	hit[0] = new Hit(shaderFile, D3DXVECTOR2(950, 203));
	hit[1] = new Hit(shaderFile, D3DXVECTOR2(1029, 203));
	hit[2] = new Hit(shaderFile, D3DXVECTOR2(1108.5, 203));

	//coin
	coin[0] = new Coin(shaderFile, D3DXVECTOR2(790, 203));
	coin[1] = new Coin(shaderFile, D3DXVECTOR2(990, 203));
	coin[2] = new Coin(shaderFile, D3DXVECTOR2(1029, 376));

	//goomba
	mon = new Monster(shaderFile, D3DXVECTOR2(1060, 74));

	//mushroom
	mush = new Mushroom(shaderFile, D3DXVECTOR2(1069, 203));
}

void DestroyScene()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(block[i]);
	for (int i = 0; i < 3; i++)
		SAFE_DELETE(brick[i]);
	for (int i = 0; i < 3; i++)
		SAFE_DELETE(hit[i]);
	for (int i = 0; i < 3; i++)
		SAFE_DELETE(coin[i]);
	SAFE_DELETE(mon);
	SAFE_DELETE(mush);
}

void Update()
{
	{//±À¹Ù ÀÌµ¿
		if (mon->GetbAutoLeft() == true)
		{
			mon->AutoMoveLeft(0.1f);
			if (mon->Position().x < -20)
			{
				mon->SetbAutoLeft(false);
			}
		}
		//¹âÇûÀ»¶§
		if (player->Left() <= mon->Right() &&
			player->Right() >= mon->Left() &&
			player->Top() <= mon->Top() + 10)
		{
			mon->SetbAutoLeft(false);
		}
	}

	{//'?' ºí·Ï
		for (int i = 0; i < 3; i++)
		{//'?' ºí·Ï À­ÂÊ Ãæµ¹
			if (player->Left() < block[i]->Right() + 5.0f &&
				player->Right() > block[i]->Left() + 5.0f &&
				player->Top() > block[i]->Bottom() &&
				player->Bottom() < block[i]->Top() + 5.0f)
			{
				player->SetbOnGround(true);

				if (player->Right() > block[i]->Right() + 8.0f) //¿À¸¥ÂÊÀ¸·Î ¶³¾îÁü
				{
					player->SetbOnGround(false);
				}
				else if (player->Left() < block[i]->Left() - 8.0f) //¿ÞÂÊÀ¸·Î ¶³¾îÁü
				{
					player->Velocity(-0.7f);
					player->SetbOnGround(false);
				}
			}

			//'?' ºí·Ï ¾Æ·¡ÂÊ Ãæµ¹
			if (player->Left() < block[i]->Right() &&
				player->Right() > block[i]->Left() &&
				player->Bottom() < block[i]->Top() &&
				player->Top() >= block[i]->Bottom() - 2.0f)
			{
				player->SetbOnGround(true);
				coin[i]->SetbAutoUp(true); //ÄÚÀÎ À­ ¹«ºù
				block[i]->SetbHit(true);

				if (player->GetbOnGround() == true)
				{
					player->Velocity(-0.7f);
					player->SetbOnGround(false);
				}
			}
			//ÄÚÀÎ ³ª¿È
			if (coin[i]->GetbAutoUp() == true)
				coin[i]->AutoMoveUp();
			//ÄÚÀÎ »ç¶óÁü
			//if (player->Left() <= coin[i]->Right() &&
			//	player->Right() >= coin[i]->Left() &&
			//	player->Top() <= coin[i]->Top())
			//{
			//	coin[i]->SetbHit(true);
			//}
		}
	}

	{//¹ö¼¸ ³ª¿À´Â ºí·Ï
		//¹ö¼¸ ºí·Ï À§ Ãæµ¹
		if (player->Left() < block[3]->Right() + 5.0f &&
			player->Right() > block[3]->Left() + 5.0f &&
			player->Top() > block[3]->Bottom() &&
			player->Bottom() < block[3]->Top() + 5.0f)
		{
			player->SetbOnGround(true);

			if (player->Right() > block[3]->Right() + 5.0f) //¿À¸¥ÂÊÀ¸·Î ¶³¾îÁü
			{
				player->SetbOnGround(false);
			}
			else if (player->Left() < block[3]->Left() - 5.0f) //¿ÞÂÊÀ¸·Î ¶³¾îÁü
			{
				player->Velocity(-0.7f);
				player->SetbOnGround(false);
			}
		}

		//¹ö¼¸ ºí·Ï ¾Æ·¡ Ãæµ¹
		if (player->Left() < block[3]->Right() &&
			player->Right() > block[3]->Left() &&
			player->Bottom() < block[3]->Top() &&
			player->Top() >= block[3]->Bottom() - 2.0f)
		{
			player->SetbOnGround(true);
			mush->SetbAutoUp(true);
			block[3]->SetbHit(true);

			if (player->GetbOnGround() == true)
			{
				player->Velocity(-0.7f);
				player->SetbOnGround(false);
			}
		}

		//¹ö¼¸ À­ ¹«ºù
		if (mush->GetbAutoUp() == true)
			mush->AutoMoveUp();

		//¹ö¼¸ ¿À¸¥ÂÊ ¹«ºù
		if (mush->GetbAutoRight() == true)
		{
			mush->AutoMoveRight();

			//¹ö¼¸ ¿À¸¥ÂÊÀ¸·Î ¶³¾îÁü
			if (mush->Left() > brick[2]->Right())
				mush->SetbOnGround(false);

			//¹ö¼¸ ÆÄÀÌÇÁ¶û Ãæµ¹ ÈÄ ¿ÞÂÊÀ¸·Î ÀÌµ¿

			//¸¶¸®¿À¿Í Ãæµ¹
			if (player->Left() <= mush->Right() &&
				player->Right() >= mush->Left() &&
				player->Bottom() <= mush->Top() &&
				player->Top() >= mush->Bottom())
			{
				player->SetbUpgrade(true);
				mush->SetbHit(true);
			}
		}
	}
	{//ÀÏ¹Ý º®µ¹
		//º®µ¹ À§ Ãæµ¹
		for (int i = 0; i < 3; i++)
		{
			if (player->Left() < brick[i]->Right() + 5.0f &&
				player->Right() > brick[i]->Left() + 5.0f &&
				player->Top() > brick[i]->Bottom() &&
				player->Bottom() < brick[i]->Top() + 5.0f)
			{
				player->SetbOnGround(true);

				if (player->Right() > brick[i]->Right() + 8.0f) //¿À¸¥ÂÊÀ¸·Î ¶³¾îÁü
				{
					player->SetbOnGround(false);
				}
				else if (player->Left() < brick[i]->Left() - 8.0f) //¿ÞÂÊÀ¸·Î ¶³¾îÁü
				{
					player->Velocity(-0.7f);
					player->SetbOnGround(false);
				}
			}

			//º®µ¹ ¾Æ·¡ Ãæµ¹
			if (player->Left() < brick[i]->Right() &&
				player->Right() > brick[i]->Left() &&
				player->Bottom() < brick[i]->Top() &&
				player->Top() >= brick[i]->Bottom() - 2.0f)
			{
				player->SetbOnGround(true);
				if (player->GetbOnGround() == true)
				{
					player->Velocity(-0.7f);
					player->SetbOnGround(false);
					brick[i]->SetbHit(true);
					hit[i]->SetbHit(true);
				}
			}
		}
	}

	D3DXMATRIX P;

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	camera->Update();

	D3DXMATRIX V = camera->View();

	bg->Update(V, P);
	player->Update(V, P);
	for (int i = 0; i < 4; i++)
		block[i]->Update(V, P);
	for (int i = 0; i < 3; i++)
		brick[i]->Update(V, P);
	for (int i = 0; i < 3; i++)
		hit[i]->Update(V, P);
	for (int i = 0; i < 3; i++)
		coin[i]->Update(V, P);
	mon->Update(V, P);
	mush->Update(V, P);
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		bg->Render();
		mush->Render();
		for (int i = 0; i < 3; i++)
			coin[i]->Render();
		for (int i = 0; i < 3; i++)
			brick[i]->Render();
		for (int i = 0; i < 4; i++)
			block[i]->Render();
		for (int i = 0; i < 3; i++)
			hit[i]->Render();
		mon->Render();
		player->Render();
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"";

		RECT rect;
		rect.left = 20;
		rect.top = 20;
		rect.right = 600;
		rect.bottom = 20;

		text = L"Frame Per Second : " + to_wstring((int)ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);

		rect.top = 40;
		rect.bottom = 40;

		text = L"Character Position : " + to_wstring((int)player->PositionX());
		text += L", ";
		text += to_wstring((int)player->PositionY());
		DirectWrite::RenderText(text, rect);
	}
	DirectWrite::GetDC()->EndDraw();


	SwapChain->Present(0, 0);
}