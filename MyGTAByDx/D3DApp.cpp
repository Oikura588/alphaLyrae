#include "D3DApp.h"

#include "DXTrace.h"
#include "DXUtil.h"

namespace {
	D3DApp *g_pd3dApp = nullptr;
}


// ��Ϊ���Ա��������thisָ�������²��ܱ�����windows�ص���������Ҫ���߾ȹ�
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
	,m_bLocKMouse(false)
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
	MSG msg = { 0 };

	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}
		else {
			UpdateScene(0.f);
			DrawScene();

		}

	}


	//��Ϣѭ��
	return (int)msg.wParam;
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

void D3DApp::SetRenderPipeLine()
{
	assert(m_pd3dDeviceContext);
	assert(m_pd3dDevice);
	assert(m_pSwapChain);

	if (m_pd3dDevice1 != nullptr)
	{
		assert(m_pd3dDeviceContext1);
		assert(m_pd3dDevice1);
		assert(m_pSwapChain1);
	}

	// �ͷ���Ⱦ��������õ��������Դ
	m_pRenderTargetView.Reset();
	m_pDepthStencilView.Reset();
	m_pDepthStencilBuffer.Reset();

	// ���轻�����������´�����ȾĿ����ͼ
	ComPtr<ID3D11Texture2D> backBuffer;
	HR(m_pSwapChain->ResizeBuffers(1, m_ClientWidth, m_ClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	HR(m_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_pRenderTargetView.GetAddressOf()));

	// ���õ��Զ�����

	backBuffer.Reset();


	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_ClientWidth;
	depthStencilDesc.Height = m_ClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Ҫʹ�� 4X MSAA? --��Ҫ������������MASS����
	if (m_bEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}



	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	// ������Ȼ������Լ����ģ����ͼ
	HR(m_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, m_pDepthStencilBuffer.GetAddressOf()));
	HR(m_pd3dDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), nullptr, m_pDepthStencilView.GetAddressOf()));


	// ����ȾĿ����ͼ�����/ģ�建������ϵ�����
	m_pd3dDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());

	// �����ӿڱ任
	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = static_cast<float>(m_ClientWidth);
	m_ScreenViewport.Height = static_cast<float>(m_ClientHeight);
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;

	m_pd3dDeviceContext->RSSetViewports(1, &m_ScreenViewport);

}

LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
	case WM_ACTIVATE:
	{
		// test if window is being activated 
		if (LOWORD(wParam) != WA_INACTIVE)
		{
			// application is being activated 
			m_bLocKMouse = true;
			//SetCursorPos(m_ClientWidth / 2, m_ClientHeight / 2);
		}
		else
		{
			m_bLocKMouse = false;
			// application is being deactivated 
		}
	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
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
	HRESULT hr = S_OK;

	//����D3D�豸��������
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ���Եȼ�
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;

	// ��������

	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	D3D_DRIVER_TYPE driverType;

	for (UINT drivertypeIndex=0;drivertypeIndex<numDriverTypes;++drivertypeIndex)
	{
		driverType = driverTypes[drivertypeIndex];
		hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, m_pd3dDevice.GetAddressOf(), &featureLevel, m_pd3dDeviceContext.GetAddressOf());
		if (hr==E_INVALIDARG)
		{
			// Direct3D 11.0 ��API������D3D_FEATURE_LEVEL_11_1������������Ҫ�������Եȼ�11.0�Լ����µİ汾
			hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, m_pd3dDevice.GetAddressOf(), &featureLevel, m_pd3dDeviceContext.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			break;
		}
	}

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	// �����豸�ɹ�

	// ���֧�����Եȼ�

	if (featureLevel!=D3D_FEATURE_LEVEL_11_0&& featureLevel!=D3D_FEATURE_LEVEL_11_1)
	{
		MessageBox(0, L"D3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}
	// ��� MSAA �����ȼ�

	m_pd3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality);

	if (m_4xMsaaQuality<=0)
	{
		MessageBox(0, L"4xMSAA don't support", 0, 0);
		return false;
	}


	ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
	ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;	// D3D11.0(����DXGI1.1)�Ľӿ���
	ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;	// D3D11.1(����DXGI1.2)���еĽӿ���



	// Ϊ����ȷ���� DXGI������������������Ҫ��ȡ���� D3D�豸 �� DXGI�������������������
	// "IDXGIFactory::CreateSwapChain: This function is being called with a device from a different IDXGIFactory."
	HR(m_pd3dDevice.As(&dxgiDevice));
	HR(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1.GetAddressOf())));

	// �鿴�ö����Ƿ����IDXGIFactory2�ӿ�
	hr = dxgiFactory1.As(&dxgiFactory2);
	// �����������˵��֧��D3D11.1
	if (dxgiFactory2 != nullptr)
	{
		HR(m_pd3dDevice.As(&m_pd3dDevice1));
		HR(m_pd3dDeviceContext.As(&m_pd3dDeviceContext1));
		// �����ֽṹ����������������
		DXGI_SWAP_CHAIN_DESC1 sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Width = m_ClientWidth;
		sd.Height = m_ClientHeight;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		// �Ƿ���4�����ز�����
		if (m_bEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd;
		fd.RefreshRate.Numerator = 60;
		fd.RefreshRate.Denominator = 1;
		fd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		fd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fd.Windowed = TRUE;
		// Ϊ��ǰ���ڴ���������
		HR(dxgiFactory2->CreateSwapChainForHwnd(m_pd3dDevice.Get(), m_hMainWnd, &sd, &fd, nullptr, m_pSwapChain1.GetAddressOf()));
		HR(m_pSwapChain1.As(&m_pSwapChain));
	}
	else
	{
		// ���DXGI_SWAP_CHAIN_DESC��������������
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = m_ClientWidth;
		sd.BufferDesc.Height = m_ClientHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		// �Ƿ���4�����ز�����
		if (m_bEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = m_hMainWnd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;
		HR(dxgiFactory1->CreateSwapChain(m_pd3dDevice.Get(), &sd, m_pSwapChain.GetAddressOf()));
	}

	// ���Խ�ֹalt+enterȫ��
	dxgiFactory1->MakeWindowAssociation(m_hMainWnd, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

	// ÿ�����ڱ����µ�����С��ʱ�򣬶���Ҫ�������OnResize���������ڵ���
	// �Ա�������ظ�
	SetRenderPipeLine();

	return true;

}
