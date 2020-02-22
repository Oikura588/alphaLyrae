#include "ActorComponent.h"
#include <iostream>
int ActorComponent::IDNum = 1;
ActorComponent::ActorComponent()
	:Owner(nullptr)
	,bHasOwner(false)
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
	//调用Children的BeginPlay
	for (auto ch:Children)
	{
		std::cout << ID << "'s Children:";
		ch->BeginPlay();
	}
}

void ActorComponent::Tick(float dt)
{
	//调用Children的Tick
	for (auto ch:Children)
	{
		std::cout << ID << "'s Children:";
		ch->Tick(dt);
	}
}

void ActorComponent::Draw()
{
	for (auto com : Children)
	{
		//PrimitiveComponent* tmp = dynamic_cast<PrimitiveComponent*>(com);

		//if (tmp)
		//{
		//	tmp->Draw();
		//}

		com->Draw();
	}
}




void ActorComponent::SetOwner(ActorComponent* NewOwner)
{
	if (NewOwner == nullptr) {
		Owner = nullptr;
		bHasOwner = false;
	}
	
	else if (Owner == nullptr) {
		Owner = NewOwner;
		bHasOwner = true;

	}

	else if (NewOwner->ID!=Owner->ID)
	{
		Owner->RemoveChildren(ID);
		Owner = NewOwner;
		Owner->AddChildren(this);
		bHasOwner = true;
	}

	if (Owner)
	{
		//std::cout << Owner->ID<<"\n";

	}
}

void ActorComponent::AddChildren(ActorComponent* ChildActor)
{
	Children.push_back(ChildActor);
	ChildActor->SetOwner(this);
}

void ActorComponent::RemoveChildren(int ChildrenActorID)
{
	auto ch = Children.begin();
	std::cout << (*ch)->ID;
	while (ch!=Children.end())
	{
		if ((*ch)->ID == ChildrenActorID) {
			(*ch)->SetOwner(nullptr);
			ch = Children.erase(ch);
		}
		else
			++ch;
	}
}