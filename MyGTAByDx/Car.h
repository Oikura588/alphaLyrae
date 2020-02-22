#pragma once
#include "Actor.h"
class Car :
	public Actor
{
public:
	Car();
	~Car();

	virtual void BeginPlay();

	// Tick����, ��Ϸ�߼�����
	virtual void Tick(float DeltaSeconds);


	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

	// �ƶ����
	virtual void MoveForward(float v);
	virtual void MoveRight(float v);

private:
	//����
	MeshComponent* CarBody;

	//�ĸ�����
	SceneComponent* LFWheelAxis;
	MeshComponent* LFWheel;
	SceneComponent* RFWheelAxis;
	MeshComponent* RFWheel;
	SceneComponent* LBWheelAxis;
	MeshComponent* LBWheel;
	SceneComponent* RBWheelAxis;
	MeshComponent* RBWheel;


	// �ĸ�����ǰ��/���˵�ת��

	void WheelMoveForwardRotate(float v);


	// ǰ���������������ƶ���ת��
	void WheelMoveRightRotate(float v);



};

