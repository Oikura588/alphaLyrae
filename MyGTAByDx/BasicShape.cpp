#include "BasicShape.h"
#include "WICTextureLoader.h"
#include "DXTrace.h"
#include "VertexTypes.h"

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

void BasicShape::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	//�����
	//���ò�����
	SetTexture(m_pDefaultTexture.Get());
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
	m_WorldMatrix = DirectX::XMMatrixIdentity();

	
}

void BasicShape::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	using namespace DirectX;

	if (pTexture)
	{
		m_pDefaultTexture = pTexture;
	}
	else {
		
		HR(CreateWICTextureFromFile(m_pd3dDevice, L"Texture\\Default.png", nullptr, m_pDefaultTexture.GetAddressOf()));

	}
	//��������������°󶨣�
	//BasicShape::InitResource(m_pd3dDevice, m_pd3dDeviceContext);


	
}

void BasicShape::Draw()
{

	using namespace DirectX;

	UpdateMesh(m_MeshData);



	//��ȡ�Ѿ��󶨵������ϵĳ��������������и���
	ComPtr<ID3D11Buffer> cBuffer = nullptr;
	m_pd3dDeviceContext->VSGetConstantBuffers(0, 1, &cBuffer);
	ConstantBufferForScene cBForScene;

	cBForScene.world = m_WorldMatrix;
	cBForScene.worldInvTranspose = XMMatrixInverse(nullptr, cBForScene.world);

	//// ...

	// ���³���������
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dDeviceContext->Map(cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForScene), &cBForScene, sizeof(ConstantBufferForScene));
	m_pd3dDeviceContext->Unmap(cBuffer.Get(), 0);

	//PS�׶���������Ͳ�����


	m_pd3dDeviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	m_pd3dDeviceContext->PSSetShaderResources(0, 1, m_pDefaultTexture.GetAddressOf());

	m_pd3dDeviceContext->DrawIndexed(m_IndexCount, 0, 0);
}

void BasicShape::Update(float dt)
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
	this->width = 2;
	this->height = 2;
	this->depth = 2;

}

CubeShape::CubeShape(float width, float height, float depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}

CubeShape::~CubeShape()
{

}

void CubeShape::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	using namespace DirectX;
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;
	
	//�ɱ仯��
	//��������
	m_MeshData = Geometry::CreateCube(width,height,depth);
	//UpdateMesh(m_MeshData);

	//����Ĭ������
	//HR(CreateWICTextureFromFile(pd3dDevice, L"Texture\\Default.png", nullptr, m_pDefaultTexture.GetAddressOf()));

	BasicShape::InitResource(pd3dDevice, pd3dDeviceContext);

}

CylinderShape::CylinderShape()
{
	this->radius = 2;
	this->height = 2;
	this->slices = 20;
}

CylinderShape::CylinderShape(float radius, float height , UINT slices )
{
	this->radius = radius;
	this->height = height;
	this->slices = slices;
}

CylinderShape::~CylinderShape()
{
}

void CylinderShape::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	using namespace DirectX;
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;

	//�ɱ仯��
	//��������
	m_MeshData = Geometry::CreateCylinder(radius,height,slices);
	//UpdateMesh(m_MeshData);

	//����Ĭ������
	//HR(CreateWICTextureFromFile(pd3dDevice, L"Texture\\Default.png", nullptr, m_pDefaultTexture.GetAddressOf()));

	BasicShape::InitResource(pd3dDevice, pd3dDeviceContext);
}
