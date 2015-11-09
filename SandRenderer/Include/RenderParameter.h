#ifndef RenderParameter_h
#define RenderParameter_h

#include "PCH.h"

namespace Sand
{
	enum ParameterType
	{
		// ��ֵ��
		PT_VECTOR , 
		PT_MATRIX , 
		PT_MATRIX_ARRAY , 

		// ��������
		PT_SHADER_RESOURCE , 
		PT_CONSTANT_BUFFER , 
		PT_UNORDERED_ACCESS , 
		PT_SAMPLER
	};


	class RenderParameter
	{
	public:
		RenderParameter();
		RenderParameter( RenderParameter& copy );
		virtual ~RenderParameter();

		/*
			���ò�����
		*/
		void SetName( const std::wstring & name );

		/*
			��ȡ������
		*/
		std::wstring& GetName();

		/*
			��ȡ��������
		*/
		virtual const ParameterType GetParameterType() = 0;

		/*
			ʹ��pData��ʼ������
		*/
		void InitializeParameterData( void* pData );

		/*
			д�����ֵ
		*/
		virtual void SetParameterData( void* pData ) = 0;

	protected:
		std::wstring m_Name;
	};
}

#endif