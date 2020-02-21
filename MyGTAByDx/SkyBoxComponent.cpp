#include "SkyBoxComponent.h"
#include "TextureLoader.h"

SkyBoxComponent::SkyBoxComponent()
	:m_ViewM()
	,m_ProM()
{
	m_pShape = nullptr;
}

void SkyBoxComponent::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;
	//���û��������״��Ĭ��Ϊcube
	if (m_pShape == nullptr)
	{
		m_pShape = new SphereShapeWithPos();
		TextureLoader* m_TextureLoader = new TextureLoader();
		m_TextureLoader->Init(pd3dDevice, pd3dDeviceContext);



		m_pShape->SetTexture(m_TextureLoader->LoadTextureCube("daylight.jpg").Get());

		delete(m_TextureLoader);
		m_TextureLoader = nullptr;
	}

	// ��Shape��ʼ����Դ
	m_pShape->InitResource(m_pd3dDevice, m_pd3dDeviceContext);
}

void SkyBoxComponent::Draw()
{
	if (m_pShape == nullptr)
	{
		//˵��û�г�ʼ������ִ�л���
	}
	else {
		m_pShape->Draw();
	}
}

void SkyBoxComponent::Update(float dt)
{
	if (m_pShape == nullptr)
	{
		//˵��û�г�ʼ������ִ�и���
	}
	else {
		//���¾��ǰѾ��󴫸�Shape,Shapeÿ��Drawʱ����¸�����
		//LocalMatrix =  W;
		m_pShape->m_WorldMatrix =DirectX::XMMatrixTranspose(GetWorldMatrix());
		m_pShape->m_ViewMatrix = DirectX::XMMatrixTranspose(m_ViewM);
		m_pShape->m_ProjMatrix = DirectX::XMMatrixTranspose(m_ProM);


	}
}

void SkyBoxComponent::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pShape->SetTexture(pTexture);

}

void SkyBoxComponent::SetMaterial()
{
}
