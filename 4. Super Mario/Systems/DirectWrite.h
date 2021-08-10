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
	ID2D1Factory1* factory; //Direct2D ���ҽ� ����
	static IDWriteFactory* writeFactory;

	ID2D1Device* device; //2D���� ����� �� �ִ� ���ҽ�
	static ID2D1DeviceContext* deviceContext;
	//�������ϴµ� ���Ǵ� ���� �� ��� ���� ����

	static ID2D1Bitmap1* bitmap; //��Ʈ�� ����
	static IDXGISurface* surface; 
	//ȭ�� ������ ��ü�� ���� �������̽� ����

	static ID2D1SolidColorBrush* brush; //�ܻ����� ������ �׸�
	static IDWriteTextFormat* format; //�ؽ�Ʈ�� ����ϴ� ��Ʈ �� �ܶ� Ư���� ����
};