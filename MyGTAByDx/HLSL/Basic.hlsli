#include "LightHelper.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_SamLinear : register(s0);

cbuffer VSConstantBuffer : register(b0)
{
	matrix g_World;
	matrix g_View;
	matrix g_Proj;
	matrix g_WorldInvTranspose;

}


cbuffer PSConstantBuffer : register(b1)
{
	DirectionalLight g_DirLight;
	Material g_Material;
	float3 g_EyePos;
	float g_Pad;
	
	float3 g_EyePosW;
	float g_Pad2;
}


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