#ifndef ShaderResourceParameter_h
#define ShaderResourceParameter_h

#include "Engine/Parameter/Parameters/BaseClass/RenderParameter.h"

namespace Sand
{
	class ShaderResourceParameter : public RenderParameter
	{
	public:
		ShaderResourceParameter( std::wstring name );
		ShaderResourceParameter( ShaderResourceParameter& copy );
		virtual ~ShaderResourceParameter();

		virtual void SetParameterData( void * pData );

		virtual const ParameterType GetParameterType();

		int GetResourceViewID();

	protected:
		int m_iShaderResourceID;
	};
}

#endif