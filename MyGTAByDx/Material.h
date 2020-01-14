#pragma once
#include <DirectXMath.h>
#include "string.h"
struct Material {
	Material() { memset(this, 0, sizeof(Material)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = 镜面反射强度
	DirectX::XMFLOAT4 Reflect;
};