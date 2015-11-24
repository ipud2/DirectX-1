// 变换矩阵
cbuffer Transforms
{
	matrix WorldMatrix;
	matrix ViewProjMatrix;
};

// 细分因子
cbuffer TessellationParameters
{
	float4 EdgeFactors;
};

cbuffer RenderingParameters
{
	float4 FinalColor = float4(1.0f , 0.0f , 0.0f , 1.0f);
};

struct VertexIn
{
	float3 position 	:	POSITION;
};

struct VertexOut
{
	float3 WorldPosition	:	POSITION;
};

// 控制点
struct HS_CONTROL_POINT_OUTPUT
{
	float3 WorldPosition	:	POSITION;
};

// 细分参数
struct HS_CONSTANT_DATA_OUTPUT
{
	float Edges[3]		:	SV_TessFactor;
	float Inside		:	SV_InsideTessFactor;
};

struct DS_OUTPUT
{
	float4 Position 	:	SV_Position;
};

// ------------------Vertex Shader----------------------
VertexOut VSMAIN(in VertexIn input)
{
	VertexOut output;

	output.WorldPosition = mul(float4(input.position , 1.0f) , WorldMatrix).xyz;

	return output;
}

// --------------------Hull Shader-------------------------
HS_CONSTANT_DATA_OUTPUT PassThroughConstantHS(InputPatch<VertexOut , 3> ip , uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT output;

	output.Edges[0] = EdgeFactors.x;
	output.Edges[1] = EdgeFactors.y;
	output.Edges[2] = EdgeFactors.z;

	output.Inside = EdgeFactors.w;

	return output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PassThroughConstantHS")]
HS_CONTROL_POINT_OUTPUT HSMAIN(InputPatch<VertexOut , 3> ip , 
								uint i : SV_OutputControlPointID , 
								uint PatchID : SV_PrimitiveID)
{
	HS_CONTROL_POINT_OUTPUT output;

	output.WorldPosition = ip[i].WorldPosition;

	return output;
}

// -----------------------Domain Shader---------------------------
[domain("tri")]
DS_OUTPUT DSMAIN(const OutputPatch<HS_CONTROL_POINT_OUTPUT , 3> TrianglePatch ,
					float3 BarycentricCoordinates : SV_DomainLocation , 
					HS_CONSTANT_DATA_OUTPUT input)
{
	DS_OUTPUT output;

	float3 vWorldPos = BarycentricCoordinates.x * TrianglePatch[0].WorldPosition + BarycentricCoordinates.y * TrianglePatch[1].WorldPosition + BarycentricCoordinates.z * TrianglePatch[2].WorldPosition;

	output.Position = mul(float4(vWorldPos.xyz , 1.0f) , ViewProjMatrix);

	return output;
}

// --------------------Pixel Shader------------------
float4 PSMAIN(in DS_OUTPUT input) : SV_Target
{
	float4 color = FinalColor;

	return color;
}