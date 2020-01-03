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

	HINSTANCE	AppInst() const;		//��ȡAppInstance
	HWND		MainWnd() const;		//��ȡ�����ھ��
	float		AspectRatio() const;	//��ȡ��Ļ��߱�

	int Run();							//������ѭ��


	virtual bool Init();				//��ʼ�����ں�D3D����



};

