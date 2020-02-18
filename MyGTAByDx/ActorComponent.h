/*=============================================================================
	ActorComponent.h: Base Class which can add to different types of Actor
=============================================================================*/
#pragma once
#include <vector>

class ActorComponent {
public:
    ActorComponent();
    virtual ~ActorComponent();


	int ID;
	static int IDNum;

	void PrintID();

	virtual void BeginPlay();
	virtual void Tick(float dt);


	// Owner
	bool bHasOwner;
	ActorComponent* Owner;
	void SetOwner(ActorComponent* NewOwner);
	inline ActorComponent* GetOwner() { return Owner; }

	// Children
    std::vector<ActorComponent*> Children;

	void AddChildren(ActorComponent* ChildActor);
    void RemoveChildren(int ChildrenActorI);


};