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
		//转换成功，即父组件也是场景组件
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
//
//void SceneComponent::BeginPlay()
//{
//	using namespace DirectX;
//	ActorComponent::BeginPlay();
//	//PrintTransform();
//	//LocalMatrix = XMMatrixTranslation(10.f, 0.f, 0.f);
//		//初始化Components中的其他组件
//	for (auto com : Children) {
//		std::cout << ID << "'s Components:";
//		com->BeginPlay();
//	}
//
//}
//
//void SceneComponent::Tick(float dt)
//{
//	for (auto com : Children) {
//		//std::cout << ID << "'s Components:";
//		com->Tick(dt);
//	}
//
//}


