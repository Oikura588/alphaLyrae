#include "Actor.h"
#include <iostream>

int Actor::IDNum = 1;

Actor::Actor()
{
	//ÿ�ε��ù��캯����IDNum++
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
	//Tick������Components��Tick
	//��ʼ��Components�е��������
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
	//����PrimitiveComponent.
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

	//��ʼ��RootComponent
	if (RootComponent==nullptr)
	{
		RootComponent = new SceneComponent();
	}
	RootComponent->BeginPlay();




}
