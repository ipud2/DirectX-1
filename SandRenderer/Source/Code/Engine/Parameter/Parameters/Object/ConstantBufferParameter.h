#ifndef ConstantBufferParameter_h
#define ConstantBufferParameter_h

#include "Engine/Parameter/Parameters/BaseClass/RenderParameter.h"

namespace Sand
{
	class ConstantBufferParameter : public RenderParameter
	{
	public:
		ConstantBufferParameter( std::wstring name );
		ConstantBufferParameter( ConstantBufferParameter& copy );
		virtual ~ConstantBufferParameter();

		virtual void SetParameterData( void * pData );

		virtual const ParameterType GetParameterType();

		int GetResourceID();

	protected:
		int m_iConstantBufferID;
	};
};
#endif