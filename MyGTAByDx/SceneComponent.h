/*=============================================================================
	SceneComponent.h: Base Class which has Transform
=============================================================================*/


#include "ActorComponent.h"
#include <iostream>

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

	// ÿ��SceneComponent��һ��SceneComponent
	Transform WorldTransform;

	// ���������������е�Transform
	inline Transform& GetWorldTransform() { return WorldTransform; };
	inline void PrintTransform() { WorldTransform.Print(); };


	virtual void BeginPlay() override;

};