#include "PrimitiveComponent.h"

PrimitiveComponent::PrimitiveComponent()
{
}

PrimitiveComponent::~PrimitiveComponent()
{
}

void PrimitiveComponent::BeginPlay()
{
	SceneComponent::BeginPlay();
}

void PrimitiveComponent::Tick(float dt)
{
	SceneComponent::Tick(dt);
	Update(dt);
	//Draw();
}



void PrimitiveComponent::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
}

void PrimitiveComponent::Draw()
{
}

void PrimitiveComponent::Update(float dt)
{
}
