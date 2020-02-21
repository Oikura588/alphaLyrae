#pragma once
/************************************************************************/
/* 基本形状,包含索引信息和顶点信息                                      */
/************************************************************************/
#include <vector>
#include "DXUtil.h"
#include "Geometry.h"

class BasicShapeWithPosNormalTex
{
public:
	BasicShapeWithPosNormalTex();
	virtual ~BasicShapeWithPosNormalTex();

	//加载纹理、网格等资源
	virtual void InitResource(ID3D11Device* pd3dDevice,ID3D11DeviceContext* pd3dDeviceContext);

	//设置纹理

	void SetTexture(ID3D11ShaderResourceView* pTexture=nullptr);

	//Draw时调用
	virtual void Draw();
	//Update时调用
	virtual void Update(float dt);


	//网格数据
	Geometry::MeshData<VertexPosNormalTex>	m_MeshData;
	ComPtr<ID3D11ShaderResourceView>		m_pDefaultTexture;			    // 默认纹理
	//ComPtr<ID3D11SamplerState>				m_pSamplerState;			// 默认采样器
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


class CubeShape :public BasicShapeWithPosNormalTex {
public:
	CubeShape();
	CubeShape(float width , float height , float depth );

	~CubeShape();
	

	//加载纹理、网格等资源
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

	//加载纹理、网格等
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



	//加载纹理、网格等
	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

	//BasicShape里的Draw是按GOPipeLine写的，这里重写
	virtual void Draw() ;



	DirectX::XMMATRIX		m_ViewMatrix;					// 观察
	DirectX::XMMATRIX		m_ProjMatrix;					// 投影
	DirectX::XMMATRIX		m_WorldMatrix;					// 世界矩阵



	void SetTexture(ID3D11ShaderResourceView* pTexture);

protected:
	float radius ;
	UINT levels;
	UINT slices;


	//网格数据
	Geometry::MeshData<VertexPos>			m_MeshData;
	ComPtr<ID3D11ShaderResourceView>		m_pDefaultTexture;			    // 默认纹理
	//ComPtr<ID3D11SamplerState>			m_pSamplerState;			// 默认采样器
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;									// 顶点缓冲区
	ComPtr<ID3D11Buffer> m_pIndexBuffer;									// 索引缓冲区
	UINT m_IndexCount;														// 索引数目 
	UINT m_VertexStride;													// 顶点字节大小


	template<class VertexType>
	bool UpdateMesh(const Geometry::MeshData<VertexType>& meshData);
};

