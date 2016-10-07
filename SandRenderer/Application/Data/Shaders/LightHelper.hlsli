struct DirectionalLight
{
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;

	float4 LightDirection;
};

cbuffer Material
{
	float4 AmbientMaterial;
	float4 DiffuseMaterial;
	float4 SpecularMaterial;

	float4 Reflect;
};

void ComputeDirectionalLight(DirectionalLight light , 
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
	ambient = light.AmbientLight * AmbientMaterial;

	float3 Incident = -light.LightDirection.xyz;

	// 检测入射光与法线是否在同一侧
	float DiffuseFactor = dot(Incident , Normal);

	[flatten]
	if(DiffuseFactor > 0.0f)
	{
		float3 Reflect = reflect(-Incident , Normal);
		float SpecularFactor = pow(max(dot(Reflect , ToEye) , 0.0f) , SpecularMaterial.w);

		diffuse = DiffuseFactor * light.DiffuseLight * DiffuseMaterial;
		specular = SpecularFactor * light.SpecularLight * SpecularMaterial;
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

static const float SMAP_SIZE = 2048.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;

//
// 计算阴影系数：
// shadowPosH 是以光源为视点时，该点从局部空间变换到纹理空间后的坐标值
// (局部->世界->视图->NDC->纹理空间)
// shadowPosH.xy代表纹理坐标
// shadowPosH.z 代表以灯光为视点时，归一化的深度值
// 1.0f代表完全不在阴影中，0.0f代表完全处于阴影中
//
float CalcShadowFactor(SamplerComparisonState ShadowSampler , Texture2D ShadowMap , float4 ShadowPosH)
{
	ShadowPosH.xy /= ShadowPosH.w;

	float depth = ShadowPosH.z;

	const float dx = SMAP_DX;

	float percentLit = 0.0f;
	const float2 offsets[9] = 
	{
		float2(-dx , -dx) , float2(0.0f , -dx) , float2(dx , -dx) , 
		float2(-dx , 0.0f) , float2(0.0f , 0.0f) , float2(dx , 0.0f) , 
		float2(-dx , dx) , float2(0.0f , dx) , float2(dx , dx)
	};

	[unroll]
	for(int i = 0; i < 9; i++)
	{
		//
		// ShadowMap.SampleCmpLevelZero(SampleComparisonState ShadowSampler , float2 Pos , float depth)
		// 以Pos为纹理坐标采样，采样方式由ShadowSampler定义
		// 采样得到的值是一个深度值s
		// 将其与depth进行比较
		// 比较操作由ShadowSampler的成员ComparisonFunc定义
		// 如：当ComparisonFunc定义的操作为LESS
		// 则当depth < s时，返回1
		// 否则返回0
		//
		percentLit += ShadowMap.SampleCmpLevelZero(ShadowSampler , ShadowPosH.xy + offsets[i] , depth).r;
	}

	return percentLit /= 9.0f;
}