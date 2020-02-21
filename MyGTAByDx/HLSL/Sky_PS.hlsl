// Sky_PS.hlsl
#include "Sky.hlsli"

float4 main(VertexPosHL pIn) : SV_Target
{
	//return float4(1.0f,1.f,1.f,1.f);
	return g_TexCube.Sample(g_Sam, pIn.PosL);
}