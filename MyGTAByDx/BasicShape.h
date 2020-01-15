#pragma once
/************************************************************************/
/* ������״,����������Ϣ�Ͷ�����Ϣ                                      */
/************************************************************************/
#include <vector>
#include "DXUtil.h"
#include "Geometry.h"

class BasicShape
{
public:
	BasicShape();
	virtual ~BasicShape();

	//���������������Դ
	virtual void InitResource(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pd3dDeviceContext)=0;

	//Updateʱ����
	virtual void Update(float dt) = 0;


	//��������
	Geometry::MeshData<VertexPosNormalTex>	m_MeshData;
	ComPtr<ID3D11ShaderResourceView>		m_pDefaultTexture;			    //Ĭ������
	ComPtr<ID3D11SamplerState>				m_pSamplerState;				//Ĭ�ϲ�����
	DirectX::XMMATRIX						m_WorldMatrix;					// �������
	ID3D11Device*							m_pd3dDevice;
	ID3D11DeviceContext*					m_pd3dDeviceContext;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;               // ���㻺����
	ComPtr<ID3D11Buffer> m_pIndexBuffer;                // ����������
	UINT m_IndexCount;                                  // ������Ŀ 
	UINT m_VertexStride;                                // �����ֽڴ�С


	template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);
};


class CubeShape :public BasicShape {
public:
	CubeShape();
	~CubeShape();
	

	//���������������Դ
	void InitResource(ID3D11Device* pd3dDevice,  ID3D11DeviceContext* pd3dDeviceContext);

	void Update(float dt);


};

