#include "stdafx.h"
#include "Device.h"
#include "Objects/Background.h"
#include "Objects/Bubble.h"

Background* bg; //���
Sprite* mach; //���
Sprite* aw; //ȭ��ǥ
vector<Bubble*>bubbles; //�߻� ����

int NextBubble; //���� ����
Sprite* nextbubbles;
int Next_NextBubble; //�ٴ��� ����
Sprite* next_nextbubbles;

//�浹 ����
//�� �ٿ� 8���� 7��
int line[8][8] = { 0 };

int confirm[8][8] = { 0 };

bool BubbleCheck(int y, int x, int color) //ó�� ���� ����Ʈ����
{
	if (y > 7 || y < 0 || x > 7 || x < 0) //����
		return false;
	if (line[y][x] == 0) //���� ����
		return false;
	if (line[y][x] != color) //���� ������
		return false;
	if (confirm[y][x] == 10) 
		return false;

	return true;
}

bool check(int y, int x) //^ �Ŀ� ���� ���� ����Ʈ����
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

	bg = new Background(L"../_Shaders/008_Sprite.fx"); //���

	//���
	mach = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 8, 713, 84, 759);
	mach->Position(Width/2, 46);
	mach->Scale(100, 100);

	//ȭ��
	aw = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 12, 488, 34, 543);
	aw->Position(Width/2, 76);
	aw->Scale(50, 125);

	//���� �� ����
	NextBubble = Math::Random(0, 99999) % 5 + 1;
	//Next_NextBubble = Math::Random(0, 89999) % 5 + 1;

	switch (NextBubble)
	{
	case 1: //�Ķ���
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1187, 28, 1204);
		break;
	case 2: //������			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1214, 28, 1231);
		break;
	case 3: //�����			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1241, 28, 1258);
		break;
	case 4: //�ʷϻ�			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1268, 28, 1285);
		break;
	case 5: //�����			   		   
		nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1295, 28, 1312);
		break;
	}

	//switch (Next_NextBubble)
	//{
	//case 1: //�Ķ���
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1187, 28, 1204);
	//	break;
	//case 2: //������			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1214, 28, 1231);
	//	break;
	//case 3: //�����			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1241, 28, 1258);
	//	break;
	//case 4: //�ʷϻ�			   		   
	//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", shaderFile, 11, 1268, 28, 1285);
	//	break;
	//case 5: //�����			   		   
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


	if (bubbles.size() > 2) //������ ������ 3�� �̻��� ��
	{
		queue<int> Qy;//��
		queue<int> Qx;//��
		queue<int> Qc;//���� 

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				confirm[i][j] = 0;
			}
		}

		int lastbubble = bubbles.size() - 1; //�������� �� ����
		Qy.push((int)(bubbles[lastbubble]->Location().x)), Qx.push((int)(bubbles[lastbubble]->Location().y)), Qc.push(1);
		int bubbleColor = bubbles[lastbubble]->Color(); //^������ ��
		int colorCount = 0; //ī��Ʈ

		while (Qy.empty() == false)
		{
			int Py = Qy.front(); Qy.pop(); //���� y��ǥ
			int Px = Qx.front(); Qx.pop(); //���� x��ǥ
			int Pc = Qc.front(); Qc.pop(); //���� ī��Ʈ
			colorCount = Pc;
			if (!(Py >= 0 && Py <= 8) || !(Px >= 0 && Px <= 8))
			{
				colorCount = Pc;
				break;
			}
			if (confirm[Py][Px] == 10) continue;
			confirm[Py][Px] = 10;//Ȯ�ο�

			//��
			if (BubbleCheck(Py - 1, Px, bubbleColor))
				Qy.push(Py - 1), Qx.push(Px), Qc.push(Pc + 1);
			//��
			if (BubbleCheck(Py, Px + 1, bubbleColor))
				Qy.push(Py), Qx.push(Px + 1), Qc.push(Pc + 1);
			//��
			if (BubbleCheck(Py + 1, Px, bubbleColor))
				Qy.push(Py + 1), Qx.push(Px), Qc.push(Pc + 1);
			//��
			if (BubbleCheck(Py, Px - 1, bubbleColor))
				Qy.push(Py), Qx.push(Px - 1), Qc.push(Pc + 1);
			if (Py % 2 == 1)
			{
				//���
				if (BubbleCheck(Py - 1, Px + 1, bubbleColor))
					Qy.push(Py - 1), Qx.push(Px + 1), Qc.push(Pc + 1);
				//����
				if (BubbleCheck(Py + 1, Px + 1, bubbleColor))
					Qy.push(Py + 1), Qx.push(Px + 1), Qc.push(Pc + 1);
			}
			else
			{
				//�»�
				if (BubbleCheck(Py - 1, Px - 1, bubbleColor))
					Qy.push(Py - 1), Qx.push(Px - 1), Qc.push(Pc + 1);
				//����
				if (BubbleCheck(Py + 1, Px - 1, bubbleColor))
					Qy.push(Py + 1), Qx.push(Px - 1), Qc.push(Pc + 1);
			}
		}
		if (colorCount >= 3)//�������� 3�� �̻�
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
						line[i][j] = 0; //line�� ����� ���� �� 0���� �ʱ�ȭ��
					}
				}
			}
		}

		if (bubbles.size() != 0) //������� ������ �ϳ��� ���� ��
		{

			for (int i = 0; i < bubbles.size(); i++) //0���� ������� ���� ũ�⸸ŭ
			{
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < 8; k++)
					{
						confirm[j][k] = 0; //�迭 0���� �ʱ�ȭ
					}
				}

				Qy.push((int)(bubbles[i]->Location().x)), Qx.push((int)(bubbles[i]->Location().y)), Qc.push(1);
				bubbleColor = bubbles[i]->Color();
				colorCount = 0; //ī��Ʈ 0
				while (Qy.empty() == false)
				{
					int cy = Qy.front(); Qy.pop();//cy = ���� y��ǥ
					int cx = Qx.front(); Qx.pop();//cx = ���� x��ǥ

					if (cy == 0) //���� y��ǥ�� 0�϶�
						colorCount = 1; //ī��Ʈ 1

					if (!(cy >= 0 && cy <= 8) || !(cx >= 0 && cx <= 8))
					{//y��ǥ x��ǥ�� ���� ��
						break;
					}
					if (confirm[cy][cx] == 10) continue;
					confirm[cy][cx] = 10;

					//��
					if (check(cy - 1, cx)) //y-1 x�� �״��
						Qy.push(cy - 1), Qx.push(cx);
					//��
					if (check(cy, cx + 1)) //y�� �״�� x+1
						Qy.push(cy), Qx.push(cx + 1);
					//��
					if (check(cy + 1, cx))
						Qy.push(cy + 1), Qx.push(cx);
					//��
					if (check(cy, cx - 1))
						Qy.push(cy), Qx.push(cx - 1);
					if (cy % 2 == 1)
					{
						//���
						if (check(cy - 1, cx + 1))
							Qy.push(cy - 1), Qx.push(cx + 1);
						//����
						if (check(cy + 1, cx + 1))
							Qy.push(cy + 1), Qx.push(cx + 1);
					}
					else
					{
						//�»�
						if (check(cy - 1, cx - 1))
							Qy.push(cy - 1), Qx.push(cx - 1);
						//����
						if (check(cy + 1, cx - 1))
							Qy.push(cy + 1), Qx.push(cx - 1);
					}
				}
				if (colorCount == 0) //���� �� ������ ������ų� ���� ��
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
	//ȭ��ǥ ȸ��(����)
	if (Key->Press(VK_RIGHT) && aw->Rotation() > -87.0f)
		aw->Rotation(aw->Rotation() - 0.05f);
	//ȭ��ǥ ȸ��(������)
	if (Key->Down(VK_SPACE))
	{ //���� ���� �� �߻�
		wstring file = Shaders + L"008_Sprite.fx";

		float angle = aw->Rotation() + 90;
		Bubble* bubble = new Bubble(file, aw->Position(), angle, 0.9, NextBubble);
		bubbles.push_back(bubble);

		NextBubble= Math::Random(0, 666666) % 5 + 1;
		//NextBubble = Next_NextBubble;
		//Next_NextBubble = Math::Random(0, 666666) % 5 + 1;

		switch (NextBubble)
		{
		case 1: //�Ķ���
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1187, 28, 1204);
			break;
		case 2: //������			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1214, 28, 1231);
			break;
		case 3: //�����			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1241, 28, 1258);
			break;
		case 4: //�ʷϻ�			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1268, 28, 1285);
			break;
		case 5: //�����			   		   
			nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1295, 28, 1312);
			break;
		}
		nextbubbles->Position(Width / 2, 76);
		nextbubbles->Scale(52, 52);

		//switch (Next_NextBubble)
		//{
		//case 1: //�Ķ���
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1187, 28, 1204);
		//	break;
		//case 2: //������			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1214, 28, 1231);
		//	break;
		//case 3: //�����			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1241, 28, 1258);
		//	break;
		//case 4: //�ʷϻ�			   		   
		//	next_nextbubbles = new Sprite(L"../_Textures/PuzzleBobble/PuzzleBobble.png", file, 11, 1268, 28, 1285);
		//	break;
		//case 5: //�����			   		   
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
		if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 >= Height - 106) //1��° ��
		{
			bubbles[i]->Velocity(D3DXVECTOR2(0, 0));

			if (bubbles[i]->Position().x >= 296 && bubbles[i]->Position().x < 348)
			{
				bubbles[i]->Position(328, Height - 106);
				line[0][0] = bubbles[i]->Color(); //0,0�� �� ����
				bubbles[i]->Location(0, 0); //��ġ ����
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

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y)) //2��° ��
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

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 2)) //3��° ��
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

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 3)) //4��° ��
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

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 4)) //5��° ��
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

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 5)) //6��° ��
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

		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 6)) //7��° ��
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
		else if (bubbles[i]->Position().y + bubbles[i]->Scale().y / 2 > Height - (106 + bubbles[i]->Scale().y * 7)) //7��° �� �Ʒ�
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
		//���� ����
		//���->��ġ->ȭ��ǥ->����
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