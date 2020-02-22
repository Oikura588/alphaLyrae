#pragma once
#include "Actor.h"
class Car :
	public Actor
{
public:
	Car();
	~Car();

	virtual void BeginPlay();

	// Tick函数, 游戏逻辑更新
	virtual void Tick(float DeltaSeconds);


	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

	// 移动相关
	virtual void MoveForward(float v);
	virtual void MoveRight(float v);

private:
	//车身
	MeshComponent* CarBody;

	//四个轮子
	SceneComponent* LFWheelAxis;
	MeshComponent* LFWheel;
	SceneComponent* RFWheelAxis;
	MeshComponent* RFWheel;
	SceneComponent* LBWheelAxis;
	MeshComponent* LBWheel;
	SceneComponent* RBWheelAxis;
	MeshComponent* RBWheel;


	// 四个轮子前进/后退的转动

	void WheelMoveForwardRotate(float v);


	// 前面两个轮子左右移动的转动
	void WheelMoveRightRotate(float v);



};

