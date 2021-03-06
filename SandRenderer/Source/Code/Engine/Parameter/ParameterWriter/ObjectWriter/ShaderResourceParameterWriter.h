#ifndef ShaderResourceParameterWriter_h
#define ShaderResourceParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"

namespace Sand
{
	class ShaderResourceParameterWriter : public ParameterWriter
	{
	public:
		ShaderResourceParameterWriter();
		virtual ~ShaderResourceParameterWriter();

		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		virtual RenderParameter* GetRenderParameterRef();

		void SetRenderParameterRef( ShaderResourceParameter* pParamRef );
		void SetValue( ResourceProxyPtr value );

	protected:
		ShaderResourceParameter* m_pParameter;

		ResourceProxyPtr m_Value;
	};
}

#endif