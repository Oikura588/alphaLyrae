#include "Actor.h"
#include <iostream>

int Actor::IDNum = 1;

Actor::Actor()
{
	//每次调用构造函数，IDNum++
	ID = IDNum;
	IDNum++;

	RootComponent = new SceneComponent();

}

Actor::~Actor()
{
}


void Actor::AddComponent(ActorComponent *InComponent)
{
	RootComponent->AddChildren(InComponent);
}

void Actor::RemoveComponent(int ComponentID)
{
		auto ch = RootComponent->Children.begin();
		std::cout << (*ch)->ID;
		while (ch!= RootComponent->Children.end())
		{
			if ((*ch)->ID == ComponentID) {
				ch = RootComponent->Children.erase(ch);
			}
			else
				++ch;
	}
	
}

void Actor::Tick(float DeltaSeconds)
{
	//Tick，调用Components的Tick
	//初始化Components中的其他组件
	if (RootComponent)
	{
		RootComponent->Tick(DeltaSeconds);

	}

}

void Actor::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
}

void Actor::Render()
{
	//绘制PrimitiveComponent.
	if (RootComponent)
	{
		for (auto com : RootComponent->Children)
		{
			//PrimitiveComponent* tmp = dynamic_cast<PrimitiveComponent*>(com);

			//if (tmp)
			//{
			//	tmp->Draw();
			//}

			com->Draw();
		}

	}
}



void Actor::PrintID()
{
	std::cout << ID << "\n";
}

void Actor::BeginPlay()
{
	//PrintID();

	//初始化RootComponent
	if (RootComponent==nullptr)
	{
		RootComponent = new SceneComponent();
	}
	RootComponent->BeginPlay();




}
