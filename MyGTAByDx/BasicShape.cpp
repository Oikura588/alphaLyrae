#include "BasicShape.h"
#include "DDSTextureLoader.h"
#include "DXTrace.h"


BasicShape::BasicShape()
	:m_pDefaultTexture(nullptr)
	,m_pVertexBuffer(nullptr)
	,m_pIndexBuffer(nullptr)
	,m_pd3dDevice(nullptr)
	,m_pd3dDeviceContext(nullptr)
	,m_pSamplerState(nullptr)
{

}

BasicShape::~BasicShape()
{

}


template<class VertexType>
bool BasicShape::UpdateMesh(const Geometry::MeshData<VertexType>& meshData)
{
	// 释放旧资源
	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();

	// 设置顶点缓冲区描述
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)meshData.vertexVector.size() * sizeof(VertexType);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// 新建顶点缓冲区
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = meshData.vertexVector.data();
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

	// 输入装配阶段的顶点缓冲区设置
	UINT stride = sizeof(VertexType); // 跨越字节数
	UINT offset = 0;                            // 起始偏移量

	m_pd3dDeviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	// 设置索引缓冲区描述
	m_IndexCount = (UINT)meshData.indexVector.size();
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = m_IndexCount * sizeof(WORD);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	// 新建索引缓冲区
	InitData.pSysMem = meshData.indexVector.data();
	HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
	// 输入装配阶段的索引缓冲区设置
	m_pd3dDeviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	return true;
}



CubeShape::CubeShape():BasicShape()
{


}

CubeShape::~CubeShape()
{

}

void CubeShape::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	using namespace DirectX;



	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;
	//设置网格
	m_MeshData = Geometry::CreateCube();
	UpdateMesh(m_MeshData);

	//加载纹理
	HR(CreateDDSTextureFromFile(pd3dDevice, L"Texture\\WoodCrate.dds", nullptr, m_pDefaultTexture.GetAddressOf()));
	//设置采样器
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));


	//设置初始的world矩阵
	m_WorldMatrix = XMMatrixIdentity();

	//PS阶段设置纹理和采样器


	pd3dDeviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	pd3dDeviceContext->PSSetShaderResources(0, 1, m_pDefaultTexture.GetAddressOf());
}

void CubeShape::Update(float dt)
{
	using namespace DirectX;
	static float phi = 0.0f, theta = 0.0f;
	phi += 0.0001f, theta += 0.00015f;
	XMMATRIX W = XMMatrixRotationX(phi) * XMMatrixRotationY(theta);
	m_WorldMatrix = XMMatrixTranspose(W);

}
