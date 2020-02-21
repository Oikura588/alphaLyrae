#pragma once
#include"Actor.h"


class Camera;
class SkyBoxComponent;
class SkyBox:public Actor
{
public:
	SkyBox();
	SkyBox(Camera* FollowCamera);
	virtual ~SkyBox() {};




	void SetFollowCamera(Camera* FollowCamera);

	virtual void BeginPlay();

	// Tick函数, 游戏逻辑更新
	virtual void Tick(float DeltaSeconds);


	// 渲染相关

	// 子类实现，调用需要渲染的组件来进行渲染
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);


protected:
	//天空球
	SkyBoxComponent*	SkyComponent;
	Camera* FollowCamera;

};

