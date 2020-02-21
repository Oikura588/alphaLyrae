#pragma once
/************************************************************************/
/* ������״,����������Ϣ�Ͷ�����Ϣ                                      */
/************************************************************************/
#include <vector>
#include "DXUtil.h"
#include "Geometry.h"

class BasicShapeWithPosNormalTex
{
public:
	BasicShapeWithPosNormalTex();
	virtual ~BasicShapeWithPosNormalTex();

	//���������������Դ
	virtual void InitResource(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pd3dDeviceContext);

	//��������

	void SetTexture(ID3D11ShaderResourceView* pTexture=nullptr);

	//Drawʱ����
	virtual void Draw();
	//Updateʱ����
	virtual void Update(float dt);


	//��������
	Geometry::MeshData<VertexPosNormalTex>	m_MeshData;
	ComPtr<ID3D11ShaderResourceView>		m_pDefaultTexture;			    // Ĭ������
	//ComPtr<ID3D11SamplerState>				m_pSamplerState;			// Ĭ�ϲ�����
	DirectX::XMMATRIX						m_WorldMatrix;					// �������
	ID3D11Device*							m_pd3dDevice;
	ID3D11DeviceContext*					m_pd3dDeviceContext;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;									// ���㻺����
	ComPtr<ID3D11Buffer> m_pIndexBuffer;									// ����������
	UINT m_IndexCount;														// ������Ŀ 
	UINT m_VertexStride;													// �����ֽڴ�С


	template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);
};


class CubeShape :public BasicShapeWithPosNormalTex {
public:
	CubeShape();
	CubeShape(float width , float height , float depth );

	~CubeShape();
	

	//���������������Դ
	void InitResource(ID3D11Device* pd3dDevice,  ID3D11DeviceContext* pd3dDeviceContext);

protected:

	float width;
	float height;
	float depth;


};


class CylinderShape : public BasicShapeWithPosNormalTex {
public:
	CylinderShape();
	CylinderShape(float radius , float height , UINT );
	~CylinderShape();

	//�������������
	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

protected:

	float radius;
	float height;
	UINT slices;

};


class SphereShapeWithPos 
{

public:
	SphereShapeWithPos();
	SphereShapeWithPos(float radius, UINT levels , UINT slices);
	~SphereShapeWithPos();



	//�������������
	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

	//BasicShape���Draw�ǰ�GOPipeLineд�ģ�������д
	virtual void Draw() ;



	DirectX::XMMATRIX		m_ViewMatrix;					// �۲�
	DirectX::XMMATRIX		m_ProjMatrix;					// ͶӰ
	DirectX::XMMATRIX		m_WorldMatrix;					// �������



	void SetTexture(ID3D11ShaderResourceView* pTexture);

protected:
	float radius ;
	UINT levels;
	UINT slices;


	//��������
	Geometry::MeshData<VertexPos>			m_MeshData;
	ComPtr<ID3D11ShaderResourceView>		m_pDefaultTexture;			    // Ĭ������
	//ComPtr<ID3D11SamplerState>			m_pSamplerState;			// Ĭ�ϲ�����
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;									// ���㻺����
	ComPtr<ID3D11Buffer> m_pIndexBuffer;									// ����������
	UINT m_IndexCount;														// ������Ŀ 
	UINT m_VertexStride;													// �����ֽڴ�С


	template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);
};

