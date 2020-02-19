#include "MeshComponent.h"

MeshComponent::MeshComponent()
	:m_pShape(nullptr)
{
}

MeshComponent::~MeshComponent()
{
}


void MeshComponent::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;
	//���û��������״��Ĭ��Ϊcube
	if (m_pShape==nullptr)
	{
		m_pShape = new CubeShape();
	}

	// ��Shape��ʼ����Դ
	m_pShape->InitResource(m_pd3dDevice, m_pd3dDeviceContext);
}

void MeshComponent::Draw()
{
	if (m_pShape==nullptr)
	{
		//˵��û�г�ʼ������ִ�л���
	}
	else {
		m_pShape->Draw();
	}
}

void MeshComponent::Update(float dt)
{
	if (m_pShape == nullptr)
	{
		//˵��û�г�ʼ������ִ�и���
	}
	else {

		//LocalMatrix =  W;
		m_pShape->m_WorldMatrix =XMMatrixTranspose( GetWorldMatrix());
	}
}

void MeshComponent::SetShape(BasicShape* shape)
{
	m_pShape = shape;
}

void MeshComponent::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pShape->SetTexture(pTexture);
}


