#ifndef BaseNumericTypeRenderParameter_h
#define BaseNumericTypeRenderParameter_h

#include "Engine/Parameter/Parameters/BaseClass/RenderParameter.h"

namespace Sand
{
	class BaseNumericTypeRenderParameter : public RenderParameter
	{
	public:
		BaseNumericTypeRenderParameter( std::wstring name );
		BaseNumericTypeRenderParameter( BaseNumericTypeRenderParameter& copy );
		virtual ~BaseNumericTypeRenderParameter();

		/*
			��ȡ��ʶ����ֻ�е�������д������ʱ���Żᷢ���ı�
		*/
		unsigned int GetIdentifier();

	protected:
		// ��ʶ�Ƿ�ı䣬��Ҫ����constant buffer�ж������Ƿ��и���
		unsigned int m_Identifier;
	};
};
#endif