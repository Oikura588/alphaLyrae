#pragma once
#include "DXUtil.h"

enum EProjectileType
{
	PERSPECTIVE,
	Orthographic
};

//即使用焦点和不适用焦点的区别
enum EControType {
	LOCK,
	UNLOCK
};

// 抽象基类
// 继承以实现第一人称和第三人称相机
class Camera
{
public:
	Camera();
	virtual ~Camera() {};

	// 获取ID
	inline unsigned int GetID() { return m_ID; }


	// 获取位置
	inline DirectX::XMFLOAT3 GetPosition() const { return m_Position; }
	inline DirectX::XMVECTOR GetPositionVector() const { return XMLoadFloat3(&m_Position); }

	//设置位置等属性
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



	



	// 获取矩阵
	inline DirectX::XMMATRIX GetProjM()const { return m_Proj; } 
	inline DirectX::XMMATRIX GetViewM() const { return m_View; }


	// 更新观察矩阵
	// 每帧调用

	//更新相机位置、朝向以及View矩阵，子类实现
	virtual void Tick(float dt)=0;		
	virtual void UpdateViewM() ;

	void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext); //初始化渲染资源	



	// 更改投影模式
	// 更改投影模式时才调用

	void ChangeProjType();

	void UpdateProjM();



	void UpdateViewToPipeLine();

	void UpdateProjToPipeLine();

	// 键盘移动，由子类实现具体逻辑.因为相机绑定在车子上，所以先不实现
	virtual void KeyboardMoveForward(float v);
	virtual void KeyboardMoveRight(float v);



	// 鼠标移动，由子类实现具体逻辑（第一人称和第三人称不同）

	// 鼠标横向移动v
	virtual void MouseX(float v);

	// 鼠标竖向移动v
	virtual void MouseY(float v);

	// 鼠标滚轮移动

	virtual void MouseZ(float v);

protected:

	//相机的ID,每个id唯一
	unsigned int m_ID;
	static unsigned int IDNum;

	DirectX::XMFLOAT3 m_Position;


	// 计算View矩阵
	EControType m_CameraCtrlType;


	DirectX::XMFLOAT3 m_Right;
	DirectX::XMFLOAT3 m_Up;
	DirectX::XMFLOAT3 m_Forward;
	DirectX::XMFLOAT3 m_Focus;
	DirectX::XMMATRIX m_View;
	


	// 计算投影矩阵
	EProjectileType m_ProjectileType;


	DirectX::XMMATRIX m_Proj;

	float m_Near;						//近裁剪平面
	float m_Far;						//远裁剪平面
	float m_Aspect;						//横纵比			Width/Height

	
	// 透视投影需要知道FOV，而正交投影只需要知道横纵之一就可以计算
	// Perspective
	float	m_FOV;						// FOV , 垂直方向的张开角度，（0，180）
										
	//		nearClipPlaneHeight=2*m_Near*tan(m_FOV/2)
	//		farClipPlaneHeight=2*m_Far*tan(m_FOV/2)
	//		nearClipPlaneWidth=Height*Aspect;
	//		...
	
	// Orthographic
	float m_Size;						//视平面竖直方向高度的一半
	//		Height=2*Size;
	//		Width=Asepect*Height;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;


	// 当前视口
	D3D11_VIEWPORT m_ViewPort;



	// 鼠标移动速度
	float m_Speed;		


};


// 默认看向原点的相机，测试用
class DefaultCamera :public  Camera {

public:
	DefaultCamera();
	~DefaultCamera() {};

	virtual void Tick(float dt);

};

// 第一人称相机，重写了鼠标移动等
class FirstPersonCamera :public Camera {
public:
	FirstPersonCamera();
	~FirstPersonCamera() {};


	//因为位置固定到车子上，所以只实现鼠标逻辑就行

	// 鼠标横向移动v
	virtual void MouseX(float v);

	// 鼠标竖向移动v
	virtual void MouseY(float v);
	virtual void Tick(float dt);

};


class ThirdPersonCamera :public Camera {
public:
	ThirdPersonCamera();
	~ThirdPersonCamera() {};


	//因为位置固定到车子上，所以只实现鼠标逻辑就行
	// 鼠标横向移动v
	virtual void MouseX(float v);

	// 鼠标竖向移动v
	virtual void MouseY(float v);


	virtual void MouseZ(float v);


	virtual void Tick(float dt);

	virtual void UpdateViewM();
protected:

	// 摄影机臂长
	float m_ArmLength;
	// 摄影机的最小最大距离
	float m_MinArmLength, m_MaxArmLength;

	// 以世界坐标系为基准，当前的旋转角度
	float m_Theta;
	float m_Phi;
};
