#ifndef ParameterContainer_h
#define ParameterContainer_h

#include "PCH.h"
#include "ConstantBufferParameterWriter.h"
#include "ShaderResourceParameterWriter.h"
#include "UnorderedAccessParameterWriter.h"
#include "SamplerParameterWriter.h"
#include "Vector4fParameterWriter.h"
#include "Vector3fParameterWriter.h"
#include "Vector2fParameterWriter.h"
#include "MatrixParameterWriter.h"
#include "MatrixArrayParameterWriter.h"
#include "StructureParameterWriter.h"

namespace Sand
{
	class ParameterContainer
	{
	public:
		ParameterContainer();
		virtual ~ParameterContainer();

		// ���һ��������container��
		void AddRenderParameter( ParameterWriter* pWriter );

		/*
			��ȡָ�����ֵ�ParameterWriter����
			�������ڣ��򴴽�
		*/
		ParameterWriter* GetRenderParameterWriter( const std::wstring& name );
		Vector4fParameterWriter* GetVector4fParameterWriter( const std::wstring& name );
		Vector3fParameterWriter* GetVector3fParameterWriter( const std::wstring& name );
		Vector2fParameterWriter* GetVector2fParameterWriter( const std::wstring& name );
		MatrixParameterWriter* GetMatrixParameterWriter( const std::wstring& name );
		MatrixArrayParameterWriter* GetMatrixArrayParameterWriter( const std::wstring& name , int count );
		StructureParameterWriter* GetStructureParameterWriter( const std::wstring& name , int Size );
		UnorderedAccessParameterWriter* GetUnorderedAccessParameterWriter( const std::wstring& name );
		ShaderResourceParameterWriter* GetShaderResourceParameterWriter( const std::wstring& name );
		ConstantBufferParameterWriter* GetConstantBufferParameterWriter( const std::wstring& name );
		SamplerParameterWriter* GetSamplerParameterWriter( const std::wstring& name );

		/*
			���ܣ���Container�е�����Writer��value��Ӧ�õ���Parameter��ȥ
			���������е���Ⱦ����

			ֻ����Ҫ���µ����ݲŻᴴ��ParameterWriter����������ӵ�Container��
			����ͨ��SetXXXParameter��������Ӧ����ֵ��Ҫ���µ�ֵ
			���ͨ��SetRenderParams����Щ���²���ֵӦ�õ�������
		*/
		void UpdateRenderParam( IParameterManager* pParameterManager );
		void InitRenderParams();

	protected:
		std::vector<ParameterWriter*> m_RenderParameter;
	};
}

#endif