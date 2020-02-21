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

	// Tick����, ��Ϸ�߼�����
	virtual void Tick(float DeltaSeconds);


	// ��Ⱦ���

	// ����ʵ�֣�������Ҫ��Ⱦ�������������Ⱦ
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);


protected:
	//�����
	SkyBoxComponent*	SkyComponent;
	Camera* FollowCamera;

};

