/*=============================================================================
	ActorComponent.h: Base Class which can add to different types of Actor
=============================================================================*/
#pragma once

class ActorComponent {
public:
    ActorComponent();
    virtual ~ActorComponent();


	int ID;
	static int IDNum;

	void PrintID();

	virtual void BeginPlay();
};