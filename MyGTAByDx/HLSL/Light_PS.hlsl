#include"Light.hlsli"

float4 main(VertexOut pIn):SV_Target
{
	pIn.NormalW = normalize(pIn.NormalW);
	
	// ָ���۾�������
	float3 dirToEye = normalize(g_EyePos - pIn.PosW);
	
	 // ��ʼ��Ϊ0 
	float4 ambient, diffuse, spec;
	float4 A, D, S;
	ambient = diffuse = spec = A = D = S = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	ComputeDirectionLight(g_Material, g_DirLight, pIn.NormalW, dirToEye, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;
	
	float4 litColor = pIn.Color * (ambient + diffuse) + spec;
    
	litColor.a = g_Material.Diffuse.a * pIn.Color.a;
    
	return litColor;
}