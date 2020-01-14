#pragma once
#include "DXUtil.h"

/************************************************************************/
/* �����                                                                     */
/************************************************************************/
struct DirectionalLight
{
	DirectionalLight() { memset(this, 0, sizeof(DirectionalLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;
	DirectX::XMFLOAT3 Direction;
	float Pad; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};
