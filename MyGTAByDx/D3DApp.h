/*=============================================================================
	D3DApp.h: Base Class which has a Basic Windows
=============================================================================*/
#pragma once
#include<d3d11_1.h>
#include <wrl/client.h>
#include<string>

#pragma comment(lib,"d3d11.lib")

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	HINSTANCE	AppInst() const;		//��ȡAppInstance
	HWND		MainWnd() const;		//��ȡ�����ھ��
	float		AspectRatio() const;	//��ȡ��Ļ��߱�

	int Run();							//������ѭ��


	virtual bool Init();				//��ʼ�����ں�D3D����

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HINSTANCE	m_hAppInst;				//Ӧ�ó�����
	HWND		m_hMainWnd;				//�����ھ��
	bool		m_bEnable4xMsaa;		//�Ƿ�֧��4�����ز���
	UINT		m_4xMsaaQuality;		//MSAA֧�ֵ������ȼ�

	//ʹ��ģ�������������
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	//D3D11
	ComPtr<ID3D11Device>			m_pd3dDevice;			//D3D�豸
	ComPtr<ID3D11DeviceContext>		m_pd3dDeviceContext;	//D3D������
	ComPtr<IDXGISwapChain>			m_pSwapChain;			//D3D������

	//D3D11.1
	ComPtr<ID3D11Device1>			m_pd3dDevice1;			//D3D11
	ComPtr<ID3D11DeviceContext1>	m_pd3dDeviceContext1;	//
	ComPtr<IDXGISwapChain1>			m_pSwapChain1;			//d3d11.1������


	//ͨ����Դ
	ComPtr<ID3D11Texture2D>			m_pDepthStencilBuffer;	//���ģ�建��
	ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;	//RT View
	ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;	//D/S View


	D3D11_VIEWPORT m_ScreenViewport;                      // �ӿ�


	//������Ĵ���
	std::wstring m_MainWindowCaption;						//���ڱ���
	int m_ClientWidth;										//�ͻ��˸߶�
	int m_ClientHeight;										//�ӿڸ߶�


protected:
	bool InitMainWindow();									//�����ڳ�ʼ��
	bool InitD3D();											//D3D��ʼ��




};

