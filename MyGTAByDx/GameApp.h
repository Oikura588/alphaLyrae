#pragma once
#include "D3DApp.h"
#include <DirectXMath.h>

// 顶点. pos, color
struct VertexPosColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;

	static const D3D11_INPUT_ELEMENT_DESC inputDesc[2];
};



class GameApp :
	public D3DApp
{
public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void SetRenderPipeLine();
	void UpdateScene(float dt);
	void DrawScene();


	//Shader初始化
	bool InitShader();

	//初始化渲染资源
	bool InitResource();


	ComPtr<ID3D11VertexShader>		m_pVertexShader;
	ComPtr<ID3D11InputLayout>		m_pVertexInputLayout;
	ComPtr<ID3D11Buffer>			m_pVertexBuffer;
	ComPtr<ID3D11PixelShader>		m_pPixelShader;
	//似乎不用
	ComPtr<ID3D11InputLayout>		m_pPixelInputLayout;
	ComPtr<ID3D11Buffer>			m_pPixelBuffer;

};

