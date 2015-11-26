cbuffer Transforms
{
	matrix WorldViewProjMatrix;
	matrix TexTransform;
};

SamplerState LinearSampler;
Texture2D WoodCrateTexture;

struct VertexIn
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct PixelIn
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

PixelIn VSMain(in VertexIn input)
{
	PixelIn output = (PixelIn)0;

	output.Pos = mul(float4(input.Pos , 1.0f) , WorldViewProjMatrix);
	output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransform).xy;

	return output;
}

float4 PSMain(in PixelIn input) : SV_Target
{
	float4 color = WoodCrateTexture.Sample(LinearSampler , input.Tex);

	return color;
}