#include "SceneComponent.h"

SceneComponent::SceneComponent()
    : ActorComponent(),
	WorldTransform()
{
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::BeginPlay()
{
	PrintTransform();
}

