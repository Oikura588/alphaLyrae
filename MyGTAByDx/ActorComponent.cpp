#include "ActorComponent.h"
#include <iostream>
int ActorComponent::IDNum = 1;
ActorComponent::ActorComponent()
{

	ID = IDNum;
	IDNum++;
}

ActorComponent::~ActorComponent()
{
}

void ActorComponent::PrintID()
{
	std::cout << ID<<"\n";
}

void ActorComponent::BeginPlay()
{
}
