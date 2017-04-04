cbuffer cbTransform
{
	matrix WorldViewProjMatrix;
	matrix TexTransformMatrix;
};

struct VertexIn
{
	float3 PosL 	:	POSITION;
	float2 Tex 		:	TEXCOORD;
};

struct VertexOut
{
	float4 PosH		:	SV_POSITION;
	float2 Tex  	:	TEXCOORD;
};

Texture2D DiffuseTexture;
SamplerState LinearSampler;

VertexOut VSMain(VertexIn input)
{
	VertexOut output;

	output.PosH = mul(float4(input.PosL , 1.0f) , WorldViewProjMatrix);
	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransformMatrix).xy;

	return output;
}

void PSMain(VertexOut input)
{
	float4 texColor = DiffuseTexture.Sample(LinearSampler , input.Tex);

	clip(texColor.a - 0.15f);
}