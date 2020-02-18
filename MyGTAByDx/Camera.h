#pragma once
#include "DXUtil.h"



// �������
// �̳���ʵ�ֵ�һ�˳ƺ͵����˳����
class Camera
{

	enum EProjectileType
	{
		PERSPECTIVE,
		Orthographic
	};
public:
	Camera();
	virtual ~Camera()=0;

	// ��ȡID
	inline unsigned int GetID() { return m_ID; }


	// ��ȡλ��
	inline DirectX::XMFLOAT3 GetPosition() const { return m_Position; }


	// ��ȡ����
	inline DirectX::XMMATRIX GetProjM()const { return m_Proj; } 
	inline DirectX::XMMATRIX GetViewM() const { return m_View; }


	// ���¹۲����
	virtual void UpdateViewM() = 0;


protected:
	//�����ID,ÿ��idΨһ
	unsigned int m_ID;


	DirectX::XMFLOAT3 m_Position;


	// ����View����
	DirectX::XMFLOAT3 m_Right;
	DirectX::XMFLOAT3 m_Up;
	DirectX::XMFLOAT3 m_Forward;
	DirectX::XMMATRIX m_View;
	


	// ����ͶӰ����
	EProjectileType m_ProjectileType;
	DirectX::XMMATRIX m_Proj;

	float m_Near;						//���ü�ƽ��
	float m_Far;						//Զ�ü�ƽ��
	float m_Aspect;						//���ݱ�			Width/Height

	
	// ͸��ͶӰ��Ҫ֪��FOV��������ͶӰֻ��Ҫ֪������֮һ�Ϳ��Լ���
	// Perspective
	float	m_FOV;						// FOV , ��ֱ������ſ��Ƕȣ���0��180��
										
	//		nearClipPlaneHeight=2*m_Near*tan(m_FOV/2)
	//		farClipPlaneHeight=2*m_Far*tan(m_FOV/2)
	//		nearClipPlaneWidth=Height*Aspect;
	//		...
	
	// Orthographic
	float m_Size;						//��׶����ֱ����߶ȵ�һ��
	//		nearClipPlaneHeight=2*Size;
	//		nearWidth=Asepect*Height;


	// ��ǰ�ӿ�
	D3D11_VIEWPORT m_ViewPort;








};

