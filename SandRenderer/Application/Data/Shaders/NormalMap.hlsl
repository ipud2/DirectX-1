#include "LightHelper.hlsli"

cbuffer cbTrasform
{
	 matrix WorldMatrix;
	 matrix WorldInvTransposeMatrix;
	 matrix WorldViewProjMatrix;
	 matrix TexTransformMatrix;
};

cbuffer cbLight
{
	DirectionalLight Light[3];
	matrix ShadowTransformMatrix;
};

cbuffer cbMaterial
{
	Material Mat;
};

cbuffer cbEffect
{
	bool bUseTexture = true;
	bool bAlphaClip = true;
	bool bEnabledReflect = false;
};

cbuffer cbPhongParameter
{
	float3 ViewPosition;
};

TextureCube SkyboxTexture;
Texture2D DiffuseTexture;
Texture2D ShadowMap;
Texture2D NormalMap;
SamplerState LinearSampler;
SamplerComparisonState ShadowSampler;


struct VertexIn
{
	float3 PosL 	:	POSITION;
	float3 NormalL 	:	NORMAL;
	float2 Tex 		:	TEXCOORD;
	float3 TangentL	:	TANGENT;
};

struct PixelIn
{
	float4 PosH			:	SV_POSITION;
	float3 PosW			:	POSITION;
	float3 NormalW		:	NORMAL;
	float3 TangentW		:	TANGENT;
	float2 Tex 			:	TEXCOORD0;
	float4 ShadowPosH	:	TEXCOORD1;
};

PixelIn VSMain(VertexIn input)
{
	PixelIn output;

	output.PosW = mul(float4(input.PosL , 1.0f) , WorldMatrix).xyz;
	output.PosH = mul(float4(input.PosL , 1.0f) , WorldViewProjMatrix);

	output.TangentW = mul(input.TangentL , (float3x3)WorldMatrix);

	output.NormalW = mul(input.NormalL , (float3x3)WorldInvTransposeMatrix);

	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransformMatrix).xy;

	output.ShadowPosH = mul(float4(input.PosL , 1.0f) , ShadowTransformMatrix);

	return output;
}

float4 PSMain(in PixelIn input) : SV_Target
{
	// 将法线归一化
	input.NormalW = normalize(input.NormalW);

	float3 toEye = ViewPosition - input.PosW;

	float dist = length(toEye);

	toEye /= dist;

	float4 TexColor = float4(1.0f , 1.0f , 1.0f , 1.0f);
	if(bUseTexture)
	{
		TexColor = DiffuseTexture.Sample(LinearSampler , input.Tex);

		if(bAlphaClip)
		{
			clip(TexColor.a - 0.1f);
		}
	}


	// -------------------法线贴图--------------------
	float3 NormalMapSample = NormalMap.Sample(LinearSampler , input.Tex).xyz;

	// 根据法线贴图扰动法线
	float3 BumpNormal = NormalSampleToWorldSpace(NormalMapSample , input.NormalW , input.TangentW);

	float4 color = TexColor;

	float4 ambient = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 diffuse = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 specular = float4(0.0f , 0.0f , 0.0f , 0.0f);

	float3 shadow = float3(1.0f , 1.0f , 1.0f);
	shadow[0] = CalcShadowFactor(ShadowSampler , ShadowMap , input.ShadowPosH);

	[unroll]
	for(int i = 0; i < 3; i++)
	{
		float4 A , D , S;

		ComputeDirectionalLight(Mat ,
								Light[i] , 
								BumpNormal , 
								toEye , 
								A , 
								D , 
								S);

		ambient += A;
		diffuse += shadow[i] * D;
		specular += shadow[i] * S;
	}

	color = TexColor * (ambient + diffuse) + specular;

	if(bEnabledReflect)
	{
		float3 incident = -toEye;
		float3 reflectionVector = reflect(incident , BumpNormal);
		float4 reflectionColor = SkyboxTexture.Sample(LinearSampler , reflectionVector);

		color += Mat.Reflect * reflectionColor;
	}

	color.a = Mat.DiffuseMaterial.a * TexColor.a;

	return color;
}