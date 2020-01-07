// HLSL中要用到的结构体
struct VertexIn {
	float3 pos:POSITION;
	float4 color:COLOR;
};

struct VertexOut {
	float4 posH:SV_POSITION;
	float4 color:COLOR;
};


