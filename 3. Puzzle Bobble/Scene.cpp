#include "stdafx.h"
#include "Device.h"
#include "Objects/Background.h"
#include "Objects/Bubble.h"

Background* bg; //배경
Sprite* mach; //기계
Sprite* aw; //화살표
vector<Bubble*>bubbles; //발사 버블

int NextBubble; //다음 버블
Sprite* nextbubbles;
int Next_NextBubble; //다다음 버블
Sprite* next_nextbubbles;

//충돌 판정
//한 줄에 8개씩 7줄
int line[8][8] = { 0 };

int confirm[8][8] = { 0 };

bool BubbleCheck(int y, int x, int color) //처음 버블 떨어트릴때
{
	if (y > 7 || y < 0 || x > 7 || x < 0) //범위
		return false;
	if (line[y][x] == 0) //버블 유무
		return false;
	if (line[y][x] != color) //색이 같은지
		return false;
	if (confirm[y][x] == 10) 
		return false;

	return true;
}

bool check(int y, int x) //^ 후에 남은 버블 떨어트리기
{
	if (y < 0 || y > 7 || x < 0 || x > 7) 
		return false;
	if (line[y][x] == 0) 
		return false;
	if (confirm[y][x] == 10) 
		return false;
	return true;
}

void InitScene()
{
	wstring shaderFile = L"../_Shaders/008_Sprite.fx";

	bg = new Background(L"../_Shaders/008_Sprite.fx"); //배경

	//기계
	mach = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 8, 713, 84, 759);
	mach->Position(Width/2, 46);
	mach->Scale(100, 100);

	//화살
	aw = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 12, 488, 34, 543);
	aw->Position(Width/2, 76);
	aw->Scale(50, 125);

	//구슬 색 랜덤
	NextBubble = Math::Random(0, 99999) % 5 + 1;
	//Next_NextBubble = Math::Random(0, 89999) % 5 + 1;

	switch (NextBubble)
	{
	case 1: //파란색
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1187, 28, 1204);
		break;
	case 2: //빨간색			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1214, 28, 1231);
		break;
	case 3: //노란색			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1241, 28, 1258);
		break;
	case 4: //초록색			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1268, 28, 1285);
		break;
	case 5: //보라색			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1295, 28, 1312);
		break;
	}

	//switch (Next_NextBubble)
	//{
	//case 1: //파란색
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1187, 28, 1204);
	//	break;
	//case 2: //빨간색			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1214, 28, 1231);
	//	break;
	//case 3: //노란색			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1241, 28, 1258);
	//	break;
	//case 4: //초록색			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1268, 28, 1285);
	//	break;
	//case 5: //보라색			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1295, 28, 1312);
	//	break;
	//}
}

void DestroyScene()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(mach);
	SAFE_DELETE(aw);
	SAFE_DELETE(nextbubbles);
	SAFE_DELETE(next_nextbubbles);
	for (Bubble* bubble : bubbles)
		SAFE_DELETE(bubble);
}

