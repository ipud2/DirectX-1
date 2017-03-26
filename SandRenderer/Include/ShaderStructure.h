#ifndef ShaderStructure_h
#define ShaderStructure_h

#include "PCH.h"
#include "StringUtil.h"
#include "BaseNumericTypeRenderParameter.h"

namespace Sand
{
	/*
		struct VertexIn
		{
			float3 PosL		:	POSITION;
			float2 Tex		:	TEXCOORD;
			float3 NormalL	:	NORMAL;
		};

		struct VertexOut
		{
			float4 PosH		:	SV_POSITION;
			float3 PosW		:	POSITION;
			float2 Tex		:	TEXCOORD;
			float3 NormalW	:	NORMAL;
		};

		cbuffer Transform
		{
			float4x4 World;
			float4x4 WorldViewProj;
			float4x4 WorldInvTranspose;
			float4x4 TexTransform;
		};

		// 我承认，这部分是强行加入。。。
		Texture2D DiffuseMap;
		SamplerState SampleLinear;

		VertexOut main( VertexIn input )
		{
			VertexOut output;

			output.PosH = mul(float4(input.PosL , 1.0f) , WorldViewProj);
			output.PosW = mul(float4(input.PosL , 1.0f) , World).xyz;
			output.Tex = mul(float4(input.Tex , 0.0f , 1.0f) , TexTransform).xy;
			output.NormalW = mul(input.NormalL , (float3x3)WorldInvTranspose);

			return output;
		};

		shader中数据分为以下几部分：
		输入字段 ： 用于描述VertexIn
		输出字段	:  用于描述VertexOut
		绑定的资源 : 如上面的DiffuseMap , SamplerLinear , Transform
		cbuffer组成（cbuffer是个结构体，内部由多种数据） : 描述CBuffer的构成，如上面的Transform是由哪些组成的
	*/

	enum ShaderMask
	{
		SM_VERTEX_SHADER = 0x0001 ,
		SM_HULL_SHADER = 0x0002 ,
		SM_DOMAIN_SHADER = 0x0004 ,
		SM_GEOMETRY_SHADER = 0x0008 ,
		SM_PIXEL_SHADER = 0x0010 , 
		SM_COMPUTE_SHADER = 0x0020
	};

	// shader类型
	enum ShaderType
	{
		ST_VERTEX_SHADER ,
		ST_HULL_SHADER ,
		ST_DOMAIN_SHADER ,
		ST_GEOMETRY_SHADER ,
		ST_PIXEL_SHADER ,
		ST_COMPUTE_SHADER
	};

	// 用于描述资源是如何绑定到shader上
	struct ShaderInputBindDesc
	{
		// 封装了D3D11_SHADER_INPUT_BIND_DESC
		ShaderInputBindDesc( D3D11_SHADER_INPUT_BIND_DESC desc )
		{
			Name = std::wstring( StringUtil::ToUnicode( std::string( desc.Name ) ) );
			Type = desc.Type;
			BindPoint = desc.BindPoint;
			BindCount = desc.BindCount;
			uFlags = desc.uFlags;
			ReturnType = desc.ReturnType;
			Dimension = desc.Dimension;
			NumSamples = desc.NumSamples;
			pParamRef = nullptr;
		};

		// 默认构造函数
		ShaderInputBindDesc()
		{
			Name = std::wstring( L"" );
			Type = D3D_SIT_CBUFFER;
			BindPoint = 0;
			BindCount = 0;
			uFlags = 0;
			ReturnType = D3D11_RETURN_TYPE_UNORM;
			Dimension = D3D_SRV_DIMENSION_UNKNOWN;
			NumSamples = 0;
			pParamRef = nullptr;
		};

		std::wstring Name;							// shader资源名
		D3D_SHADER_INPUT_TYPE Type;					// 指定资源类型
		UINT BindPoint;								// 开始绑定点
		UINT BindCount;								// 对于数组而言连续绑定的slot数
		UINT uFlags;
		D3D11_RESOURCE_RETURN_TYPE ReturnType;		// 假如输入为纹理，则该值定义了返回类型
		D3D11_SRV_DIMENSION Dimension;				// 定义了绑定资源的维度
		UINT NumSamples;							// 对于多重采样纹理的采样数，纹理没有进行多重采样，该值为-1
		RenderParameter* pParamRef;
	};

	struct ConstantBufferDesc
	{
		D3D11_SHADER_BUFFER_DESC Description;
		std::vector<D3D11_SHADER_VARIABLE_DESC> Variables;
		std::vector<D3D11_SHADER_TYPE_DESC> Types;
		std::vector<BaseNumericTypeRenderParameter*> Parameters;

		RenderParameter* pParamRef;					// Constant Buffer保存一个参数对象指针
	};
};
#endif