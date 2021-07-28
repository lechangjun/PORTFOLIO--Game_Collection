#include "stdafx.h"
#include "Device.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitWindow(hInstance, nShowCmd);
	InitDirect3D(hInstance);

	Running();

	Destroy();

	return 0;
}


HWND Hwnd = NULL;
wstring Title = L"Draw Sprite Dohee";

IDXGISwapChain* SwapChain;
ID3D11Device* Device;
ID3D11DeviceContext* DeviceContext;
ID3D11RenderTargetView* RTV;

Keyboard* Key;
Time* Timer;

void InitWindow(HINSTANCE hInstance, int ShowWnd)
{
	//Register Class
	{
		WNDCLASSEX wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.cbClsExtra = NULL;
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = Title.c_str();
		wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		WORD check = RegisterClassEx(&wndClass);
		assert(check != 0);
	}

	//Create Handle
	{
		Hwnd = CreateWindowEx
		(
			NULL,
			Title.c_str(),
			Title.c_str(),
			WS_OVERLAPPEDWINDOW,//창 겹치는거
			CW_USEDEFAULT, CW_USEDEFAULT, //디폴트 창위치?
			Width, Height, //창 크기
			NULL,
			NULL,
			hInstance,
			NULL
		);
		assert(Hwnd != NULL);
	}

	//left right top bottom
	//left자료형 LONG
	RECT rect = { 0, 0, (LONG)Width, (LONG)Height };

	//중심 다시 맞춰야함
	//left-top  right-bottom
	//GetSystemMetrics: 스크린의 실제 크기
	//SM_CXSCREEN: X 크기
	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		Hwnd,
		centerX, centerY,
		rect.right - rect.left, //크기 나옴
		rect.bottom - rect.top, //winapi에서 top을 빼야 실제크기나옴
		TRUE
	);

	ShowWindow(Hwnd, ShowWnd);
	UpdateWindow(Hwnd);
}

void InitDirect3D(HINSTANCE hInstance)
{
	//Create Device and DeviceContext, SwapChain
	{
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = Width;
		bufferDesc.Height = Height;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferDesc = bufferDesc;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = Hwnd;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &desc, &SwapChain, &Device, NULL, &DeviceContext
		);
		assert(SUCCEEDED(hr));
	}

	//Create BackBuffer
	{
		HRESULT hr;

		ID3D11Texture2D* BackBuffer;
		hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		assert(SUCCEEDED(hr));

		hr = Device->CreateRenderTargetView(BackBuffer, NULL, &RTV);
		assert(SUCCEEDED(hr));
		BackBuffer->Release();

		DeviceContext->OMSetRenderTargets(1, &RTV, NULL);
	}

	//Create Viewport
	{
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = Width;
		viewport.Height = Height;

		DeviceContext->RSSetViewports(1, &viewport);
	}
}

void Destroy()
{

	SwapChain->Release();
	Device->Release();
	DeviceContext->Release();
	RTV->Release();
}

WPARAM Running()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	ImGui::Create(Hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();

	Key = new Keyboard();
	Timer = new Time();

	InitScene();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Timer->Update();

			Update();
			ImGui::Update();

			Render();
		}
	}
	DestroyScene();

	delete Key;

	delete Timer;
	ImGui::Delete();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc((UINT*)hwnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				DestroyWindow(hwnd);
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


