#ifndef ParameterContainer_h
#define ParameterContainer_h

#include "PCH.h"
#include "ConstantBufferParameterWriter.h"
#include "ShaderResourceParameterWriter.h"
#include "UnorderedAccessParameterWriter.h"
#include "SamplerParameterWriter.h"
#include "VectorParameterWriter.h"
#include "MatrixParameterWriter.h"
#include "MatrixArrayParameterWriter.h"

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
		����name��ȡParameterWriter����
		�����ڣ������ͷ��ϣ����䷵��
		���򷵻�nullptr
		*/
		ParameterWriter* GetRenderParameterWriter( const std::wstring& name );
		VectorParameterWriter* GetVectorParameterWriter( const std::wstring& name );
		MatrixParameterWriter* GetMatrixParameterWriter( const std::wstring& name );
		MatrixArrayParameterWriter* GetMatrixArrayParameterWriter( const std::wstring& name );
		UnorderedAccessParameterWriter* GetUnorderedAccessParameterWriter( const std::wstring& name );
		ShaderResourceParameterWriter* GetShaderResourceParameterWriter( const std::wstring& name );
		ConstantBufferParameterWriter* GetConstantBufferParameterWriter( const std::wstring& name );
		SamplerParameterWriter* GetSamplerParameterWriter( const std::wstring& name );

		/*
		���ܣ�Ϊָ�����ƵĲ�����Writer����value
		name:������
		value:����Ϊname�Ĳ�����ֵ

		method:
		����name��ѯ��Ӧ��ParameterWriter
		�������ڣ����½�һ��������ӵ�Container��,Ȼ���ʼ��
		���Ѵ��ڣ���������Writer��value��Ա
		*/
		VectorParameterWriter* SetValueToVectorParameterWriter( const std::wstring& name , const Vector4f& Value );
		MatrixParameterWriter* SetValueToMatrixParameterWriter( const std::wstring& name , const Matrix4f& Value );
		MatrixArrayParameterWriter* SetValueToMatrixArrayParameterWriter( const std::wstring& name , Matrix4f* Value , int count );
		UnorderedAccessParameterWriter* SetValueToUnorderedAccessParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value );
		ShaderResourceParameterWriter* SetValueToShaderResourceParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value );
		ConstantBufferParameterWriter* SetValueToConstantBufferParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value );
		SamplerParameterWriter* SetValueToSamplerParameterWriter( const std::wstring& name , int Value );



		/*
			���ܣ���Container�е�����Writer��value��Ӧ�õ���Parameter��ȥ
			���������е���Ⱦ����

			ֻ����Ҫ���µ����ݲŻᴴ��ParameterWriter����������ӵ�Container��
			����ͨ��SetXXXParameter��������Ӧ����ֵ��Ҫ���µ�ֵ
			���ͨ��SetRenderParams����Щ���²���ֵӦ�õ�������
		*/
		void SetRenderParams( IParameterManager* pParameterManager );
		void InitRenderParams();

	protected:
		std::vector<ParameterWriter*> m_RenderParameter;
	};
}

#endif