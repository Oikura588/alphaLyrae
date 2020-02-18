#include "LightHelper.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_SamLinear : register(s0);



//constant buffer
cbuffer ConstantBufferForSceneChange : register(b0) 
{
	matrix g_World;
	matrix g_WorldInvTranspose;
};

cbuffer ConstantBufferForViewChange : register(b1) 
{
	matrix g_View;
	float3 g_EyePosW;
};

cbuffer ConstantBufferForProjChange : register(b2) 
{
	matrix g_Proj;
};

cbuffer ConstantBufferForLitChange : register(b3) 
{
	DirectionalLight g_DirLight;
	Material g_Material;
};


//cbuffer VSConstantBuffer : register(b0)
//{
//	matrix g_World;
//	matrix g_View;
//	matrix g_Proj;
//	matrix g_WorldInvTranspose;
//
//}
//
//
//cbuffer PSConstantBuffer : register(b1)
//{
//	DirectionalLight g_DirLight;
//	Material g_Material;
//	float3 g_EyePos;
//	float g_Pad;
//	
//	float3 g_EyePosW;
//	float g_Pad2;
//}
//
//




//vertex data

struct VertexPosNormalTex
{
	float3 PosL : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex : TEXCOORD;
};

struct VertexPosHWNormalTex
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;		
	float3 NormalW : NORMAL;	
	float2 Tex : TEXCOORD;
};