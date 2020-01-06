#include "D3DApp.h"

namespace {
	D3DApp *g_pd3dApp = nullptr;
}


// 因为类成员函数在有this指针的情况下不能被当成windows回调函数，需要曲线救国
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return g_pd3dApp->MsgProc(hwnd, msg, wParam, lParam);
}

D3DApp::D3DApp(HINSTANCE hInstance)
	:m_hAppInst(hInstance)
	, m_MainWindowCaption(L"Dx11 Initial")
	,m_ClientWidth(800)
	,m_ClientHeight(600)
	,m_hMainWnd(nullptr)
	,m_bEnable4xMsaa(true)
	,m_4xMsaaQuality(0)
	,m_pd3dDevice(nullptr)
	,m_pd3dDevice1(nullptr)
	,m_pd3dDeviceContext(nullptr)
	,m_pd3dDeviceContext1(nullptr)
	,m_pSwapChain(nullptr)
	,m_pSwapChain1(nullptr)
	,m_pDepthStencilBuffer(nullptr)
	,m_pRenderTargetView(nullptr)
	,m_pDepthStencilView(nullptr)
{
	ZeroMemory(&m_ScreenViewport, sizeof(D3D11_VIEWPORT));

	g_pd3dApp = this;
}

D3DApp::~D3DApp()
{
	if (m_pd3dDeviceContext)
	{
		m_pd3dDeviceContext->ClearState();
	}
}

HINSTANCE D3DApp::AppInst() const
{
	return m_hAppInst;
}

HWND D3DApp::MainWnd() const
{
	return m_hMainWnd;
}

float D3DApp::AspectRatio() const
{
	return static_cast<float>(m_ClientWidth / m_ClientHeight);
}

int D3DApp::Run()
{
	//消息循环
	return 0;
}

bool D3DApp::Init()
{
	if (!InitMainWindow())
	{
		return false;
	}
	if (!InitD3D())
	{
		return false;
	}
	return true;
}

LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

bool D3DApp::InitMainWindow()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = m_hAppInst;
	wc.lpfnWndProc = MainWndProc;
	wc.lpszClassName = L"D3DWndClassName";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// Register Class
	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed", 0, 0);
		return false;
	}
	
	RECT R = { 0,0,m_ClientWidth,m_ClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	m_hMainWnd = CreateWindow(L"D3DWndClassName", m_MainWindowCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hAppInst, 0);

	if (!m_hMainWnd)
	{
		MessageBox(0, L"Create Window Failed!", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;

}

bool D3DApp::InitD3D()
{
	return false;
}
