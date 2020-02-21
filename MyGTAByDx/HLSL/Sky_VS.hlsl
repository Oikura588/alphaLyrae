// Sky_VS.hlsl
#include "Sky.hlsli"

VertexPosHL main(VertexPos vIn)
{
	VertexPosHL vOut;

	// ����z = wʹ��z/w = 1(��պб�����Զƽ��)
	float4 posH = mul(float4(vIn.PosL, 1.0f), g_MVP);
	vOut.PosH = posH.xyww;
	vOut.PosL = vIn.PosL;
	return vOut;
}