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

		// �ҳ��ϣ��ⲿ����ǿ�м��롣����
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

		shader�����ݷ�Ϊ���¼����֣�
		�����ֶ� �� ��������VertexIn
		����ֶ�	:  ��������VertexOut
		�󶨵���Դ : �������DiffuseMap , SamplerLinear , Transform
		cbuffer��ɣ�cbuffer�Ǹ��ṹ�壬�ڲ��ɶ������ݣ� : ����CBuffer�Ĺ��ɣ��������Transform������Щ��ɵ�
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

	// shader����
	enum ShaderType
	{
		ST_VERTEX_SHADER ,
		ST_HULL_SHADER ,
		ST_DOMAIN_SHADER ,
		ST_GEOMETRY_SHADER ,
		ST_PIXEL_SHADER ,
		ST_COMPUTE_SHADER
	};

	// ����������Դ����ΰ󶨵�shader��
	struct ShaderInputBindDesc
	{
		// ��װ��D3D11_SHADER_INPUT_BIND_DESC
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

		// Ĭ�Ϲ��캯��
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

		std::wstring Name;							// shader��Դ��
		D3D_SHADER_INPUT_TYPE Type;					// ָ����Դ����
		UINT BindPoint;								// ��ʼ�󶨵�
		UINT BindCount;								// ����������������󶨵�slot��
		UINT uFlags;
		D3D11_RESOURCE_RETURN_TYPE ReturnType;		// ��������Ϊ�������ֵ�����˷�������
		D3D11_SRV_DIMENSION Dimension;				// �����˰���Դ��ά��
		UINT NumSamples;							// ���ڶ��ز�������Ĳ�����������û�н��ж��ز�������ֵΪ-1
		RenderParameter* pParamRef;
	};

	struct ConstantBufferDesc
	{
		D3D11_SHADER_BUFFER_DESC Description;
		std::vector<D3D11_SHADER_VARIABLE_DESC> Variables;
		std::vector<D3D11_SHADER_TYPE_DESC> Types;
		std::vector<BaseNumericTypeRenderParameter*> Parameters;

		RenderParameter* pParamRef;					// Constant Buffer����һ����������ָ��
	};
};
#endif