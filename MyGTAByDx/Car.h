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
	MeshComponent* LFWheel;
	MeshComponent* RFWheel;
	MeshComponent* LBWheel;
	MeshComponent* RBWheel;


};

