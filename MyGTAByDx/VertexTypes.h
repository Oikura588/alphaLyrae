#pragma once
#include"DXUtil.h"
#include "LightType.h"

struct VertexPosNormalTex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 tex;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
}; 



struct VertexPosNormalColor {
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 color;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];

};

// 场景变换用到的buffer
// 每个场景中的物体更新时会变化
struct ConstantBufferForScene {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX worldInvTranspose;
};

// 观察发生变化是用的Buffer
// 相机移动时会变化
struct ConstantBufferForView {
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX eyePos;
};


// 投影发生变化时

struct ConstantBufferForProj{
	DirectX::XMMATRIX proj;
};


// 灯光发生变化
struct ConstantBufferForLit {
	DirectionalLight dirLight;
	int numDirLight;
	DirectX::XMFLOAT3 pad;
};