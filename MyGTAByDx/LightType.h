#pragma once
#include "DXUtil.h"

/************************************************************************/
/* 方向光                                                                     */
/************************************************************************/
struct DirectionalLight
{
	DirectionalLight() { memset(this, 0, sizeof(DirectionalLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;
	DirectX::XMFLOAT3 Direction;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};
