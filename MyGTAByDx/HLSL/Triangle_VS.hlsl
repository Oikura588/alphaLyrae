#include"Triangle.hlsli"


VertexOut main(VertexIn vIn)
{
	VertexOut vOut;
    vOut.posH = mul(float4(vIn.pos, 1.0f),world);
    vOut.posH = mul(vOut.posH, view);
    vOut.posH = mul(vOut.posH, proj);
	vOut.color = vIn.color;
	return vOut;
}