// HLSL��Ҫ�õ��Ľṹ��
cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix proj;
    
}

struct VertexIn {
	float3 pos:POSITION;
	float4 color:COLOR;
};

struct VertexOut {
	float4 posH:SV_POSITION;
	float4 color:COLOR;
};


