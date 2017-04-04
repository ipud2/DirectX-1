#ifndef ParameterContainer_h
#define ParameterContainer_h

#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/ObjectWriter/ConstantBufferParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/ObjectWriter/ShaderResourceParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/ObjectWriter/UnorderedAccessParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/ObjectWriter/SamplerParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/ScalarWriter/BoolParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/ScalarWriter/FloatParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/VectorWriter/Vector4fParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/VectorWriter/Vector3fParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/VectorWriter/Vector2fParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/MatrixWriter/MatrixParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/MatrixWriter/MatrixArrayParameterWriter.h"
#include "Engine/Parameter/ParameterWriter/StructWriter/StructureParameterWriter.h"

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
		BoolParameterWriter* GetBoolParameterWriter( const std::wstring& name );
		FloatParameterWriter* GetFloatParameterWriter( const std::wstring& name );
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