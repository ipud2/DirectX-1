struct DirectionalLight
{
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;

	float4 LightDirection;
};

struct Material
{
	float4 AmbientMaterial;
	float4 DiffuseMaterial;
	float4 SpecularMaterial;

	float4 Reflect;
};

void ComputeDirectionalLight(Material Mat , 
							 DirectionalLight light , 
							 float3 Normal , 
							 float3 ToEye , 
							 out float4 ambient , 
							 out float4 diffuse , 
							 out float4 specular)
{
	/*
		Phong Reflection Model
	*/
	ambient = float4(0.0f , 0.0f , 0.0f , 0.0f);
	diffuse = float4(0.0f , 0.0f , 0.0f , 0.0f);
	specular = float4(0.0f , 0.0f , 0.0f , 0.0f);

	// 计算环境光
	ambient = light.AmbientLight * Mat.AmbientMaterial;

	float3 Incident = -light.LightDirection.xyz;

	// 检测入射光与法线是否在同一侧
	float DiffuseFactor = dot(Incident , Normal);

	[flatten]
	if(DiffuseFactor > 0.0f)
	{
		float3 Reflect = reflect(-Incident , Normal);
		float SpecularFactor = pow(max(dot(Reflect , ToEye) , 0.0f) , Mat.SpecularMaterial.w);

		diffuse = DiffuseFactor * light.DiffuseLight * Mat.DiffuseMaterial;
		specular = SpecularFactor * light.SpecularLight * Mat.SpecularMaterial;
	}
}


// 根据法线贴图采样得到的值扰动法线
// 法线贴图中采样得到的数据为该点法线在切线空间中的坐标
// 由于我们的光照计算时在世界空间中完成
// 因此我们需要计算出在世界空间中被扰动后的法线
float3 NormalSampleToWorldSpace(float3 NormalMapSample , 
								float3 UnitNormalW , 
								float3 TangentW)
{
	// 法线贴图中采样得到的值范围在[0 , 1]
	// 需要将其转换到[-1 , 1]
	float3 NormalTangent = 2 * NormalMapSample - 1;

	// 正交坐标轴
	float3 N = UnitNormalW;
	float3 T = normalize(TangentW - dot(TangentW , N) * N);
	float3 B = cross(N , T);


	/*
		Tx Ty Tz
		Bx By Bz
		Nx Ny Nz
	*/
	float3x3 TBN = float3x3(T , B , N);
	float3 BumpNormalW = mul(NormalTangent , TBN);

	return BumpNormalW;
}