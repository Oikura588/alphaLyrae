#pragma once
#include "PrimitiveComponent.h"
#include "BasicShape.h"

class SkyBoxComponent : public PrimitiveComponent {
public:
	SkyBoxComponent();
	virtual ~SkyBoxComponent() {};

	// ��Ⱦ���
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext); //��ʼ����Ⱦ��Դ	
	virtual void Draw();						//����Դ�󶨵�pipeline
	virtual void Update(float dt);				//������Դ


	// ��������������ʱ��
	void SetTexture(ID3D11ShaderResourceView* pTexture = nullptr);

	// ����Material

	void SetMaterial();


	// ÿ֡���£�������ľ��󴫸�SkyBox
	void SetViewMAndProM(const DirectX::XMMATRIX& ViewM,const DirectX::XMMATRIX& ProM) {
		m_ViewM = ViewM;
		m_ProM = ProM;
	}
protected:
	//��״��������
	SphereShapeWithPos* m_pShape;


	//ViewProj����
	DirectX::XMMATRIX m_ViewM;
	DirectX::XMMATRIX m_ProM;




};
