#include "SceneComponent.h"

SceneComponent::SceneComponent()
    : ActorComponent(),
	WorldTransform(),
	LocalTransform(),
	FatherSceneComponent(nullptr)
{
	WorldMatrix = DirectX::XMMatrixIdentity();
	LocalMatrix = DirectX::XMMatrixIdentity();

}

SceneComponent::~SceneComponent()
{
}

SceneComponent* SceneComponent::GetFatherSceneComponent()
{
	if (bHasOwner)
	{
		
		FatherSceneComponent = dynamic_cast<SceneComponent*>(Owner);
		//ת���ɹ����������Ҳ�ǳ������
		if (FatherSceneComponent)
		{
			return FatherSceneComponent;
		}
		return nullptr;
	}
	return nullptr;
}

void SceneComponent::SetLocalMatrix()
{
	using namespace DirectX;
	LocalMatrix =XMMatrixMultiply(XMMatrixTranslation(LocalTransform.Location.X, LocalTransform.Location.Y, LocalTransform.Location.Z),XMMatrixRotationRollPitchYaw(LocalTransform.Rotation.X, LocalTransform.Rotation.Y, LocalTransform.Rotation.Z));
}

void SceneComponent::UpdateWorldM()
{
	//����и����
	if (GetFatherSceneComponent())
	{
		WorldMatrix = DirectX::XMMatrixMultiply(LocalMatrix, FatherSceneComponent->GetWorldMatrix());
	}
	else {
		WorldMatrix = LocalMatrix;
	}
}

void SceneComponent::Tick(float dt)
{
	UpdateWorldM();
	ActorComponent::Tick(dt);
}



