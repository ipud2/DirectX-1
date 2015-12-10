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