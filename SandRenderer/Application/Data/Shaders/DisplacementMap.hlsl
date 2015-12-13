#include "LightHelper.hlsli"

cbuffer cbDisplacementTransform
{
	matrix WorldMatrix;
	matrix WorldInvTransposeMatrix;
	matrix TexTransformMatrix;
};

cbuffer cbDisplacementConstant
{
	DirectionalLight Light[3];

	float MaxTessDistance;
	float MinTessDistance;
	float MinTessFactor;
	float MaxTessFactor;
	float HeightScale;
};

cbuffer cbDisplacementPos
{
	float3 ViewPosition;
	matrix ViewProjMatrix;
};

cbuffer cbDisplacementMaterial
{
	Material Mat;
	bool bUseTexture = true;
	bool bAlphaClip = true;
	bool bEnabledReflect = false;
};

SamplerState LinearSampler;
TextureCube SkyboxTexture;
Texture2D DiffuseTexture;
Texture2D NormalMap;

struct VertexIn
{
	float3 PosL 	:	POSITION;
	float3 NormalL 	:	NORMAL;
	float2 Tex 		:	TEXCOORD;
	float3 TangentL :	TANGENT;
};

struct VertexOut
{
	float3 PosW 	:	POSITION;
	float3 NormalW	:	NORMAL;
	float3 TangentW	:	TANGENT;
	float2 Tex 		:	TEXCOORD;
	float TessFactor : 	TESS;
};

struct HullShaderControlPointOutput
{
	float3 PosW 	:	POSITION;
	float3 NormalW	:	NORMAL;
	float3 TangentW	:	TANGENT;
	float2 Tex 		:	TEXCOORD;
};

struct PatchTess
{
	float EdgeTessFactor[3] 	:	SV_TessFactor;
	float InsideTessFactor		:	SV_InsideTessFactor;
};

struct DomainOutput
{
	float4 PosH		:	SV_POSITION;
	float3 PosW 	: 	POSITION;
	float3 NormalW 	:	NORMAL;
	float3 TangentW	:	TANGENT;
	float2 Tex 		:	TEXCOORD;
};

#define NUM_CONTROL_POINTS 3

VertexOut VSMain(VertexIn input)
{
	VertexOut output;

	output.PosW = mul(float4(input.PosL , 1.0f) , WorldMatrix).xyz;

	output.NormalW = mul(input.NormalL , (float3x3)WorldInvTransposeMatrix);

	output.TangentW = mul(input.TangentL , (float3x3)WorldMatrix);

	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransformMatrix).xy;

	float dist = distance(output.PosW , ViewPosition);

	float tess = saturate( ( MinTessDistance - dist ) / ( MinTessDistance - MaxTessDistance ) );

	output.TessFactor = MinTessFactor + tess * (MaxTessFactor - MinTessFactor);

	return output;
}

PatchTess CalcHSPatchConstants(InputPatch<VertexOut , NUM_CONTROL_POINTS> patch , uint PatchID : SV_PrimitiveID)
{
	PatchTess Output;

	/*				0
					/\
				   /  \
				 2/    \1
				 /      \
			   1/________\2
					0
	*/
	Output.EdgeTessFactor[0] = 0.5f * (patch[1].TessFactor + patch[2].TessFactor);
	Output.EdgeTessFactor[1] = 0.5f * (patch[0].TessFactor + patch[2].TessFactor);
	Output.EdgeTessFactor[2] = 0.5f * (patch[0].TessFactor + patch[1].TessFactor);

	Output.InsideTessFactor = Output.EdgeTessFactor[0];	

	return Output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HullShaderControlPointOutput HSMain(InputPatch<VertexOut , NUM_CONTROL_POINTS> p , 
									uint i : SV_OutputControlPointID , 
									uint PatchID : SV_PrimitiveID)
{
	HullShaderControlPointOutput Output;

	Output.PosW 	= p[i].PosW;
	Output.NormalW 	= p[i].NormalW;
	Output.TangentW = p[i].TangentW;
	Output.Tex 		= p[i].Tex;

	return Output;
}

[domain("tri")]
DomainOutput DSMain(PatchTess input , 
					float3 domain : SV_DomainLocation , 
					const OutputPatch<HullShaderControlPointOutput , NUM_CONTROL_POINTS> patch)
{
	DomainOutput Output;

	Output.PosW 	= 	domain.x * patch[0].PosW 		+ domain.y * patch[1].PosW 		+ domain.z * patch[2].PosW;
	Output.NormalW 	= 	domain.x * patch[0].NormalW 	+ domain.y * patch[1].NormalW 	+ domain.z * patch[2].NormalW;
	Output.TangentW = 	domain.x * patch[0].TangentW 	+ domain.y * patch[1].TangentW 	+ domain.z * patch[2].TangentW;
	Output.Tex 		= 	domain.x * patch[0].Tex 		+ domain.y * patch[1].Tex 		+ domain.z * patch[2].Tex;

	// 归一化法线
	Output.NormalW = normalize(Output.NormalW);

	//根据距离选择mipmap等级，距离越远，所需细节越少，因此选择mipmap大的级别
	//可以加快渲染速度
	const float MipInterval = 20.0f;
	float mipLevel = clamp( ( distance( Output.PosW , ViewPosition ) - MipInterval ) / MipInterval , 0.0f , 6.0f);

	//偏移的高度保存在透明通道中
	float h = NormalMap.SampleLevel(LinearSampler , Output.Tex , mipLevel).a;

	//沿着法线的方向偏移顶点，从几何的角度使其发生凹凸感
	Output.PosW += (HeightScale * (h - 1.0f)) * Output.NormalW;

	Output.PosH = mul(float4(Output.PosW , 1.0f) , ViewProjMatrix);

	return Output;
}

float4 PSMain(DomainOutput input) : SV_Target
{
	input.NormalW = normalize(input.NormalW);

	float3 toEye = ViewPosition - input.PosW;

	float dist = length(toEye);

	toEye /= dist;

	float4 texColor = float4(1.0f , 1.0f , 1.0f , 1.0f);
	if(bUseTexture)
	{
		texColor = DiffuseTexture.Sample(LinearSampler , input.Tex);

		if(bAlphaClip)
		{
			clip(texColor.a - 0.1f);
		}
	}

	float3 NormalMapSample = NormalMap.Sample(LinearSampler , input.Tex).xyz;
	float3 BumpNormal = NormalSampleToWorldSpace(NormalMapSample , input.NormalW , input.TangentW);

	float4 color = texColor;

	float4 ambient = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 diffuse = float4(0.0f , 0.0f , 0.0f , 0.0f);
	float4 specular = float4(0.0f , 0.0f , 0.0f , 0.0f);

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
		diffuse += D;
		specular += S;
	}

	color = texColor * (ambient + diffuse) + specular;

	if(bEnabledReflect)
	{
		float3 incident = -toEye;
		float3 ReflectionVector = reflect(incident , BumpNormal);

		float4 ReflectionColor = SkyboxTexture.Sample(LinearSampler , ReflectionVector);

		color += Mat.Reflect * ReflectionColor;
	}

	color.a = Mat.DiffuseMaterial.a * texColor.a;

	return color;
}