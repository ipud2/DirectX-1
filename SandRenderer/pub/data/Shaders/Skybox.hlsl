cbuffer SkyBoxTransform
{
	matrix WorldViewProjMatrix;
};

TextureCube SkyboxTexture;
SamplerState SkyboxSampler;

struct VertexIn
{
	float3 PosL 	:	POSITION;
};

struct PixelIn
{
	float4 PosH	:	SV_POSITION;
	float3 PosL :	POSITION;
};

PixelIn VSMain(VertexIn input)
{
	PixelIn output;

	output.PosH = mul(float4(input.PosL , 1.0f) , WorldViewProjMatrix).xyww;
	output.PosL = input.PosL;

	return output;
}

float4 PSMain(PixelIn input) : SV_Target
{
	return SkyboxTexture.Sample(SkyboxSampler , input.PosL);
}