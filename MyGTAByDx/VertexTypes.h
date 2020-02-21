#pragma once
#include"DXUtil.h"
#include "LightType.h"
#include "Material.h"

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

struct VertexPos {
	DirectX::XMFLOAT3 pos;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[1];

};

// �����任�õ���buffer
// ÿ�������е��������ʱ��仯
struct ConstantBufferForScene {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX worldInvTranspose;
};

// �۲췢���仯���õ�Buffer
// ����ƶ�ʱ��仯
struct ConstantBufferForView {
	DirectX::XMMATRIX view;
	DirectX::XMFLOAT4 eyePos;
};


// ͶӰ�����仯ʱ
// ��������÷����仯ʱ�����

struct ConstantBufferForProj{
	DirectX::XMMATRIX proj;
};


// �ƹⷢ���仯
struct ConstantBufferForLit {
	DirectionalLight dirLight;
	Material material;

};


// ��պй����õ���

struct ConstantBufferMVP {
	DirectX::XMMATRIX mvp;
	
};