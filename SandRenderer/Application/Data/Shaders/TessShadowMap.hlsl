cbuffer cbTransform
{
	matrix WorldMatrix;
	matrix WorldInvTransposeMatrix;
	matrix TexTransformMatrix;
};

cbuffer cbTess
{
	float MaxTessDistance;
	float MinTessDistance;
	float MinTessFactor;
	float MaxTessFactor;

	float HeightScale;
};

cbuffer cbView
{
	matrix ViewProjMatrix;
	float3 ViewPosition;		//正常渲染时的视点位置
};

Texture2D DiffuseTexture;
Texture2D NormalMap;
SamplerState LinearSampler;

struct VertexIn
{
	float3 PosL 	:	POSITION;
	float3 NormalL 	:	NORMAL;
	float2 Tex 		:	TEXCOORD;
};

struct VertexOut
{
	float3 PosW 	:	POSITION;
	float3 NormalW 	:	NORMAL;
	float2 Tex 		:	TEXCOORD;
	float TessFactor:	TESS;
};

struct HullOut
{
	float3 PosW		:	POSITION;
	float3 NormalW	:	NORMAL;
	float2 Tex 		:	TEXCOORD;
};

struct PatchTess
{
	float EdgeTessFactor[3]	:	SV_TessFactor;
	float InsideTessFactor	:	SV_InsideTessFactor;
};

struct DomainOut
{
	float4 PosH		:	SV_POSITION;
	float3 PosW		:	POSITION;
	float3 NormalW	:	NORMAL;
	float2 Tex 		:	TEXCOORD;
};

#define NUM_CONTROL_POINTS	3

VertexOut VSMain(VertexIn input)
{
	VertexOut output;

	output.PosW = mul(float4(input.PosL , 1.0f) , WorldMatrix).xyz;
	output.NormalW = mul(input.NormalL , (float3x3)WorldInvTransposeMatrix);
	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransformMatrix).xy;

	float d= distance(ViewPosition , output.PosW);
	float tess = saturate((MinTessDistance - d) / (MinTessDistance - MaxTessDistance));
	output.TessFactor = MinTessFactor + tess * (MaxTessFactor - MinTessFactor);

	return output;
}

PatchTess CalcHSPatchConstants(
	InputPatch<VertexOut , NUM_CONTROL_POINTS> patch , uint PatchID : SV_PrimitiveID)
{
	PatchTess Output;

	Output.EdgeTessFactor[0] = 0.5f * (patch[1].TessFactor + patch[2].TessFactor);
	Output.EdgeTessFactor[1] = 0.5f * (patch[0].TessFactor + patch[2].TessFactor);
	Output.EdgeTessFactor[2] = 0.5f * (patch[2].TessFactor + patch[0].TessFactor);

	Output.InsideTessFactor = Output.EdgeTessFactor[0];

	return Output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HullOut HSMain(InputPatch<VertexOut , NUM_CONTROL_POINTS> patch , 
			uint i : SV_OutputControlPointID , 
			uint PatchID : SV_PrimitiveID)
{
	HullOut Output;

	Output.PosW 	= patch[i].PosW;
	Output.NormalW 	= patch[i].NormalW;
	Output.Tex 		= patch[i].Tex;

	return Output;
}

[domain("tri")]
DomainOut DSMain(PatchTess input , 
				float3 domain : SV_DomainLocation , 
				const OutputPatch<HullOut , NUM_CONTROL_POINTS> patch)
{
	DomainOut Output;

	Output.PosW 	= domain.x * patch[0].PosW 		+ domain.y * patch[1].PosW 		+ domain.z * patch[2].PosW;
	Output.NormalW 	= domain.x * patch[0].NormalW 	+ domain.y * patch[1].NormalW 	+ domain.z * patch[2].NormalW;
	Output.Tex 		= domain.x * patch[0].Tex 		+ domain.y * patch[1].Tex 		+ domain.z * patch[2].Tex;

	Output.NormalW = normalize(Output.NormalW);

	float MipInterval = 20.0f;
	float dist = distance(Output.PosW , ViewPosition);
	float mipLevel = clamp((dist - MipInterval) / MipInterval , 0.0f , 6.0f);
	float h = NormalMap.SampleLevel(LinearSampler , Output.Tex , mipLevel).a;

	Output.PosW += (HeightScale * (h - 1.0f) * Output.NormalW);

	Output.PosH = mul(float4(Output.PosW , 1.0f) , ViewProjMatrix);

	return Output;
}

void PSMain(DomainOut input)
{
	float4 diffuse = DiffuseTexture.Sample(LinearSampler , input.Tex);

	clip(diffuse.a - 0.15f);
}