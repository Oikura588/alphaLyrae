/*=============================================================================
	SceneComponent.h: Base Class which has Transform
=============================================================================*/

#pragma once

#include "ActorComponent.h"
#include <iostream>
#include "DXUtil.h"



// Vector3 3*float
struct Vector3 {
	float X;
	float Y;
	float Z;

	Vector3():X(0.f),Y(0.f),Z(0.f) {
	}
	void Print() {
		std::cout << "X:" << X << ", Y:" << Y << ", Z:" << Z << "\n";
	}
};
// Transform
struct Transform {
	Vector3 Location;

	//Roll Pitch Yaw
	Vector3 Rotation;
	Vector3 Scale;

	Transform():Location(),Rotation(),Scale(){
	}

	void Print() {
		std::cout << "Location:";
		Location.Print();
		std::cout << "Rotation:";
		Rotation.Print();
		std::cout << "Scale:";
		Scale.Print();
	}


};

class SceneComponent : public ActorComponent {
public:
    SceneComponent();
    virtual ~SceneComponent();

	// 每个SceneComponent有一个WorldTransform，如果有父组件且父组件为SceneComponent的话，基于父组件的WorldTransform计算自己的WorldTransform

	// 返回父场景组件orNULL
	SceneComponent* GetFatherSceneComponent();
	SceneComponent* FatherSceneComponent;
	Transform WorldTransform;  
	DirectX::XMMATRIX WorldMatrix;
	// 每个SceneComponent有一个LocalTransform
	Transform LocalTransform;
	DirectX::XMMATRIX LocalMatrix;

	// 根据Transform设置LocalMatrix
	void SetLocalMatrix();


	//  根据组件关系更新世界矩阵
	void UpdateWorldM();




	// 返回WorldMatrix
	DirectX::XMMATRIX& GetWorldMatrix() {
		
		return WorldMatrix;
	}


	// 返回世界位置

	DirectX::XMFLOAT3& GetWorldPosition() {
		
		DirectX::XMFLOAT3 Pos;
		Pos.x = WorldMatrix.r[3].m128_f32[0];
		Pos.y = WorldMatrix.r[3].m128_f32[1];

		Pos.z = WorldMatrix.r[3].m128_f32[2];

		return Pos;

	}


	inline void PrintTransform() { WorldTransform.Print(); };



	//virtual void BeginPlay() override;
	virtual void Tick(float dt);


};