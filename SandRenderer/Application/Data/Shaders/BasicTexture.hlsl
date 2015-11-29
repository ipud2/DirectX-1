// #include "LightHelper.hlsli"
void ComputeDirectionalLight(float4 AmbientMaterial , 	float4 DiffuseMaterial , 	float4 SpecularMaterial , 
							 float4 AmbientLight , 		float4 DiffuseLight , 		float4 SpecularLight , 
							 float3 LightDirection , 
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
	ambient = AmbientLight * AmbientMaterial;

	float3 Incident = -LightDirection;

	// 检测入射光与法线是否在同一侧
	float DiffuseFactor = dot(Incident , Normal);

	[flatten]
	if(DiffuseFactor > 0.0f)
	{
		float3 Reflect = reflect(LightDirection , Normal);
		float SpecularFactor = pow(max(dot(Reflect , ToEye) , 0.0f) , SpecularMaterial.w);

		diffuse = DiffuseFactor * DiffuseLight * DiffuseMaterial;
		specular = SpecularFactor * SpecularLight * SpecularMaterial;
	}
}

cbuffer Transforms
{
	matrix WorldViewProjMatrix;
	matrix WorldMatrix;
	matrix WorldInvTransposeMatrix;
	matrix TexTransform;
};

cbuffer DirectionLight
{
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;

	float4 LightDirection;
};

cbuffer SurfaceMaterial
{
	float4 AmbientMaterial;
	float4 DiffuseMaterial;
	float4 SpecularMaterial;
};

cbuffer PhongParameter
{
	float4 ViewPosition;
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
	float3 ToEye = ViewPosition.xyz - input.PosW;

	float dist = length(ToEye);

	ToEye /= dist;

	float4 color = WoodCrateTexture.Sample(LinearSampler , input.Tex);

	float4 ambient = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 diffuse = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 specular = float4(0.0f , 0.0f , 0.0f , 0.0f);

	ComputeDirectionalLight(AmbientMaterial , 	DiffuseMaterial , 	SpecularMaterial , 
							AmbientLight , 		DiffuseLight , 		SpecularLight , 
							LightDirection.xyz , 
							input.NormalW , 
							ToEye , 
							ambient , 
							diffuse , 
							specular);

	color = color * (ambient + diffuse) + specular;

	return color;
}