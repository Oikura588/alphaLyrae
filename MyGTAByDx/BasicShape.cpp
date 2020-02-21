#include "BasicShape.h"
#include "WICTextureLoader.h"
#include "DXTrace.h"
#include "VertexTypes.h"

BasicShapeWithPosNormalTex::BasicShapeWithPosNormalTex()
	:m_pDefaultTexture(nullptr)
	,m_pVertexBuffer(nullptr)
	,m_pIndexBuffer(nullptr)
	,m_pd3dDevice(nullptr)
	,m_pd3dDeviceContext(nullptr)
	//,m_pSamplerState(nullptr)
{

}

BasicShapeWithPosNormalTex::~BasicShapeWithPosNormalTex()
{

}

void BasicShapeWithPosNormalTex::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;

	//��������
	SetTexture(m_pDefaultTexture.Get());



	//���ó�ʼ��world����
	m_WorldMatrix = DirectX::XMMatrixIdentity();

	
}

void BasicShapeWithPosNormalTex::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	using namespace DirectX;

	if (pTexture)
	{
		m_pDefaultTexture = pTexture;
	}
	else {
		
		HR(CreateWICTextureFromFile(m_pd3dDevice, L"Texture\\Default.png", nullptr, m_pDefaultTexture.GetAddressOf()));

	}


	
}

void BasicShapeWithPosNormalTex::Draw()
{

	// ����������ߵ�Draw
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

	//PS�׶���������

	m_pd3dDeviceContext->PSSetShaderResources(0, 1, m_pDefaultTexture.GetAddressOf());

	m_pd3dDeviceContext->DrawIndexed(m_IndexCount, 0, 0);
}

void BasicShapeWithPosNormalTex::Update(float dt)
{
}


template<class VertexType>
bool BasicShapeWithPosNormalTex::UpdateMesh(const Geometry::MeshData<VertexType>& meshData)
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



CubeShape::CubeShape():BasicShapeWithPosNormalTex()
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

	BasicShapeWithPosNormalTex::InitResource(pd3dDevice, pd3dDeviceContext);

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

	BasicShapeWithPosNormalTex::InitResource(pd3dDevice, pd3dDeviceContext);

}
















SphereShapeWithPos::SphereShapeWithPos()
{
	this->radius = 1.0;
	this->levels = 20;
	this->slices = 20;
}

SphereShapeWithPos::SphereShapeWithPos(float radius, UINT levels, UINT slices)
{
	this->radius = radius;
	this->levels = levels;
	this->slices = slices;
}

SphereShapeWithPos::~SphereShapeWithPos()
{
}







void SphereShapeWithPos::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	using namespace DirectX;
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;

	//�ɱ仯��
	//��������
	m_MeshData = Geometry::CreateSphere<VertexPos>(radius,levels, slices);

	//BasicShapeWithPosNormalTex::InitResource(pd3dDevice, pd3dDeviceContext);


	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;

	//��������
	SetTexture(m_pDefaultTexture.Get());



	//���ó�ʼ��world����
	m_WorldMatrix = DirectX::XMMatrixIdentity();
}

void SphereShapeWithPos::Draw()
{
	// ����������ߵ�Draw
	using namespace DirectX;

	UpdateMesh(m_MeshData);

	//��ȡ�Ѿ��󶨵������ϵĳ��������������и���
	ComPtr<ID3D11Buffer> cBuffer = nullptr;
	m_pd3dDeviceContext->VSGetConstantBuffers(0, 1, &cBuffer);
	ConstantBufferMVP cBForMVP;

	cBForMVP.mvp = DirectX::XMMatrixTranspose(m_WorldMatrix* m_ViewMatrix*m_ProjMatrix);

	// ���³���������
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dDeviceContext->Map(cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferMVP), &cBForMVP, sizeof(ConstantBufferMVP));
	m_pd3dDeviceContext->Unmap(cBuffer.Get(), 0);

	//PS�׶���������

	m_pd3dDeviceContext->PSSetShaderResources(0, 1, m_pDefaultTexture.GetAddressOf());
	m_pd3dDeviceContext->DrawIndexed(m_IndexCount, 0, 0);
}

void SphereShapeWithPos::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	using namespace DirectX;

	if (pTexture)
	{
		m_pDefaultTexture = pTexture;
	}
	else {

		HR(CreateWICTextureFromFile(m_pd3dDevice, L"Texture\\Default.png", nullptr, m_pDefaultTexture.GetAddressOf()));

	}

}

template<class VertexType>
inline bool SphereShapeWithPos::UpdateMesh(const Geometry::MeshData<VertexType>& meshData)
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
