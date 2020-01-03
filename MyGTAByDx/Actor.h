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

	// 先用std::vector管理Component
    std::vector<class ActorComponent*> Components;

	void AddComponent(ActorComponent& InComponent);
	void RemoveComponent(int ComponentID);

	// 管理Actor的Transform
	SceneComponent* RootComponent;


	//*******************ID相关***********************
	// Identifier
    int ID;
	static int IDNum;
	// 输出ID
	void PrintID();



	//******************世界逻辑相关
	// BeginPlay函数，游戏世界开始时调用
    virtual void BeginPlay();

    // Tick函数, 游戏逻辑更新
    virtual void Tick(float DeltaSeconds);



};
