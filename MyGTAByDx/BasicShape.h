#pragma once
/************************************************************************/
/* 基本形状,包含索引信息和顶点信息                                      */
/************************************************************************/
#include <vector>
#include "DXUtil.h"
#include "Geometry.h"

class BasicShape
{
public:
	BasicShape();
	virtual ~BasicShape();

	//加载纹理、网格等资源
	virtual void InitResource(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pd3dDeviceContext)=0;


	//Draw时调用
	virtual void Draw() = 0;
	//Update时调用
	virtual void Update(float dt) = 0;


	//网格数据
	Geometry::MeshData<VertexPosNormalTex>	m_MeshData;
	ComPtr<ID3D11ShaderResourceView>		m_pDefaultTexture;			    // 默认纹理
	ComPtr<ID3D11SamplerState>				m_pSamplerState;				// 默认采样器
	DirectX::XMMATRIX						m_WorldMatrix;					// 世界矩阵
	ID3D11Device*							m_pd3dDevice;
	ID3D11DeviceContext*					m_pd3dDeviceContext;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;									// 顶点缓冲区
	ComPtr<ID3D11Buffer> m_pIndexBuffer;									// 索引缓冲区
	UINT m_IndexCount;														// 索引数目 
	UINT m_VertexStride;													// 顶点字节大小


	template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);
};


class CubeShape :public BasicShape {
public:
	CubeShape();
	~CubeShape();
	

	//加载纹理、网格等资源
	void InitResource(ID3D11Device* pd3dDevice,  ID3D11DeviceContext* pd3dDeviceContext);
	void Draw();
	void Update(float dt);


};

