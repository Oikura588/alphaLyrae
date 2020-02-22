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

	//方便Rnder的逻辑判断，实际只有需要渲染的才实现绘制逻辑。
	virtual void Draw();
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