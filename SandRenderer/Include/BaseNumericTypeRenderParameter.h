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
			获取标识符，只有当参数被写入数据时，才会发生改变
		*/
		unsigned int GetValueID();

	protected:
		// 标识是否改变，主要用于constant buffer判断数据是否有更新
		unsigned int m_IdentifierChange;
	};
}

#endif