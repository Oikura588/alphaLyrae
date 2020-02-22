#include "Camera.h"
#include "DXUtil.h"
#include "VertexTypes.h"
#include "DXTrace.h"

using namespace DirectX;
unsigned int Camera::IDNum = 1;
Camera::Camera()
{
	m_ID = IDNum;
	IDNum++;

	m_Position = XMFLOAT3(0.0F, 0.0F, -10.0F);
	m_Up = XMFLOAT3(0.0F, 1.0F, 0.0F);
	m_Right = XMFLOAT3(1.0f, 0.0f, 0.0f);

	//默认朝Z轴正向，也就是屏幕向里
	m_Forward = XMFLOAT3(0.0f, 0.0f, 1.0f);
	//默认朝向原点
	m_Focus = XMFLOAT3(0.F, 0.F, 0.F);

	m_Aspect = XM_PIDIV2;
	m_Near = 1.0f;
	m_Far = 1000.0f;


	m_FOV = XM_PIDIV2;
	m_Size = 100;

	//默认为透视投影
	m_ProjectileType = EProjectileType::PERSPECTIVE;
	m_CameraCtrlType = EControType::UNLOCK;

	m_Speed = 5.f;

}

void Camera::SetPosition(DirectX::XMFLOAT3 Position)
{
	m_Position = Position;
}

void Camera::SetRight(DirectX::XMFLOAT3 Right)
{
	m_Right = Right;
}

void Camera::SetUp(DirectX::XMFLOAT3 Up)
{
	m_Up = Up;
}

void Camera::SetForward(DirectX::XMFLOAT3 Forward)
{
	m_Forward = Forward;
}

void Camera::SetFocus(DirectX::XMFLOAT3 Focus)
{
	m_Focus = Focus;
}

void Camera::SetSize(float Size)
{
	m_Size = Size;
}

void Camera::SetAspect(float Aspect)
{
	m_Aspect = Aspect;
}

void Camera::SetFOV(float FOV)
{
	m_FOV = FOV;
}

void Camera::SetNear(float Near)
{
	m_Near = Near;
}

void Camera::SetFar(float Far)
{
	m_Far = Far;
}



void Camera::UpdateViewM()
{
	//根据枚举值来判断使用LookAt还是使用LookTo
	switch (m_CameraCtrlType)
	{
	case EControType::UNLOCK:
	{
		m_View = XMMatrixLookToLH(GetPositionVector(), XMLoadFloat3(&m_Forward), XMLoadFloat3(&m_Up));
		break;
	}

	case EControType::LOCK:
	{
		//m_View = XMMatrixLookAtLH(GetPositionVector(), XMLoadFloat3(&m_Focus), XMLoadFloat3(&m_Up));
		XMVECTOR R = XMLoadFloat3(&m_Right);
		XMVECTOR U = XMLoadFloat3(&m_Up);
		XMVECTOR L = XMLoadFloat3(&m_Forward);
		XMVECTOR P = XMLoadFloat3(&m_Position);

		// 保持摄像机的轴互为正交，且长度都为1
		L = XMVector3Normalize(L);
		U = XMVector3Normalize(XMVector3Cross(L, R));

		// U, L已经正交化，需要计算对应叉乘得到R
		R = XMVector3Cross(U, L);

		// 填充观察矩阵
		float x = -XMVectorGetX(XMVector3Dot(P, R));
		float y = -XMVectorGetX(XMVector3Dot(P, U));
		float z = -XMVectorGetX(XMVector3Dot(P, L));

		XMStoreFloat3(&m_Right, R);
		XMStoreFloat3(&m_Up, U);
		XMStoreFloat3(&m_Forward, L);

		m_View = {
			m_Right.x, m_Up.x, m_Forward.x, 0.0f,
			m_Right.y, m_Up.y, m_Forward.y, 0.0f,
			m_Right.z, m_Up.z, m_Forward.z, 0.0f,
			x, y, z, 1.0f
		};

		break;
	}


	}

	//XMFLOAT3 Zero(0.f, 0.f, 0.f);
	//m_View = XMMatrixLookAtLH(GetPositionVector(), XMLoadFloat3(&Zero), XMLoadFloat3(&m_Up));
	UpdateViewToPipeLine();
}

