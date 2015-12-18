#include "LightHelper.hlsli"

cbuffer DirectionLight
{
	DirectionalLight Light[3];
	matrix ShadowTransformMatrix;
};

cbuffer SurfaceMaterial
{
	Material Mat;
};

cbuffer Transforms
{
	matrix WorldViewProjMatrix;
	matrix WorldMatrix;
	matrix WorldInvTransposeMatrix;
	matrix TexTransformMatrix;
};

cbuffer PhongParameter
{
	float3 ViewPosition;
};

cbuffer Effect
{
	bool bUseTexture = true;
	bool bEnabledReflect = false;
	bool bAlphaClip = true;
};

SamplerComparisonState ShadowSampler;
SamplerState LinearSampler;
Texture2D DiffuseTexture;
TextureCube SkyboxTexture;
Texture2D ShadowMap;



struct VertexIn
{
	float3 Pos 		: POSITION;
	float2 Tex 		: TEXCOORD;
	float3 Normal 	: NORMAL;
};

struct PixelIn
{
	float4 PosV 		: 	SV_POSITION;
	float3 PosW			: 	POSITION;
	float2 Tex 			: 	TEXCOORD0;
	float3 NormalW 		: 	NORMAL;
	float4 ShadowPosH	:	TEXCOORD1;
};

PixelIn VSMain(in VertexIn input)
{
	PixelIn output = (PixelIn)0;

	output.PosV = mul(float4(input.Pos , 1.0f) , WorldViewProjMatrix);
	output.PosW = mul(float4(input.Pos , 1.0f) , WorldMatrix).xyz;
	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransformMatrix).xy;
	output.NormalW = mul(input.Normal , (float3x3)WorldInvTransposeMatrix);
	output.ShadowPosH = mul(float4(input.Pos , 1.0f) , ShadowTransformMatrix);

	return output;
}

float4 PSMain(in PixelIn input) : SV_Target
{
	input.NormalW = normalize(input.NormalW);

	// 计算指向视点的向量
	float3 ToEye = ViewPosition - input.PosW;

	float dist = length(ToEye);

	ToEye /= dist;

	float4 texColor = float4(1.0f , 1.0f , 1.0f , 1.0f);

	if(bUseTexture)
	{
		texColor = DiffuseTexture.Sample(LinearSampler , input.Tex);

		if(bAlphaClip)
		{
			clip(texColor.a - 0.1f);
		}
	}

	float4 litColor = texColor;

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
								input.NormalW , 
								ToEye , 
								A , 
								D , 
								S);

		ambient += A;
		diffuse += shadow[i] * D;
		specular += shadow[i] * S;
	}
	
	litColor = texColor * (ambient + diffuse) + specular;

	if ( bEnabledReflect )
	{
		float3 incident = -ToEye;
		float3 reflectionVector = reflect( incident , input.NormalW );		//get the reflect vector about input.NormalW
		float4 reflectionColor = SkyboxTexture.Sample( LinearSampler , reflectionVector );

		litColor += Mat.Reflect * reflectionColor;
	}

	litColor.a = Mat.DiffuseMaterial.a * texColor.a;

	return litColor;
}