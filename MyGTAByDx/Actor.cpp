#include "Actor.h"
#include <iostream>
int Actor::IDNum = 1;

Actor::Actor()
	: Children(0)
	, Components(0)
	, Owner(nullptr)
	, RootComponent(nullptr)
{
	//ÿ�ε��ù��캯����IDNum++
	ID = IDNum;
	IDNum++;
	RootComponent = new SceneComponent;


}

Actor::~Actor()
{
}

void Actor::SetOwner(Actor * NewOwner)
{
	if (Owner == nullptr) {
		Owner = NewOwner;
	}
	else if (NewOwner == nullptr) {
		Owner = nullptr;
	}
	else if (NewOwner->ID!=Owner->ID)
	{
		Owner->RemoveChildren(ID);
		Owner = NewOwner;
		Owner->AddChildren(*this);
	}

	if (Owner)
	{
		//std::cout << Owner->ID<<"\n";

	}
}

void Actor::AddChildren(Actor& ChildActor)
{
	Children.push_back(&ChildActor);
}

void Actor::RemoveChildren(int ChildrenActorID)
{
	auto ch = Children.begin();
	std::cout << (*ch)->ID;
	while (ch!=Children.end())
	{
		if ((*ch)->ID == ChildrenActorID) {
			ch = Children.erase(ch);
		}
		else
			++ch;
	}
}

void Actor::AddComponent(ActorComponent & InComponent)
{
	Components.push_back(&InComponent);
}

void Actor::RemoveComponent(int ComponentID)
{
	auto com = Components.begin();
	
}

void Actor::Tick(float DeltaSeconds)
{
	//Tick
}

void Actor::PrintID()
{
	std::cout << ID << "\n";
}

void Actor::BeginPlay()
{
	PrintID();

	//��ʼ��RootComponent
	RootComponent->BeginPlay();


	//��ʼ��Components�е��������
	for (auto com : Components) {
		std::cout << ID << "'s Components:";
		com->BeginPlay();
	}


	//����Children��BeginPlay
	for (auto ch:Children)
	{
		std::cout << ID << "'s Children:";
		ch->BeginPlay();
	}


}
