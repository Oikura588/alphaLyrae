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


	// 渲染相关

	// 子类实现，调用需要渲染的组件来进行渲染
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);
	virtual void Render();





protected:
	


	

};
