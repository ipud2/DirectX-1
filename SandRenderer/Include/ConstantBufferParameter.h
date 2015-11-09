#ifndef ConstantBufferParameter_h
#define ConstantBufferParameter_h

#include "RenderParameter.h"

namespace Sand
{
	class ConstantBufferParameter : public RenderParameter
	{
	public:
		ConstantBufferParameter();
		ConstantBufferParameter( ConstantBufferParameter& copy );
		virtual ~ConstantBufferParameter();

		virtual void SetParameter( void * pData );

		virtual const ParameterType GetParameterType();

		int GetValue();

	protected:
		int m_iConstantBufferID;
	};
};
#endif