/*=============================================================================
	D3DApp.h: Base Class which has a Basic Windows
=============================================================================*/
#pragma once
#include "DXUtil.h"



class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	HINSTANCE	AppInst() const;		//获取AppInstance
	HWND		MainWnd() const;		//获取主窗口句柄
	float		AspectRatio() const;	//获取屏幕宽高比

	int Run();							//窗口主循环


	virtual bool Init();				//初始化窗口和D3D部分
	virtual void SetRenderPipeLine();	//设置管线资源，分辨率变化等需要调用
	virtual void UpdateScene(float dt) = 0;   // 子类需要实现该方法，完成每一帧的更新
	virtual void DrawScene() = 0;             // 子类需要实现该方法，完成每一帧的绘制


	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HINSTANCE	m_hAppInst;				//应用程序句柄
	HWND		m_hMainWnd;				//主窗口句柄
	bool		m_bEnable4xMsaa;		//是否支持4倍多重采样
	UINT		m_4xMsaaQuality;		//MSAA支持的质量等级



	//D3D11
	ComPtr<ID3D11Device>			m_pd3dDevice;			//D3D设备
	ComPtr<ID3D11DeviceContext>		m_pd3dDeviceContext;	//D3D上下文
	ComPtr<IDXGISwapChain>			m_pSwapChain;			//D3D交换链

	//D3D11.1
	ComPtr<ID3D11Device1>			m_pd3dDevice1;			//D3D11
	ComPtr<ID3D11DeviceContext1>	m_pd3dDeviceContext1;	//
	ComPtr<IDXGISwapChain1>			m_pSwapChain1;			//d3d11.1交换链


	//通用资源
	ComPtr<ID3D11Texture2D>			m_pDepthStencilBuffer;	//深度模板缓冲
	ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;	//RT View
	ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;	//D/S View


	D3D11_VIEWPORT m_ScreenViewport;                      // 视口


	//派生类的窗口
	std::wstring m_MainWindowCaption;						//窗口标题
	int m_ClientWidth;										//客户端高度
	int m_ClientHeight;										//视口高度
	bool m_bLocKMouse;										//窗口激活时锁定鼠标

protected:
	bool InitMainWindow();									//主窗口初始化
	bool InitD3D();											//D3D初始化




};

