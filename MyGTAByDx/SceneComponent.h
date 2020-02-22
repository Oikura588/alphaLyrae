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

	// ÿ��SceneComponent��һ��WorldTransform������и�����Ҹ����ΪSceneComponent�Ļ������ڸ������WorldTransform�����Լ���WorldTransform

	// ���ظ��������orNULL
	SceneComponent* GetFatherSceneComponent();
	SceneComponent* FatherSceneComponent;
	Transform WorldTransform;  
	DirectX::XMMATRIX WorldMatrix;
	// ÿ��SceneComponent��һ��LocalTransform
	Transform LocalTransform;
	DirectX::XMMATRIX LocalMatrix;

	// ����Transform����LocalMatrix
	void SetLocalMatrix();


	//  ���������ϵ�����������
	void UpdateWorldM();




	// ����WorldMatrix
	DirectX::XMMATRIX& GetWorldMatrix() {
		
		return WorldMatrix;
	}


	// ��������λ��

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