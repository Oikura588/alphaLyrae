// 标准材质
struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular; // w = SpecPower
	float4 Reflect;
};



// 平行光
struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float Pad;
};

void ComputeDirectionLight(Material mat, DirectionalLight L,
							float3 normal,float3 dirToEye,
							out float4 ambient,
							out float4 diffuse,
							out float4 spec
)
{
	// 初始化输出
	 // 初始化输出
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // 光向量与照射方向相反
	float3 lightVec = -L.Direction;

    // 添加环境光
	ambient = mat.Ambient * L.Ambient;

    // 添加漫反射光和镜面光
	float diffuseFactor = dot(lightVec, normal);

    // 展开，避免动态分支
    [flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, dirToEye), 0.0f), mat.Specular.w);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular * L.Specular;
	}
	
	
}