void Camera::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;
}

void Camera::UpdateViewToPipeLine()
{

	//获取已经绑定到管线上的常量缓冲区并进行更改
	ComPtr<ID3D11Buffer> cBuffer = nullptr;
	m_pd3dDeviceContext->VSGetConstantBuffers(1, 1, &cBuffer);
	ConstantBufferForView cBForView;


	cBForView.view = DirectX::XMMatrixTranspose(GetViewM());
	cBForView.eyePos = DirectX::XMFLOAT4(GetPosition().x, GetPosition().y, GetPosition().z, 1.0f);

	// 更新观察矩阵
	D3D11_MAPPED_SUBRESOURCE mappedData;

	HR(m_pd3dDeviceContext->Map(cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForView), &cBForView, sizeof(ConstantBufferForView));
	m_pd3dDeviceContext->Unmap(cBuffer.Get(), 0);
}

void Camera::UpdateProjToPipeLine()
{

	//获取已经绑定到管线上的常量缓冲区并进行更改
	ComPtr<ID3D11Buffer> cBuffer = nullptr;
	m_pd3dDeviceContext->VSGetConstantBuffers(2, 1, &cBuffer);
	ConstantBufferForProj cBForProj;


	cBForProj.proj = DirectX::XMMatrixTranspose(GetProjM());

	// 更新观察矩阵
	D3D11_MAPPED_SUBRESOURCE mappedData;

	HR(m_pd3dDeviceContext->Map(cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForProj), &cBForProj, sizeof(ConstantBufferForProj));
	m_pd3dDeviceContext->Unmap(cBuffer.Get(), 0);
}

void Camera::KeyboardMoveForward(float v)
{
}

void Camera::KeyboardMoveRight(float v)
{
}

void Camera::MouseX(float v)
{
	//根据鼠标横向的值来转向,即Yaw值


}

void Camera::MouseY(float v)
{
	//根据鼠标竖向的值来转向,即Pitch
}

void Camera::MouseZ(float v)
{
	//根据鼠标滚轮的值来拉近缩远等

}

void Camera::ChangeProjType()
{
	if (m_ProjectileType== EProjectileType::Orthographic)
	{
		m_ProjectileType = EProjectileType::PERSPECTIVE;

	}
	else {
		m_ProjectileType = EProjectileType::Orthographic;
	}

	UpdateProjM();
}

void Camera::UpdateProjM()
{
	//根据枚举值来判断使用哪种投影
	switch (m_ProjectileType)
	{
	case EProjectileType::Orthographic:
	{
		float Height = 2 * m_Size;
		float Width = m_Aspect * Height;
		m_Proj = XMMatrixOrthographicOffCenterLH(-Width / 2.F, Width / 2.F, -Height / 2.F, Height / 2.F, m_Near, m_Far);
	
		break; 
	}
		
	case EProjectileType::PERSPECTIVE:
		m_Proj = XMMatrixPerspectiveFovLH(m_FOV, m_Aspect, m_Near, m_Far);
		break;
	}

	UpdateProjToPipeLine();



}

DefaultCamera::DefaultCamera()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, -5.0f);
}



void DefaultCamera::Tick(float dt)
{
	//UpdateViewM();

}

FirstPersonCamera::FirstPersonCamera()
{
	m_CameraCtrlType = EControType::UNLOCK;
}



void FirstPersonCamera::MouseX(float v)
{
	v = v * m_Speed/5000.f;
	XMMATRIX R = XMMatrixRotationY(v);

	XMStoreFloat3(&m_Right, XMVector3TransformNormal(XMLoadFloat3(&m_Right), R));
	//XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), R));
	XMStoreFloat3(&m_Forward, XMVector3TransformNormal(XMLoadFloat3(&m_Forward), R));

}

