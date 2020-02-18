/**
 * PrimitiveComponents are SceneComponents that contain or generate some sort of geometry, generally to be rendered or used as collision data.
 * There are several subclasses for the various types of geometry, but the most common by far are the ShapeComponents (Capsule, Sphere, Box), StaticMeshComponent, and SkeletalMeshComponent.
 * ShapeComponents generate geometry that is used for collision detection but are not rendered, while StaticMeshComponents and SkeletalMeshComponents contain pre-built geometry that is rendered, but can also be used for collision detection.
 */

#pragma once
#include "SceneComponent.h"
#include "DXUtil.h"


class PrimitiveComponent : public SceneComponent {
public:
    PrimitiveComponent();

    virtual ~PrimitiveComponent();

	// ��Ϸ�߼����
	virtual void BeginPlay() ;
	virtual void Tick(float dt)		 ;

	// ��Ⱦ���
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)=0 ; //��ʼ����Ⱦ��Դ	
	virtual void Draw();				//����Դ�󶨵�pipeline
	virtual void Update(float dt);				//������Դ

protected:
	ID3D11Device*						m_pd3dDevice;
	ID3D11DeviceContext*				m_pd3dDeviceContext;
};
