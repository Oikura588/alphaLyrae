#ifndef D3DUTIL_H
#define D3DUTIL_H


#include <assert.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>


#pragma comment(lib, "D3DCompiler.lib")

// 安全COM组件释放宏
#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

//着色器编译相关

HRESULT CreateShaderFromFile(
	const WCHAR* csoFileNameInOut,
	const WCHAR* hlslFileName,
	LPCSTR entryPoint,
	LPCSTR shaderModel,
	ID3DBlob** ppBlobOut);


#endif