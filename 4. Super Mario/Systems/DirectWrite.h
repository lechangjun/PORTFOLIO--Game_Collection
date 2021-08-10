#pragma once

class DirectWrite
{
public:
	static void Create();
	static void Delete();

	static DirectWrite* Get();
	static ID2D1DeviceContext* GetDC() { return deviceContext; }

	static void CreateBackBuffer();
	static void DeleteBackBuffer();

	static void RenderText(wstring& text, RECT& rect);

private:
	static DirectWrite* instance;

private:
	DirectWrite();
	~DirectWrite();

private:
	ID2D1Factory1* factory; //Direct2D 리소스 생성
	static IDWriteFactory* writeFactory;

	ID2D1Device* device; //2D에서 사용할 수 있는 리소스
	static ID2D1DeviceContext* deviceContext;
	//렌더링하는데 사용되는 상태 및 명령 버퍼 집합

	static ID2D1Bitmap1* bitmap; //비트맵 구현
	static IDXGISurface* surface; 
	//화상 데이터 객체에 대한 인터페이스 구현

	static ID2D1SolidColorBrush* brush; //단색으로 영역을 그림
	static IDWriteTextFormat* format; //텍스트를 사용하는 폰트 및 단락 특성을 설정
};