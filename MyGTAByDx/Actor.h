/*=============================================================================
	Actor.h: Base Class which can place in World
=============================================================================*/
#pragma once
#include "Object.h"
#include "SceneComponent.h"
#include <vector>


class Actor : public Object {
public:
	Actor();
    virtual ~Actor();

	// Owner
	Actor* Owner;
	void SetOwner(Actor* NewOwner);
	inline Actor* GetOwner() { return Owner; }


	// Children
    std::vector<Actor*> Children;

	void AddChildren(Actor& ChildActor);
    void RemoveChildren(int ChildrenActorI);

	// ����std::vector����Component
    std::vector<class ActorComponent*> Components;

	void AddComponent(ActorComponent& InComponent);
	void RemoveComponent(int ComponentID);

	// ����Actor��Transform
	SceneComponent* RootComponent;


	//*******************ID���***********************
	// Identifier
    int ID;
	static int IDNum;
	// ���ID
	void PrintID();



	//******************�����߼����
	// BeginPlay��������Ϸ���翪ʼʱ����
    virtual void BeginPlay();

    // Tick����, ��Ϸ�߼�����
    virtual void Tick(float DeltaSeconds);



};
