struct DirectionalLight
{
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;

	float4 LightDirection;
};

struct SurfaceMaterial
{
	float4 AmbientMaterial;
	float4 DiffuseMaterial;
	float4 SpecularMaterial;
};

void ComputeDirectionalLight(SurfaceMaterial Material , 
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
	ambient = light.AmbientLight * Material.AmbientMaterial;

	float3 Incident = -light.LightDirection.xyz;

	// 检测入射光与法线是否在同一侧
	float DiffuseFactor = dot(Incident , Normal);

	[flatten]
	if(DiffuseFactor > 0.0f)
	{
		float3 Reflect = reflect(-Incident , Normal);
		float SpecularFactor = pow(max(dot(Reflect , ToEye) , 0.0f) , Material.SpecularMaterial.w);

		diffuse = DiffuseFactor * light.DiffuseLight * Material.DiffuseMaterial;
		specular = SpecularFactor * light.SpecularLight * Material.SpecularMaterial;
	}
}

cbuffer DirectionLight
{
	DirectionalLight Light[2];
};

cbuffer SurfaceProperty
{
	SurfaceMaterial BasicSurfaceProperty;
};

cbuffer Transforms
{
	matrix WorldViewProjMatrix;
	matrix WorldMatrix;
	matrix WorldInvTransposeMatrix;
	matrix TexTransform;
};

cbuffer PhongParameter
{
	float3 ViewPosition;
};

SamplerState LinearSampler;
Texture2D WoodCrateTexture;

struct VertexIn
{
	float3 Pos 		: POSITION;
	float2 Tex 		: TEXCOORD;
	float3 Normal 	: NORMAL;
};

struct PixelIn
{
	float4 PosV 	: SV_POSITION;
	float3 PosW		: POSITION;
	float2 Tex 		: TEXCOORD;
	float3 NormalW 	: NORMAL;
};

PixelIn VSMain(in VertexIn input)
{
	PixelIn output = (PixelIn)0;

	output.PosV = mul(float4(input.Pos , 1.0f) , WorldViewProjMatrix);
	output.PosW = mul(float4(input.Pos , 1.0f) , WorldMatrix).xyz;
	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransform).xy;
	output.NormalW = mul(input.Normal , (float3x3)WorldInvTransposeMatrix);

	return output;
}

float4 PSMain(in PixelIn input) : SV_Target
{
	input.NormalW = normalize(input.NormalW);

	// 计算指向视点的向量
	float3 ToEye = ViewPosition - input.PosW;

	float dist = length(ToEye);

	ToEye /= dist;

	float4 color = WoodCrateTexture.Sample(LinearSampler , input.Tex);

	float4 ambient = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 diffuse = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 specular = float4(0.0f , 0.0f , 0.0f , 0.0f);

	[unroll]
	for(int i = 0; i < 2; i++)
	{
		float4 A , D , S;

		ComputeDirectionalLight(BasicSurfaceProperty , 
							Light[i] ,
							input.NormalW , 
							ToEye , 
							A , 
							D , 
							S);

		ambient += A;
		diffuse += D;
		specular += S;
	}
	

	color = color * (ambient + diffuse) + specular;

	return color;
}