#pragma once
#include "DXUtil.h"
#include "VertexTypes.h"

//设置管线状态，目前分为场景物体和天空盒两种
class PipeLine
{

public:
	PipeLine();
	virtual  ~PipeLine() {};

	//获取设备资源,设置一些基本的变量如灯光等
	virtual bool InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)=0;

	//创建Shader,绑定Shader等
	virtual bool InitShader()=0;

	//创建常量缓冲区并绑定到管线相应槽位等
	virtual bool InitPipeLine() = 0;

	//设置PipeLine，每次绘制前都要设置成相应PipeLine
	virtual void SetPipeLine() = 0;
protected:

	//保存设备信息
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;

	//Shader信息
	ComPtr<ID3D11VertexShader>		m_pVertexShader;
	ComPtr<ID3D11InputLayout>		m_pVertexInputLayout;
	ComPtr<ID3D11PixelShader>		m_pPixelShader;


};

//渲染场景内物体的PipeLine

class GameObjectPipeLine :public PipeLine {

public:
	GameObjectPipeLine();
	virtual ~GameObjectPipeLine() {};

	//获取设备资源,设置一些基本的变量如灯光等
	virtual bool InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext) ;

	//创建常量缓冲区并绑定到管线相应槽位等
	virtual bool InitPipeLine();


	//创建Shader,绑定Shader等
	virtual bool InitShader() ;

	//设置PipeLine，每次绘制前都要设置成相应PipeLine
	virtual void SetPipeLine() ;

private:
	//常量缓冲区
	ComPtr<ID3D11Buffer>			m_pConstantBuffers[4];			// 常量缓冲区
	ConstantBufferForScene			m_ConstantBufferForScene;		//每个物体管理
	ConstantBufferForView			m_ConstantBufferForView;		//相机管理
	ConstantBufferForProj			m_ConstantBufferForProj;		//相机管理
	ConstantBufferForLit			m_ConstantBufferForLit;			//GameApp管理(默认灯光不发生变化
	ComPtr<ID3D11SamplerState>		m_pSamplerState;				// 采样器

	ComPtr<ID3D11RasterizerState>   m_pRSWireframe;					// 光栅化状态: 线框模式

	//灯光
	DirectionalLight		m_DirLight;								// 默认方向光



};


//渲染天空和的PipeLine

class SkyBoxPipeLine :public PipeLine {
public:
	SkyBoxPipeLine();
	
	virtual ~SkyBoxPipeLine() {};

	//获取设备资源,设置一些基本的变量如灯光等
	virtual bool InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

	//创建Shader,绑定Shader等
	virtual bool InitShader();

	//创建常量缓冲区并绑定到管线相应槽位等
	virtual bool InitPipeLine();

	//设置PipeLine，每次绘制前都要设置成相应PipeLine
	virtual void SetPipeLine();


	ConstantBufferMVP				m_ConstantBufferMVP;			//MVP矩阵
	ComPtr<ID3D11Buffer>			m_pConstantBuffer;				// 常量缓冲区

	ComPtr<ID3D11RasterizerState>   m_pRSNoCull;					// 光栅化状态: 线框模式
	ComPtr<ID3D11DepthStencilState> m_pDSSLessEqual;		        // 深度/模板状态：允许绘制深度值相等的像素
	ComPtr<ID3D11SamplerState>		m_pSamplerState;				// 采样器

};