D3DXMATRIX V, P;
void Update()
{
		//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);


	if (bubbles.size() > 2) //생성된 버블이 3개 이상일 때
	{
		queue<int> Qy;//행
		queue<int> Qx;//열
		queue<int> Qc;//개수 

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				confirm[i][j] = 0;
			}
		}

		int lastbubble = bubbles.size() - 1; //마지막에 쏜 버블
		Qy.push((int)(bubbles[lastbubble]->Location().x)), Qx.push((int)(bubbles[lastbubble]->Location().y)), Qc.push(1);
		int bubbleColor = bubbles[lastbubble]->Color(); //^버블의 색
		int colorCount = 0; //카운트

		while (Qy.empty() == false)
		{
			int Py = Qy.front(); Qy.pop(); //현재 y좌표
			int Px = Qx.front(); Qx.pop(); //현재 x좌표
			int Pc = Qc.front(); Qc.pop(); //현재 카운트
			colorCount = Pc;
			if (!(Py >= 0 && Py <= 8) || !(Px >= 0 && Px <= 8))
			{
				colorCount = Pc;
				break;
			}
			if (confirm[Py][Px] == 10) continue;
			confirm[Py][Px] = 10;//확인용

			//상
			if (BubbleCheck(Py - 1, Px, bubbleColor))
				Qy.push(Py - 1), Qx.push(Px), Qc.push(Pc + 1);
			//우
			if (BubbleCheck(Py, Px + 1, bubbleColor))
				Qy.push(Py), Qx.push(Px + 1), Qc.push(Pc + 1);
			//하
			if (BubbleCheck(Py + 1, Px, bubbleColor))
				Qy.push(Py + 1), Qx.push(Px), Qc.push(Pc + 1);
			//좌
			if (BubbleCheck(Py, Px - 1, bubbleColor))
				Qy.push(Py), Qx.push(Px - 1), Qc.push(Pc + 1);
			if (Py % 2 == 1)
			{
				//우상
				if (BubbleCheck(Py - 1, Px + 1, bubbleColor))
					Qy.push(Py - 1), Qx.push(Px + 1), Qc.push(Pc + 1);
				//우하
				if (BubbleCheck(Py + 1, Px + 1, bubbleColor))
					Qy.push(Py + 1), Qx.push(Px + 1), Qc.push(Pc + 1);
			}
			else
			{
				//좌상
				if (BubbleCheck(Py - 1, Px - 1, bubbleColor))
					Qy.push(Py - 1), Qx.push(Px - 1), Qc.push(Pc + 1);
				//좌하
				if (BubbleCheck(Py + 1, Px - 1, bubbleColor))
					Qy.push(Py + 1), Qx.push(Px - 1), Qc.push(Pc + 1);
			}
		}
		if (colorCount >= 3)//같은색이 3개 이상
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (confirm[i][j] == 10)
					{
						for (int k = 0; k < bubbles.size(); k++)
						{
							if (bubbles[k]->Location().x == i && bubbles[k]->Location().y == j)
							{
								bubbles.erase(begin(bubbles) + k);
							}
						}
						line[i][j] = 0; //line에 저장된 버블 색 0으로 초기화함
					}
				}
			}
		}

		if (bubbles.size() != 0) //만들어진 버블이 하나라도 있을 때
		{

			for (int i = 0; i < bubbles.size(); i++) //0부터 만들어진 버블 크기만큼
			{
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < 8; k++)
					{
						confirm[j][k] = 0; //배열 0으로 초기화
					}
				}

				Qy.push((int)(bubbles[i]->Location().x)), Qx.push((int)(bubbles[i]->Location().y)), Qc.push(1);
				bubbleColor = bubbles[i]->Color();
				colorCount = 0; //카운트 0
				while (Qy.empty() == false)
				{
					int cy = Qy.front(); Qy.pop();//cy = 현재 y좌표
					int cx = Qx.front(); Qx.pop();//cx = 현재 x좌표

					if (cy == 0) //현재 y좌표가 0일때
						colorCount = 1; //카운트 1

					if (!(cy >= 0 && cy <= 8) || !(cx >= 0 && cx <= 8))
					{//y좌표 x좌표가 범위 밖
						break;
					}
					if (confirm[cy][cx] == 10) continue;
					confirm[cy][cx] = 10;

					//상
					if (check(cy - 1, cx)) //y-1 x는 그대로
						Qy.push(cy - 1), Qx.push(cx);
					//우
					if (check(cy, cx + 1)) //y는 그대로 x+1
						Qy.push(cy), Qx.push(cx + 1);
					//하
					if (check(cy + 1, cx))
						Qy.push(cy + 1), Qx.push(cx);
					//좌
					if (check(cy, cx - 1))
						Qy.push(cy), Qx.push(cx - 1);
					if (cy % 2 == 1)
					{
						//우상
						if (check(cy - 1, cx + 1))
							Qy.push(cy - 1), Qx.push(cx + 1);
						//우하
						if (check(cy + 1, cx + 1))
							Qy.push(cy + 1), Qx.push(cx + 1);
					}
					else
					{
						//좌상
						if (check(cy - 1, cx - 1))
							Qy.push(cy - 1), Qx.push(cx - 1);
						//좌하
						if (check(cy + 1, cx - 1))
							Qy.push(cy + 1), Qx.push(cx - 1);
					}
				}
				if (colorCount == 0) //같은 색 버블이 사라졌거나 없을 때
				{
					for (int l = 1; l < 8; l++)
					{
						for (int j = 1; j < 8; j++)
						{
							if (confirm[l][j] == 10)
							{
								for (int k = 0; k < bubbles.size(); k++)
								{
									if (bubbles[k]->Location().x == l && bubbles[k]->Location().y == j)
									{
										bubbles.erase(begin(bubbles) + k);
									}
								}
								line[l][j] = 0;
							}
						}
					}
				}
			}
		}
	}

	if (Key->Press(VK_LEFT) && aw->Rotation() < 87.0f)
		aw->Rotation(aw->Rotation() + 0.05f);
	//화살표 회전(왼쪽)
	if (Key->Press(VK_RIGHT) && aw->Rotation() > -87.0f)
		aw->Rotation(aw->Rotation() - 0.05f);
	//화살표 회전(오른쪽)
	if (Key->Down(VK_SPACE))
	{ //버블 생성 및 발사
		wstring file = Shaders + L"008_Sprite.fx";

		float angle = aw->Rotation() + 90;
		Bubble* bubble = new Bubble(file, aw->Position(), angle, 0.9, NextBubble);
		bubbles.push_back(bubble);

		NextBubble= Math::Random(0, 666666) % 5 + 1;
		//NextBubble = Next_NextBubble;
		//Next_NextBubble = Math::Random(0, 666666) % 5 + 1;

		switch (NextBubble)
		{
		case 1: //파란색
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1187, 28, 1204);
			break;
		case 2: //빨간색			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1214, 28, 1231);
			break;
		case 3: //노란색			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1241, 28, 1258);
			break;
		case 4: //초록색			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1268, 28, 1285);
			break;
		case 5: //보라색			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1295, 28, 1312);
			break;
		}
		nextbubbles->Position(Width / 2, 76);
		nextbubbles->Scale(52, 52);

		//switch (Next_NextBubble)
		//{
		//case 1: //파란색
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1187, 28, 1204);
		//	break;
		//case 2: //빨간색			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1214, 28, 1231);
		//	break;
		//case 3: //노란색			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1241, 28, 1258);
		//	break;
		//case 4: //초록색			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1268, 28, 1285);
		//	break;
		//case 5: //보라색			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1295, 28, 1312);
		//	break;
		//}
		//next_nextbubbles->Position(Width / 2 + 40, 30);
		//next_nextbubbles->Scale(52, 52);
	}
	//x 296 ~ 714
	//348 400 452 504 556 608 660 712
	//y 662
	//610 558 502 450 398 346
	for (int i = 0; i < bubbles.size(); i++)
	{
		if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 >= Height - 106) //1번째 줄
		{
			bubbles[i]->Velocity(D3DXVECTOR2(0, 0));

			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 348)
			{
				bubbles[i]->Position(328, Height - 106);
				line[0][0] = bubbles[i]->Color(); //0,0에 색 저장
				bubbles[i]->Location(0, 0); //위치 저장
			}
			else if (bubbles[i]->Position().x >= 348 && bubbles[i]->Position().x < 400)
			{
				bubbles[i]->Position(376, Height - 106);
				line[0][1] = bubbles[i]->Color();
				bubbles[i]->Location(0, 1);
			}
			else if (bubbles[i]->Position().x >= 400 && bubbles[i]->Position().x < 452)
			{
				bubbles[i]->Position(426, Height - 106);
				line[0][2] = bubbles[i]->Color();
				bubbles[i]->Location(0, 2);
			}
			else if (bubbles[i]->Position().x >= 452 && bubbles[i]->Position().x < 504)
			{
				bubbles[i]->Position(478, Height - 106);
				line[0][3] = bubbles[i]->Color();
				bubbles[i]->Location(0, 3);
			}
			else if (bubbles[i]->Position().x >= 504 && bubbles[i]->Position().x < 556)
			{
				bubbles[i]->Position(530, Height - 106);
				line[0][4] = bubbles[i]->Color();
				bubbles[i]->Location(0, 4);
			}
			else if (bubbles[i]->Position().x >= 556 && bubbles[i]->Position().x < 608)
			{
				bubbles[i]->Position(582, Height - 106);
				line[0][5] = bubbles[i]->Color();
				bubbles[i]->Location(0, 5);
			}
			else if (bubbles[i]->Position().x >= 608 && bubbles[i]->Position().x < 660)
			{
				bubbles[i]->Position(634, Height - 106);
				line[0][6] = bubbles[i]->Color();
				bubbles[i]->Location(0, 6);
			}
			else if (bubbles[i]->Position().x >= 660 && bubbles[i]->Position().x < 714)
			{
				bubbles[i]->Position(688, Height - 106);
				line[0][7] = bubbles[i]->Color();
				bubbles[i]->Location(0, 7);
			}
		}

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y)) //2번째 줄
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 376 && (line[0][0] || line[0][1] || line[1][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(348, Height - (106 + bubbles[i]->Scale().y));
				line[1][0] = bubbles[i]->Color();
				bubbles[i]->Location(1, 0);
			}
			else if (bubbles[i]->Position().x >= 376 && bubbles[i]->Position().x < 426 && (line[0][1] || line[0][2] || line[1][0] || line[1][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(400, Height - (106 + bubbles[i]->Scale().y));
				line[1][1] = bubbles[i]->Color();
				bubbles[i]->Location(1, 1);
			}
			else if (bubbles[i]->Position().x >= 426 && bubbles[i]->Position().x < 478 && (line[0][2] || line[0][3] || line[1][1] || line[1][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(452, Height - (106 + bubbles[i]->Scale().y));
				line[1][2] = bubbles[i]->Color();
				bubbles[i]->Location(1, 2);
			}
			else if (bubbles[i]->Position().x >= 478 && bubbles[i]->Position().x < 530 && (line[0][3] || line[0][4] || line[1][2] || line[1][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(504, Height - (106 + bubbles[i]->Scale().y));
				line[1][3] = bubbles[i]->Color();
				bubbles[i]->Location(1, 3);
			}
			else if (bubbles[i]->Position().x >= 530 && bubbles[i]->Position().x < 582 && (line[0][4] || line[0][5] || line[1][3] || line[1][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(556, Height - (106 + bubbles[i]->Scale().y));
				line[1][4] = bubbles[i]->Color();
				bubbles[i]->Location(1, 4);
			}
			else if (bubbles[i]->Position().x >= 582 && bubbles[i]->Position().x < 634 && (line[0][5] || line[0][6] || line[1][4] || line[1][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(608, Height - (106 + bubbles[i]->Scale().y));
				line[1][5] = bubbles[i]->Color();
				bubbles[i]->Location(1, 5);
			}
			else if (bubbles[i]->Position().x >= 634 && bubbles[i]->Position().x < 686 && (line[0][6] || line[0][7] || line[1][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(660, Height - (106 + bubbles[i]->Scale().y));
				line[1][6] = bubbles[i]->Color();
				bubbles[i]->Location(1, 6);
			}
		}

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 2)) //3번째 줄
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 348 && (line[1][0] || line[2][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(328, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][0] = bubbles[i]->Color();
				bubbles[i]->Location(2, 0);
			}
			else if (bubbles[i]->Position().x >= 348 && bubbles[i]->Position().x < 400 && (line[1][0] || line[1][1] || line[2][0] || line[2][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(376, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][1] = bubbles[i]->Color();
				bubbles[i]->Location(2, 1);
			}
			else if (bubbles[i]->Position().x >= 400 && bubbles[i]->Position().x < 452 && (line[1][1] || line[1][2] || line[2][1] || line[2][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(426, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][2] = bubbles[i]->Color();
				bubbles[i]->Location(2, 2);
			}
			else if (bubbles[i]->Position().x >= 452 && bubbles[i]->Position().x < 504 && (line[1][2] || line[1][3] || line[2][2] || line[2][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(478, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][3] = bubbles[i]->Color();
				bubbles[i]->Location(2, 3);
			}
			else if (bubbles[i]->Position().x >= 504 && bubbles[i]->Position().x < 556 && (line[1][3] || line[1][4] || line[2][3] || line[2][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(530, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][4] = bubbles[i]->Color();
				bubbles[i]->Location(2, 4);
			}
			else if (bubbles[i]->Position().x >= 556 && bubbles[i]->Position().x < 608 && (line[1][4] || line[1][5] || line[2][4] || line[2][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(582, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][5] = bubbles[i]->Color();
				bubbles[i]->Location(2, 5);
			}
			else if (bubbles[i]->Position().x >= 608 && bubbles[i]->Position().x < 660 && (line[1][5] || line[1][6] || line[2][5] || line[2][7]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(634, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][6] = bubbles[i]->Color();
				bubbles[i]->Location(2, 6);
			}
			else if (bubbles[i]->Position().x >= 660 && bubbles[i]->Position().x < 714 && (line[1][6] || line[1][7] || line[2][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(688, Height - (106 + bubbles[i]->Scale().y * 2));
				line[2][7] = bubbles[i]->Color();
				bubbles[i]->Location(2, 7);
			}
		}

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 3)) //4번째 줄
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 376 && (line[2][0] || line[2][1] || line[3][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(348, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][0] = bubbles[i]->Color();
				bubbles[i]->Location(3, 0);
			}
			else if (bubbles[i]->Position().x >= 376 && bubbles[i]->Position().x < 426 && (line[2][1] || line[2][2] || line[3][0] || line[3][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(400, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][1] = bubbles[i]->Color();
				bubbles[i]->Location(3, 1);
			}
			else if (bubbles[i]->Position().x >= 426 && bubbles[i]->Position().x < 478 && (line[2][2] || line[2][3] || line[3][1] || line[3][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(452, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][2] = bubbles[i]->Color();
				bubbles[i]->Location(3, 2);
			}
			else if (bubbles[i]->Position().x >= 478 && bubbles[i]->Position().x < 530 && (line[2][3] || line[2][4] || line[3][2] || line[3][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(504, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][3] = bubbles[i]->Color();
				bubbles[i]->Location(3, 3);
			}
			else if (bubbles[i]->Position().x >= 530 && bubbles[i]->Position().x < 582 && (line[2][4] || line[2][5] || line[3][3] || line[3][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(556, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][4] = bubbles[i]->Color();
				bubbles[i]->Location(3, 4);
			}
			else if (bubbles[i]->Position().x >= 582 && bubbles[i]->Position().x < 634 && (line[2][5] || line[2][6] || line[3][4] || line[3][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(608, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][5] = bubbles[i]->Color();
				bubbles[i]->Location(3, 5);
			}
			else if (bubbles[i]->Position().x >= 634 && bubbles[i]->Position().x < 686 && (line[2][6] || line[2][7] || line[3][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(660, Height - (106 + bubbles[i]->Scale().y * 3));
				line[3][6] = bubbles[i]->Color();
				bubbles[i]->Location(3, 6);
			}
		}

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 4)) //5번째 줄
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 348 && (line[3][0] || line[4][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(328, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][0] = bubbles[i]->Color();
				bubbles[i]->Location(4, 0);
			}
			else if (bubbles[i]->Position().x >= 348 && bubbles[i]->Position().x < 400 && (line[3][0] || line[3][1] || line[4][0] || line[4][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(376, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][1] = bubbles[i]->Color();
				bubbles[i]->Location(4, 1);
			}
			else if (bubbles[i]->Position().x >= 400 && bubbles[i]->Position().x < 452 && (line[3][1] || line[3][2] || line[4][1] || line[4][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(426, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][2] = bubbles[i]->Color();
				bubbles[i]->Location(4, 2);
			}
			else if (bubbles[i]->Position().x >= 452 && bubbles[i]->Position().x < 504 && (line[3][2] || line[3][3] || line[4][2] || line[4][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(478, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][3] = bubbles[i]->Color();
				bubbles[i]->Location(4, 3);
			}
			else if (bubbles[i]->Position().x >= 504 && bubbles[i]->Position().x < 556 && (line[3][3] || line[3][4] || line[4][3] || line[4][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(530, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][4] = bubbles[i]->Color();
				bubbles[i]->Location(4, 4);
			}
			else if (bubbles[i]->Position().x >= 556 && bubbles[i]->Position().x < 608 && (line[3][4] || line[3][5] || line[4][4] || line[4][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(582, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][5] = bubbles[i]->Color();
				bubbles[i]->Location(4, 5);
			}
			else if (bubbles[i]->Position().x >= 608 && bubbles[i]->Position().x < 660 && (line[3][5] || line[3][6] || line[4][5] || line[4][7]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(634, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][6] = bubbles[i]->Color();
				bubbles[i]->Location(4, 6);
			}
			else if (bubbles[i]->Position().x >= 660 && bubbles[i]->Position().x < 714 && (line[3][6] || line[3][7] || line[4][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(688, Height - (106 + bubbles[i]->Scale().y * 4));
				line[4][7] = bubbles[i]->Color();
				bubbles[i]->Location(4, 7);
			}
		}

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 5)) //6번째 줄
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 376 && (line[4][0] || line[4][1] || line[5][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(348, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][0] = bubbles[i]->Color();
				bubbles[i]->Location(5, 0);
			}
			else if (bubbles[i]->Position().x >= 376 && bubbles[i]->Position().x < 426 && (line[4][1] || line[4][2] || line[5][0] || line[5][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(400, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][1] = bubbles[i]->Color();
				bubbles[i]->Location(5, 1);
			}
			else if (bubbles[i]->Position().x >= 426 && bubbles[i]->Position().x < 478 && (line[4][2] || line[4][3] || line[5][1] || line[5][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(452, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][2] = bubbles[i]->Color();
				bubbles[i]->Location(5, 2);
			}
			else if (bubbles[i]->Position().x >= 478 && bubbles[i]->Position().x < 530 && (line[4][3] || line[4][4] || line[5][2] || line[5][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(504, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][3] = bubbles[i]->Color();
				bubbles[i]->Location(5, 3);
			}
			else if (bubbles[i]->Position().x >= 530 && bubbles[i]->Position().x < 582 && (line[4][4] || line[4][5] || line[5][3] || line[5][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(556, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][4] = bubbles[i]->Color();
				bubbles[i]->Location(5, 4);
			}
			else if (bubbles[i]->Position().x >= 582 && bubbles[i]->Position().x < 634 && (line[4][5] || line[4][6] || line[5][4] || line[5][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(608, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][5] = bubbles[i]->Color();
				bubbles[i]->Location(5, 5);
			}
			else if (bubbles[i]->Position().x >= 634 && bubbles[i]->Position().x < 686 && (line[4][6] || line[4][7] || line[5][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(660, Height - (106 + bubbles[i]->Scale().y * 5));
				line[5][6] = bubbles[i]->Color();
				bubbles[i]->Location(5, 6);
			}
		}

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 6)) //7번째 줄
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 346 && (line[5][0] || line[6][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(328, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][0] = bubbles[i]->Color();
				bubbles[i]->Location(6, 0);
			}
			else if (bubbles[i]->Position().x >= 350 && bubbles[i]->Position().x < 398 && (line[5][0] || line[5][1] || line[6][0] || line[6][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(376, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][1] = bubbles[i]->Color();
				bubbles[i]->Location(6, 1);
			}
			else if (bubbles[i]->Position().x >= 402 && bubbles[i]->Position().x < 450 && (line[5][1] || line[5][2] || line[6][1] || line[6][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(426, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][2] = bubbles[i]->Color();
				bubbles[i]->Location(6, 2);
			}
			else if (bubbles[i]->Position().x >= 454 && bubbles[i]->Position().x < 502 && (line[5][2] || line[5][3] || line[6][2] || line[6][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(478, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][3] = bubbles[i]->Color();
				bubbles[i]->Location(6, 3);
			}
			else if (bubbles[i]->Position().x >= 506 && bubbles[i]->Position().x < 554 && (line[5][3] || line[5][4] || line[6][3] || line[6][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(530, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][4] = bubbles[i]->Color();
				bubbles[i]->Location(6, 4);
			}
			else if (bubbles[i]->Position().x >= 558 && bubbles[i]->Position().x < 606 && (line[5][4] || line[5][5] || line[6][4] || line[6][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(582, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][5] = bubbles[i]->Color();
				bubbles[i]->Location(6, 5);
			}
			else if (bubbles[i]->Position().x >= 610 && bubbles[i]->Position().x < 658 && (line[5][5] || line[5][6] || line[6][5] || line[6][7]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(634, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][6] = bubbles[i]->Color();
				bubbles[i]->Location(6, 6);
			}
			else if (bubbles[i]->Position().x >= 662 && bubbles[i]->Position().x < 714 && (line[5][6] || line[5][7] || line[6][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(688, Height - (106 + bubbles[i]->Scale().y * 6));
				line[6][7] = bubbles[i]->Color();
				bubbles[i]->Location(6, 7);
			}
		}
		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 7)) //7번째 줄 아래
		{
			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 374 && (line[6][0] || line[6][1]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
			else if (bubbles[i]->Position().x >= 378 && bubbles[i]->Position().x < 424 && (line[6][1] || line[6][2]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
			else if (bubbles[i]->Position().x >= 428 && bubbles[i]->Position().x < 476 && (line[6][2] || line[6][3]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
			else if (bubbles[i]->Position().x >= 480 && bubbles[i]->Position().x < 528 && (line[6][3] || line[6][4]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
			else if (bubbles[i]->Position().x >= 532 && bubbles[i]->Position().x < 580 && (line[6][4] || line[6][5]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
			else if (bubbles[i]->Position().x >= 584 && bubbles[i]->Position().x < 658 && (line[6][5] || line[6][6]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
			else if (bubbles[i]->Position().x >= 662 && bubbles[i]->Position().x < 714 && (line[6][6] || line[6][7]))
			{
				bubbles[i]->Velocity(D3DXVECTOR2(0, 0));
				bubbles[i]->Position(Width + 100, Height + 100);
			}
		}
	}
	bg->Update(V, P);

	mach->Update(V, P);
	aw->Update(V, P);

	nextbubbles->Update(V, P);
	//next_nextbubbles->Update(V, P);

	for (Bubble* bubble : bubbles)
		bubble->Update(V, P);
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		//생성 순서
		//배경->장치->화살표->버블
		bg->Render();
		mach->Render();
		aw->Render();

		nextbubbles->Render();
		//next_nextbubbles->Render();
		for (Bubble* bubble : bubbles)
			bubble->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}