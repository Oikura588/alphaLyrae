#ifndef D3DUTIL_H
#define D3DUTIL_H


#include <assert.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include<string>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#pragma comment(lib, "D3DCompiler.lib")

// ��ȫCOM����ͷź�
#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

//��ɫ���������

HRESULT CreateShaderFromFile(
	const WCHAR* csoFileNameInOut,
	const WCHAR* hlslFileName,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut);


//ʹ��ģ�������������
template<class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;


#endif