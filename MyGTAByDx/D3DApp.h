/*=============================================================================
	D3DApp.h: Base Class which has a Basic Windows
=============================================================================*/
#pragma once
#include<d3d11_1.h>

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



};

