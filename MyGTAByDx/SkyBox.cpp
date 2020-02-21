#include "SkyBox.h"
#include "TextureLoader.h"
#include "BasicShape.h"
#include "SkyBoxComponent.h"
#include "Camera.h"
SkyBox::SkyBox()
{

	SkyComponent = new SkyBoxComponent();
}

SkyBox::SkyBox(Camera* FollowCamera)
{
	this->FollowCamera = FollowCamera;
}

void SkyBox::SetFollowCamera(Camera* FollowCamera)
{
	this->FollowCamera = FollowCamera;
}

void SkyBox::BeginPlay()
{
	Actor::BeginPlay();

}

void SkyBox::Tick(float DeltaSeconds)
{
	Actor::Tick(DeltaSeconds);

	if (SkyComponent&&FollowCamera)
	{
		SkyComponent->SetViewMAndProM(FollowCamera->GetViewM(), FollowCamera->GetProjM());
	}

}

void SkyBox::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	using namespace DirectX;
	
	AddComponent(SkyComponent);

	SkyComponent->InitResource(pd3dDevice, pd3dDeviceContext);



	//delete(m_TextureLoader);
	//m_TextureLoader = nullptr;
}

