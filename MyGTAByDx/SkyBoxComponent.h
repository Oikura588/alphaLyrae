#pragma once
#include "PrimitiveComponent.h"
#include "BasicShape.h"

class SkyBoxComponent : public PrimitiveComponent {
public:
	SkyBoxComponent();
	virtual ~SkyBoxComponent() {};

	// 渲染相关
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext); //初始化渲染资源	
	virtual void Draw();						//将资源绑定到pipeline
	virtual void Update(float dt);				//更新资源


	// 设置纹理（可运行时）
	void SetTexture(ID3D11ShaderResourceView* pTexture = nullptr);

	// 设置Material

	void SetMaterial();


	// 每帧更新，把相机的矩阵传给SkyBox
	void SetViewMAndProM(const DirectX::XMMATRIX& ViewM,const DirectX::XMMATRIX& ProM) {
		m_ViewM = ViewM;
		m_ProM = ProM;
	}
protected:
	//形状网格数据
	SphereShapeWithPos* m_pShape;


	//ViewProj矩阵
	DirectX::XMMATRIX m_ViewM;
	DirectX::XMMATRIX m_ProM;




};
