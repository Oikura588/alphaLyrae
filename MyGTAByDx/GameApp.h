#pragma once
#include "D3DApp.h"
#include <DirectXMath.h>
#include "LightType.h"
#include "Material.h"
#include "Geometry.h"
// ����. pos, color
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


	//Shader��ʼ��
	bool InitShader();

	//��ʼ����Ⱦ��Դ
	bool InitResource();


	ComPtr<ID3D11VertexShader>		m_pVertexShader;
	ComPtr<ID3D11InputLayout>		m_pVertexInputLayout;
	//ComPtr<ID3D11Buffer>			m_pVertexBuffer;
	ComPtr<ID3D11PixelShader>		m_pPixelShader;

	//int								m_IndexCount;
	//�ƺ�����
	ComPtr<ID3D11InputLayout>		m_pPixelInputLayout;
	ComPtr<ID3D11Buffer>			m_pPixelBuffer;

	//ComPtr<ID3D11Buffer>			m_pIndexBuffer;

	//����������
	ComPtr<ID3D11Buffer>			m_pConstantBuffer;

	ComPtr<ID3D11Buffer> m_pConstantBuffers[2];     // ����������

	VSConstantBuffer				m_VSConstantBuffer;
	PSConstantBuffer				m_PSConstantBuffer;

	DirectionalLight				m_DirLight;

	ComPtr<ID3D11RasterizerState> m_pRSWireframe;   // ��դ��״̬: �߿�ģʽ
	bool m_IsWireframeMode;                         // ��ǰ�Ƿ�Ϊ�߿�ģʽ

	/*template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);*/

	//ComPtr<ID3D11ShaderResourceView> m_pWoodCrate;			    // ľ������
	//ComPtr<ID3D11SamplerState> m_pSamplerState;				    // ������״̬

	class CubeShape* Cube;
};

