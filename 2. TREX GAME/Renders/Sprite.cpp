#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(wstring textureFile, wstring shaderFile)
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float endX, float endY)
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);
}

void Sprite::Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{

	textureFile = spriteFile;

	shader = new Shader(shaderFile);
	srv = Sprites::Load(spriteFile); //알아서 srv가 들어감
	shader->AsShaderResource("Map")->SetResource(srv);

	HRESULT hr; //HRESULT: 디버깅이 용이함 (SUCCEEDE0 D/FAILED 1)
	D3DX11_IMAGE_INFO info;
	hr = D3DX11GetImageInfoFromFile(spriteFile.c_str(), NULL, &info, NULL); //해당 파일에 대한 임의 정보
		//spriteFile.c_str(): sprite File의 이름
	assert(SUCCEEDED(hr));

	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	Vertex vertices[6];

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	//UV좌표
	vertices[0].Uv = D3DXVECTOR2(startX, endY); //0, 1
	vertices[1].Uv = D3DXVECTOR2(startX, startY); //0, 0
	vertices[2].Uv = D3DXVECTOR2(endX, endY); //1, 1
	vertices[3].Uv = D3DXVECTOR2(endX, endY); //1, 1
	vertices[4].Uv = D3DXVECTOR2(startX, startY); //0, 0
	vertices[5].Uv = D3DXVECTOR2(endX, startY); //1, 0

	float sizeX = (endX > 0) ? endX * (float)info.Width : (float)info.Width;
	sizeX -= startX * (float)info.Width;

	float sizeY = (endY > 0) ? endY * (float)info.Height : (float)info.Height;
	sizeY -= startY * (float)info.Height;

	scale = D3DXVECTOR2(sizeX, sizeY);
	textureSize = D3DXVECTOR2((float)info.Width, (float)info.Height);

	UpdateWorld();

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);

	Sprites::Remove(textureFile);
}

void Sprite::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
}

void Sprite::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	shader->Draw(0, 0, 6);
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 & vec)
{
	position = vec;

	UpdateWorld();
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

	UpdateWorld();
}

void Sprite::UpdateWorld()
{
	D3DXMATRIX W, S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	W = S * T;

	shader->AsMatrix("World")->SetMatrix(W);
}

//----------------------------------------------------------------------------------------
// Sprites (Sprite클래스는, Sprites클래스의 friend class로 Sprites 클래스에 직접 접근 가능함)
//----------------------------------------------------------------------------------------

map<wstring, Sprites::SpriteDesc> Sprites::spriteMap; //static 변수의 경우, 별도의 전역 변수를 한번 더 선언해야함
//클래스 뒤에 scope(::) 붙임

//SRV를 Load함수로 가져오고, Remove함수로 지움
//있으면 ref 카운트만 늘려주고
//없으면 새로 생성함 (같은 이미지일 수도 있으니;)
ID3D11ShaderResourceView * Sprites::Load(wstring file) 
{
	//<--spriteMap에 파일이 있으면--> (file을 key로 가진 갯수가 0보다 크면)
	if (spriteMap.count(file) > 0)
	{
		spriteMap[file].RefCount++; //reference count를 올려주고, 
		return spriteMap[file].SRV; //SRV 리턴
	}
	
	//<--spriteMap에 파일이 없으면 생성함-->
	HRESULT hr;
	ID3D11ShaderResourceView* srv;
	hr = D3DX11CreateShaderResourceViewFromFile(Device, file.c_str(), NULL, NULL, &srv, NULL); //c_str: const char*
	assert(SUCCEEDED(hr));
	SpriteDesc desc;
	desc.RefCount++; //reference count 올려줌
	desc.SRV = srv;
	spriteMap[file] = desc; //key: 스프라이트file //value: desc //desc안에 RefCount랑 SRV있음
	return desc.SRV; //SRV 리턴
}

void Sprites::Remove(wstring file)
{
	UINT count = spriteMap.count(file); //1 or 0 (키 값 중복불가)
	assert(count > 0); //데이터가 없으면 에러

	spriteMap[file].RefCount--; //reference count -1

	if (spriteMap[file].RefCount < 1) //키값이 file인 밸류값 멤버중 ReftCount가 1보다 작으면
	{
		SAFE_RELEASE(spriteMap[file].SRV); //밸류중 SRV 메모리 반환함
		spriteMap.erase(file); //map에서 키값이 file인 데이터 삭제
	}
}

void Sprite::AutoMove(float speed, float num1, float num2)
{
	D3DXVECTOR2 position = Position();

	position.x -= speed;

	if (position.x < num1)
	{
		position.x = num2;
		position.x -= speed;
	}

	Position(position);
}

float Sprite::xMin()
{
	return position.x - scale.x / 2;
}

float Sprite::xMax()
{
	return position.x + scale.x / 2;
}

float Sprite::yMin()
{
	return position.y - scale.y / 2;
}

float Sprite::yMax()
{
	return position.y + scale.y / 2;
}
