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
	//如果没有设置形状，默认为cube
	if (m_pShape==nullptr)
	{
		m_pShape = new CubeShape();
	}

	// 给Shape初始化资源
	m_pShape->InitResource(m_pd3dDevice, m_pd3dDeviceContext);
}

void MeshComponent::Draw()
{
	if (m_pShape==nullptr)
	{
		//说明没有初始化，不执行绘制
	}
	else {
		m_pShape->Draw();
	}
}

void MeshComponent::Update(float dt)
{
	if (m_pShape == nullptr)
	{
		//说明没有初始化，不执行更新
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


