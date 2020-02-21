#pragma once
#include "DXUtil.h"
#include "VertexTypes.h"

//���ù���״̬��Ŀǰ��Ϊ�����������պ�����
class PipeLine
{

public:
	PipeLine();
	virtual  ~PipeLine() {};

	//��ȡ�豸��Դ,����һЩ�����ı�����ƹ��
	virtual bool InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)=0;

	//����Shader,��Shader��
	virtual bool InitShader()=0;

	//�����������������󶨵�������Ӧ��λ��
	virtual bool InitPipeLine() = 0;

	//����PipeLine��ÿ�λ���ǰ��Ҫ���ó���ӦPipeLine
	virtual void SetPipeLine() = 0;
protected:

	//�����豸��Ϣ
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;

	//Shader��Ϣ
	ComPtr<ID3D11VertexShader>		m_pVertexShader;
	ComPtr<ID3D11InputLayout>		m_pVertexInputLayout;
	ComPtr<ID3D11PixelShader>		m_pPixelShader;


};

//��Ⱦ�����������PipeLine

class GameObjectPipeLine :public PipeLine {

public:
	GameObjectPipeLine();
	virtual ~GameObjectPipeLine() {};

	//��ȡ�豸��Դ,����һЩ�����ı�����ƹ��
	virtual bool InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext) ;

	//�����������������󶨵�������Ӧ��λ��
	virtual bool InitPipeLine();


	//����Shader,��Shader��
	virtual bool InitShader() ;

	//����PipeLine��ÿ�λ���ǰ��Ҫ���ó���ӦPipeLine
	virtual void SetPipeLine() ;

private:
	//����������
	ComPtr<ID3D11Buffer>			m_pConstantBuffers[4];			// ����������
	ConstantBufferForScene			m_ConstantBufferForScene;		//ÿ���������
	ConstantBufferForView			m_ConstantBufferForView;		//�������
	ConstantBufferForProj			m_ConstantBufferForProj;		//�������
	ConstantBufferForLit			m_ConstantBufferForLit;			//GameApp����(Ĭ�ϵƹⲻ�����仯
	ComPtr<ID3D11SamplerState>		m_pSamplerState;				// ������

	ComPtr<ID3D11RasterizerState>   m_pRSWireframe;					// ��դ��״̬: �߿�ģʽ

	//�ƹ�
	DirectionalLight		m_DirLight;								// Ĭ�Ϸ����



};


//��Ⱦ��պ͵�PipeLine

class SkyBoxPipeLine :public PipeLine {
public:
	SkyBoxPipeLine();
	
	virtual ~SkyBoxPipeLine() {};

	//��ȡ�豸��Դ,����һЩ�����ı�����ƹ��
	virtual bool InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext);

	//����Shader,��Shader��
	virtual bool InitShader();

	//�����������������󶨵�������Ӧ��λ��
	virtual bool InitPipeLine();

	//����PipeLine��ÿ�λ���ǰ��Ҫ���ó���ӦPipeLine
	virtual void SetPipeLine();


	ConstantBufferMVP				m_ConstantBufferMVP;			//MVP����
	ComPtr<ID3D11Buffer>			m_pConstantBuffer;				// ����������

	ComPtr<ID3D11RasterizerState>   m_pRSNoCull;					// ��դ��״̬: �߿�ģʽ
	ComPtr<ID3D11DepthStencilState> m_pDSSLessEqual;		        // ���/ģ��״̬������������ֵ��ȵ�����
	ComPtr<ID3D11SamplerState>		m_pSamplerState;				// ������

};