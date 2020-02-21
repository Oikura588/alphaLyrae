TextureCube g_TexCube : register(t0);
SamplerState g_Sam : register(s0);



cbuffer ConstantBufferMVP : register(b0)
{
	matrix g_MVP;
}

struct VertexPos
{
	float3 PosL : POSITION;
};

struct VertexPosHL
{
	float4 PosH : SV_POSITION;
	float3 PosL : POSITION;
};