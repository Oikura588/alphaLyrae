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
	SetFollowCamera(FollowCamera);
}

void SkyBox::SetFollowCamera(Camera* FollowCamera)
{
	this->FollowCamera = FollowCamera;
	SkyComponent->SetProM(FollowCamera->GetProjM());
}

void SkyBox::BeginPlay()
{
	Actor::BeginPlay();

}

void SkyBox::Tick(float DeltaSeconds)
{


	if (SkyComponent&&FollowCamera)
	{
		//SkyComponent->LocalMatrix = DirectX::XMMatrixTranslation(FollowCamera->GetPosition().x, FollowCamera->GetPosition().y, FollowCamera->GetPosition().z);
		
		//SkyComponent->SetViewMAndProM(FollowCamera->GetViewM(), FollowCamera->GetProjM());
		//SkyComponent->LocalMatrix = DirectX::XMMatrixTranslation(FollowCamera->GetPosition().x, FollowCamera->GetPosition().y, FollowCamera->GetPosition().z);
		//RootComponent->LocalMatrix= DirectX::XMMatrixTranslation(FollowCamera->GetPosition().x, FollowCamera->GetPosition().y, FollowCamera->GetPosition().z);
		//RootComponent->LocalMatrix = RootComponent->LocalMatrix * DirectX::XMMatrixRotationX(0.001f);
		SkyComponent->LocalMatrix= DirectX::XMMatrixTranslation(FollowCamera->GetPosition().x, FollowCamera->GetPosition().y, FollowCamera->GetPosition().z);

		SkyComponent->SetViewM(FollowCamera->GetViewM());

	}
	RootComponent->Tick(DeltaSeconds);



}

void SkyBox::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	using namespace DirectX;
	
	AddComponent(SkyComponent);

	SkyComponent->InitResource(pd3dDevice, pd3dDeviceContext);

	//SkyComponent->LocalMatrix = DirectX::XMMatrixTranslation(FollowCamera->GetPosition().x, FollowCamera->GetPosition().y, FollowCamera->GetPosition().z);

	//SkyComponent->SetViewMAndProM(FollowCamera->GetViewM(), FollowCamera->GetProjM());


	//delete(m_TextureLoader);
	//m_TextureLoader = nullptr;
}

