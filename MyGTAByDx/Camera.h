#pragma once
#include "DXUtil.h"



// 抽象基类
// 继承以实现第一人称和第三人称相机
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

	// 获取ID
	inline unsigned int GetID() { return m_ID; }


	// 获取位置
	inline DirectX::XMFLOAT3 GetPosition() const { return m_Position; }


	// 获取矩阵
	inline DirectX::XMMATRIX GetProjM()const { return m_Proj; } 
	inline DirectX::XMMATRIX GetViewM() const { return m_View; }


	// 更新观察矩阵
	virtual void UpdateViewM() = 0;


protected:
	//相机的ID,每个id唯一
	unsigned int m_ID;


	DirectX::XMFLOAT3 m_Position;


	// 计算View矩阵
	DirectX::XMFLOAT3 m_Right;
	DirectX::XMFLOAT3 m_Up;
	DirectX::XMFLOAT3 m_Forward;
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
	float m_Size;						//视锥体竖直方向高度的一半
	//		nearClipPlaneHeight=2*Size;
	//		nearWidth=Asepect*Height;


	// 当前视口
	D3D11_VIEWPORT m_ViewPort;








};

