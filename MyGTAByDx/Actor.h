/*=============================================================================
	Actor.h: Base Class which can place in World
=============================================================================*/
#pragma once
#include "Object.h"
#include "SceneComponent.h"
#include "MeshComponent.h"
#include <vector>


class Actor : public Object {
public:
	Actor();
    virtual ~Actor();


	void AddComponent(ActorComponent* InComponent);
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


	// ��Ⱦ���

	// ����ʵ�֣�������Ҫ��Ⱦ�������������Ⱦ
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);
	virtual void Render();





protected:
	


	

};
