#ifndef StructureParameter_h
#define StructureParameter_h

#include "BaseNumericTypeRenderParameter.h"

namespace Sand
{
	class StructureParameter : public BaseNumericTypeRenderParameter
	{
	public:
		StructureParameter( std::wstring name , int size );
		StructureParameter( StructureParameter& copy );
		virtual ~StructureParameter();

		/*
			�����µľ���ֵ�����µ�ֵ��ԭ����ֵ��һ�������ı��ʶ��
		*/
		virtual void SetParameterData( void * pData );

		/*
			��ȡ��������
		*/
		virtual const ParameterType GetParameterType();

		char* GetStructureData();
		int GetStructureSize();

	protected:
		char *m_pData;

		// �ṹ����ܴ�С����Ϊ�ṹ�����飬��Ϊ��������ܴ�С
		int m_Size;
	};
};
#endif