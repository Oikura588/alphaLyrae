#pragma once
#include "D3DApp.h"
#include <DirectXMath.h>
#include "LightType.h"
#include "Material.h"
#include "Geometry.h"
// 顶点. pos, color
//struct VertexPosColor
//{
//	DirectX::XMFLOAT3 pos;
//	DirectX::XMFLOAT4 color;
//
//	static const D3D11_INPUT_ELEMENT_DESC inputDesc[2];
//};
//
//struct MVP
//{
//	DirectX::XMMATRIX world;
//	DirectX::XMMATRIX view;
//	DirectX::XMMATRIX proj;
//
//};


struct VSConstantBuffer {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
	DirectX::XMMATRIX worldInvTranspose;

};

struct PSConstantBuffer
{
	DirectionalLight dirLight;
	Material material;
	DirectX::XMFLOAT4 eyePos;

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
	//ComPtr<ID3D11Buffer>			m_pVertexBuffer;
	ComPtr<ID3D11PixelShader>		m_pPixelShader;

	//int								m_IndexCount;
	//似乎不用
	ComPtr<ID3D11InputLayout>		m_pPixelInputLayout;
	ComPtr<ID3D11Buffer>			m_pPixelBuffer;

	//ComPtr<ID3D11Buffer>			m_pIndexBuffer;

	//常量缓冲区
	ComPtr<ID3D11Buffer>			m_pConstantBuffer;

	ComPtr<ID3D11Buffer> m_pConstantBuffers[2];     // 常量缓冲区

	VSConstantBuffer				m_VSConstantBuffer;
	PSConstantBuffer				m_PSConstantBuffer;

	DirectionalLight				m_DirLight;

	ComPtr<ID3D11RasterizerState> m_pRSWireframe;   // 光栅化状态: 线框模式
	bool m_IsWireframeMode;                         // 当前是否为线框模式

	/*template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);*/

	//ComPtr<ID3D11ShaderResourceView> m_pWoodCrate;			    // 木盒纹理
	//ComPtr<ID3D11SamplerState> m_pSamplerState;				    // 采样器状态

	class CubeShape* Cube;
};

