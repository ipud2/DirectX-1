cbuffer Transforms
{
	matrix WorldViewProjMatrix;
};
							
struct VertexIn
{
	float4 Position : 	POSITION;
	float4 Color 	:	COLOR;
};

struct VertexOut
{
	float4 Position 	: SV_POSITION;
	float4 Color 		: COLOR;
};

struct GeometryInputAndOutput
{
	float4 Position : SV_POSITION;
	float4 Color	: COLOR;
};

VertexOut VSMain(in VertexIn input)
{
	VertexOut output = (VertexOut)0;

	output.Position = input.Position;
	output.Color = input.Color;

	return output;
}

[maxvertexcount(3)]
void GSMain(triangle GeometryInputAndOutput input[3] , inout TriangleStream<GeometryInputAndOutput> TriangleOutputStream)
{
	GeometryInputAndOutput output;

	float3 faceEdgeA = input[1].Position.xyz - input[0].Position.xyz;
	float3 faceEdgeB = input[2].Position.xyz - input[0].Position.xyz;
	float3 faceNormal = normalize(cross(faceEdgeA , faceEdgeB));

	for(int i = 0; i < 3; i++)
	{
		// 沿着法线方向移动，即向外平移
		float4 position = input[i].Position + float4(faceNormal / 4 , 0);

		output.Position = mul(position , WorldViewProjMatrix);

		output.Color = input[i].Color;

		TriangleOutputStream.Append(output);
	}
}

float4 PSMain(in GeometryInputAndOutput input) : SV_Target
{
	float4 color = input.Color;

	return color;
}