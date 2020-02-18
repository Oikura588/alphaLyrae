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

	// 游戏逻辑相关
	virtual void BeginPlay() ;
	virtual void Tick(float dt)		 ;

	// 渲染相关
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)=0 ; //初始化渲染资源	
	virtual void Draw();				//将资源绑定到pipeline
	virtual void Update(float dt);				//更新资源

protected:
	ID3D11Device*						m_pd3dDevice;
	ID3D11DeviceContext*				m_pd3dDeviceContext;
};
