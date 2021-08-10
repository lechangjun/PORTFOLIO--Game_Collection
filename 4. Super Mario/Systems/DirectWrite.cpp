#include "stdafx.h"
#include "DirectWrite.h"

DirectWrite* DirectWrite::instance = NULL;

IDWriteFactory* DirectWrite::writeFactory = NULL;
ID2D1DeviceContext* DirectWrite::deviceContext = NULL;
ID2D1Bitmap1* DirectWrite::bitmap = NULL;
IDXGISurface* DirectWrite::surface = NULL;

ID2D1SolidColorBrush* DirectWrite::brush = NULL;
IDWriteTextFormat* DirectWrite::format = NULL;

void DirectWrite::Create()
{
	assert(instance == NULL);

	instance = new DirectWrite();
}

void DirectWrite::Delete()
{
	SAFE_DELETE(instance);
}

DirectWrite * DirectWrite::Get()
{
	return instance;
}

DirectWrite::DirectWrite()
{
	HRESULT hr;

	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown **)&writeFactory
		//여러 프로세스 내 구성 요소에서 캐시된 글꼴 데이터를 재사용할 수 있음을 표시
	);
	assert(SUCCEEDED(hr));

	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_WARNING; //오류 메세지 및 경고를 디버그 계층으로
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	//액세스 및 쓰기를 위한 동기화를 제공하여 여러 스레드에서 안전하게 액세스할 수 있도록 함
	assert(SUCCEEDED(hr));


	IDXGIDevice* dxgiDevice;
	hr = Device->QueryInterface(&dxgiDevice);
	assert(SUCCEEDED(hr));

	hr = factory->CreateDevice(dxgiDevice, &device);
	assert(SUCCEEDED(hr));

	hr = device->CreateDeviceContext
	(
		D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext
		//여러 스레드에 렌더링 작업을 분산함
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer();
}

DirectWrite::~DirectWrite()
{
	DeleteBackBuffer();
}

void DirectWrite::CreateBackBuffer()
{
	HRESULT hr;

	hr = SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void **)&surface);
	assert(SUCCEEDED(hr));


	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	//알파를 포함하여 채널당 8비트를 지원하는 4성분, 32비트 무부호 정규화 정수 형식
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE; //알파값 무시
	bp.dpiX = 96; //글씨 크기 조정
	bp.dpiY = 96; // "
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	//비트맵은 장치 컨텍스트 대상으로 사용할 수 있습니다.
	//비트맵은 입력으로 사용할 수 없습니다.
	bp.colorContext = NULL;

	hr = deviceContext->CreateBitmapFromDxgiSurface(surface, &bp, &bitmap);
	assert(SUCCEEDED(hr));

	deviceContext->SetTarget(bitmap);


	hr = deviceContext->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &brush);
	//글씨 색깔 조정
	assert(SUCCEEDED(hr));

	writeFactory->CreateTextFormat
	(//글씨 양식
		L"돋움체", NULL
		, DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL
		, 15, L"ko", &format
	);
}

void DirectWrite::DeleteBackBuffer()
{
	deviceContext->SetTarget(NULL);

	SAFE_RELEASE(brush);
	SAFE_RELEASE(format);

	SAFE_RELEASE(bitmap);
	SAFE_RELEASE(surface);
}

void DirectWrite::RenderText(wstring & text, RECT & rect)
{//텍스트 가시화
	D2D1_RECT_F temp;
	temp.left = (float)rect.left;
	temp.top = (float)rect.top;
	temp.right = (float)rect.right;
	temp.bottom = (float)rect.bottom;

	DirectWrite::GetDC()->DrawTextW(text.c_str(), text.size(), format, &temp, brush);
}