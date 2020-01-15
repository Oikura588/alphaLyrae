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
	// �ͷž���Դ
	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();

	// ���ö��㻺��������
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)meshData.vertexVector.size() * sizeof(VertexType);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// �½����㻺����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = meshData.vertexVector.data();
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

	// ����װ��׶εĶ��㻺��������
	UINT stride = sizeof(VertexType); // ��Խ�ֽ���
	UINT offset = 0;                            // ��ʼƫ����

	m_pd3dDeviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	// ������������������
	m_IndexCount = (UINT)meshData.indexVector.size();
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = m_IndexCount * sizeof(WORD);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	// �½�����������
	InitData.pSysMem = meshData.indexVector.data();
	HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
	// ����װ��׶ε���������������
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
	//��������
	m_MeshData = Geometry::CreateCube();
	UpdateMesh(m_MeshData);

	//��������
	HR(CreateDDSTextureFromFile(pd3dDevice, L"Texture\\WoodCrate.dds", nullptr, m_pDefaultTexture.GetAddressOf()));
	//���ò�����
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


	//���ó�ʼ��world����
	m_WorldMatrix = XMMatrixIdentity();

	//PS�׶���������Ͳ�����


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
