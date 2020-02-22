#pragma once
#include "DXUtil.h"

enum EProjectileType
{
	PERSPECTIVE,
	Orthographic
};

//��ʹ�ý���Ͳ����ý��������
enum EControType {
	LOCK,
	UNLOCK
};

// �������
// �̳���ʵ�ֵ�һ�˳ƺ͵����˳����
class Camera
{
public:
	Camera();
	virtual ~Camera() {};

	// ��ȡID
	inline unsigned int GetID() { return m_ID; }


	// ��ȡλ��
	inline DirectX::XMFLOAT3 GetPosition() const { return m_Position; }
	inline DirectX::XMVECTOR GetPositionVector() const { return XMLoadFloat3(&m_Position); }

	//����λ�õ�����
	void SetPosition(DirectX::XMFLOAT3 Position);
	void SetRight(DirectX::XMFLOAT3 Right);
	void SetUp(DirectX::XMFLOAT3 Up);
	void SetForward(DirectX::XMFLOAT3 Forward);
	void SetFocus(DirectX::XMFLOAT3 Focus);

	void SetSize(float Size);
	void SetAspect(float Aspect);
	void SetFOV(float FOV);
	void SetNear(float Near);
	void SetFar(float Far);



	



	// ��ȡ����
	inline DirectX::XMMATRIX GetProjM()const { return m_Proj; } 
	inline DirectX::XMMATRIX GetViewM() const { return m_View; }


	// ���¹۲����
	// ÿ֡����

	//�������λ�á������Լ�View��������ʵ��
	virtual void Tick(float dt)=0;		
	virtual void UpdateViewM() ;

	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext); //��ʼ����Ⱦ��Դ	



	// ����ͶӰģʽ
	// ����ͶӰģʽʱ�ŵ���

	void ChangeProjType();

	void UpdateProjM();



	void UpdateViewToPipeLine();

	void UpdateProjToPipeLine();

	// �����ƶ���������ʵ�־����߼�.��Ϊ������ڳ����ϣ������Ȳ�ʵ��
	virtual void KeyboardMoveForward(float v);
	virtual void KeyboardMoveRight(float v);



	// ����ƶ���������ʵ�־����߼�����һ�˳ƺ͵����˳Ʋ�ͬ��

	// �������ƶ�v
	virtual void MouseX(float v);

	// ��������ƶ�v
	virtual void MouseY(float v);

	// �������ƶ�

	virtual void MouseZ(float v);

protected:

	//�����ID,ÿ��idΨһ
	unsigned int m_ID;
	static unsigned int IDNum;

	DirectX::XMFLOAT3 m_Position;


	// ����View����
	EControType m_CameraCtrlType;


	DirectX::XMFLOAT3 m_Right;
	DirectX::XMFLOAT3 m_Up;
	DirectX::XMFLOAT3 m_Forward;
	DirectX::XMFLOAT3 m_Focus;
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
	float m_Size;						//��ƽ����ֱ����߶ȵ�һ��
	//		Height=2*Size;
	//		Width=Asepect*Height;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;


	// ��ǰ�ӿ�
	D3D11_VIEWPORT m_ViewPort;



	// ����ƶ��ٶ�
	float m_Speed;		


};


// Ĭ�Ͽ���ԭ��������������
class DefaultCamera :public  Camera {

public:
	DefaultCamera();
	~DefaultCamera() {};

	virtual void Tick(float dt);

};

// ��һ�˳��������д������ƶ���
class FirstPersonCamera :public Camera {
public:
	FirstPersonCamera();
	~FirstPersonCamera() {};


	//��Ϊλ�ù̶��������ϣ�����ֻʵ������߼�����

	// �������ƶ�v
	virtual void MouseX(float v);

	// ��������ƶ�v
	virtual void MouseY(float v);
	virtual void Tick(float dt);

};


class ThirdPersonCamera :public Camera {
public:
	ThirdPersonCamera();
	~ThirdPersonCamera() {};


	//��Ϊλ�ù̶��������ϣ�����ֻʵ������߼�����
	// �������ƶ�v
	virtual void MouseX(float v);

	// ��������ƶ�v
	virtual void MouseY(float v);


	virtual void MouseZ(float v);


	virtual void Tick(float dt);

	virtual void UpdateViewM();
protected:

	// ��Ӱ���۳�
	float m_ArmLength;
	// ��Ӱ������С������
	float m_MinArmLength, m_MaxArmLength;

	// ����������ϵΪ��׼����ǰ����ת�Ƕ�
	float m_Theta;
	float m_Phi;
};
