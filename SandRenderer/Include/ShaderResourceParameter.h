#ifndef ShaderResourceParameter_h
#define ShaderResourceParameter_h

#include "RenderParameter.h"

namespace Sand
{
	class ShaderResourceParameter : public RenderParameter
	{
	public:
		ShaderResourceParameter();
		ShaderResourceParameter( ShaderResourceParameter& copy );
		virtual ~ShaderResourceParameter();

		virtual void SetParameter( void * pData );

		virtual const ParameterType GetParameterType();

		int GetValue();

	protected:
		int m_iShaderResourceID;
	};
}

#endif