void FirstPersonCamera::MouseY(float v)
{
	v = v * m_Speed / 5000.f;
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&m_Right), v);
	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), R));
	XMStoreFloat3(&m_Forward, XMVector3TransformNormal(XMLoadFloat3(&m_Forward), R));

	//XMVECTOR Up = XMVector3TransformNormal(XMLoadFloat3(&m_Up), R);
	//XMVECTOR Look = XMVector3TransformNormal(XMLoadFloat3(&m_Forward), R);

	float cosPhi = (m_Forward.y);
	// 将上下视野角度Phi限制在[2pi/9, 7pi/9]，
	// 即余弦值[-cos(2pi/9), cos(2pi/9)]之间
	if (fabs(cosPhi) > cosf(XM_2PI / 9))
		return;

	//XMStoreFloat3(&m_Up, Up);
	//XMStoreFloat3(&m_Forward, Look);



	//XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&m_Right), v);
	//XMVECTOR Up = XMVector3TransformNormal(XMLoadFloat3(&m_Up), R);
	//XMVECTOR Look = XMVector3TransformNormal(XMLoadFloat3(&m_Forward), R);
	//float cosPhi = XMVectorGetY(Look);
	//// 将上下视野角度Phi限制在[2pi/9, 7pi/9]，
	//// 即余弦值[-cos(2pi/9), cos(2pi/9)]之间
	//if (fabs(cosPhi) > cosf(XM_2PI / 9))
	//	return;

	//XMStoreFloat3(&m_Up, Up);
	//XMStoreFloat3(&m_Forward, Look);
}

void FirstPersonCamera::Tick(float dt)
{
	UpdateViewM();


}

ThirdPersonCamera::ThirdPersonCamera()
{
	m_ArmLength = 10.F;
	m_MinArmLength = 5.f;
	m_MaxArmLength = 20.f;
	m_Phi = 0.f;
	m_Theta = 0.f;

	m_CameraCtrlType = EControType::LOCK;
}

void ThirdPersonCamera::MouseX(float v)
{
	v = v * m_Speed / 5000.0f;

	m_Theta = XMScalarModAngle(m_Theta - v);

}

void ThirdPersonCamera::MouseY(float v)
{
	v=v* m_Speed / 5000.0f;

	m_Phi -= v;
	// 将上下视野角度Phi限制在[pi/6, pi/2]，
	// 即余弦值[0, cos(pi/6)]之间
	if (m_Phi < XM_PI / 6)
		m_Phi = XM_PI / 6;
	else if (m_Phi > XM_PIDIV2)
		m_Phi = XM_PIDIV2;
}

void ThirdPersonCamera::MouseZ(float v)
{
	v = v * m_Speed / 1000.0f;
	m_ArmLength += v;
	// 限制距离在[m_MinDist, m_MaxDist]之间
	if (m_ArmLength < m_MinArmLength)
		m_ArmLength = m_MinArmLength;
	else if (m_ArmLength > m_MaxArmLength)
		m_ArmLength = m_MaxArmLength;

}

void ThirdPersonCamera::Tick(float dt)
{
	// 球面坐标系
	float x = m_Focus.x + m_ArmLength * sinf(m_Phi) * cosf(m_Theta);
	float z = m_Focus.z + m_ArmLength * sinf(m_Phi) * sinf(m_Theta);
	float y = m_Focus.y + m_ArmLength * cosf(m_Phi);
	m_Position = { x, y, z };
	//UpdateViewM();

}

void ThirdPersonCamera::UpdateViewM()
{
	
	XMVECTOR P = XMLoadFloat3(&m_Position);
	XMVECTOR F = XMVector3Normalize(XMLoadFloat3(&m_Focus) - P);
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), F));
	XMVECTOR U = XMVector3Cross(F, R);

	// 更新向量
	XMStoreFloat3(&m_Right, R);
	XMStoreFloat3(&m_Up, U);
	XMStoreFloat3(&m_Forward, F);


	Camera::UpdateViewM();
	

}

