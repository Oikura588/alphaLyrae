#include "MeshComponent.h"

MeshComponent::MeshComponent()
	:m_pShape(nullptr)
{
}

MeshComponent::~MeshComponent()
{
}
//
//void MeshComponent::BeginPlay()
//{
//	PrimitiveComponent::BeginPlay();
//
//}
//
//void MeshComponent::Tick(float dt)
//{
//	PrimitiveComponent::Tick(dt);
//}

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

		using namespace DirectX;

		//旋转
		static float phi = 0.001f, theta = 0.0f;
		//phi += 0.0001f, theta += 0.00015f;
		XMMATRIX W = XMMatrixRotationX(phi);

		//WorldMatrix = XMMatrixTranspose(W);
		LocalMatrix =  W*LocalMatrix;
		//LocalMatrix =  W;
		m_pShape->m_WorldMatrix =XMMatrixTranspose( GetWorldMatrix());
	}
}

void MeshComponent::SetShape(BasicShape* shape)
{
	m_pShape = shape;
}
