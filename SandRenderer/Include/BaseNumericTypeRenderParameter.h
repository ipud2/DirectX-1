#ifndef BaseNumericTypeRenderParameter_h
#define BaseNumericTypeRenderParameter_h

#include "RenderParameter.h"

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
		unsigned int GetValueID();

	protected:
		// ��ʶ�Ƿ�ı䣬��Ҫ����constant buffer�ж������Ƿ��и���
		unsigned int m_IdentifierChange;
	};
}

#endif