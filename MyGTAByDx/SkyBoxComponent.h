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
	void SetViewM(const DirectX::XMMATRIX& ViewM) {
		m_ViewM = ViewM;
	}

	// ������������
	void SetProM(const DirectX::XMMATRIX& ProjM) {
		m_ProM = ProjM;
	}
protected:
	//��״��������
	SphereShapeWithPos* m_pShape;


	//ViewProj����
	DirectX::XMMATRIX m_ViewM;
	DirectX::XMMATRIX m_ProM;




};
