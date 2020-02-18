/* MeshComponent is an abstract base for any component that is an instance of a renderable collection of triangles.
 *
 * @see StaticMeshComponent
 * @see SkeletalMeshComponent(��û��)
 */

#pragma once
#include "PrimitiveComponent.h"
#include "BasicShape.h"


class MeshComponent : public PrimitiveComponent {
public:
    MeshComponent();
    virtual ~MeshComponent();


	// ��Ϸ�߼����
	//virtual void BeginPlay() override;
	//virtual void Tick(float dt)      override;

	// ��Ⱦ���
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext); //��ʼ����Ⱦ��Դ	
	virtual void Draw();						//����Դ�󶨵�pipeline
	virtual void Update(float dt);				//������Դ


	// ������״
	void SetShape(BasicShape* shape);


	// ��������������ʱ��
	void SetTexture(ID3D11ShaderResourceView* pTexture = nullptr);
protected:
	//��״��������
	BasicShape* m_pShape;

};
