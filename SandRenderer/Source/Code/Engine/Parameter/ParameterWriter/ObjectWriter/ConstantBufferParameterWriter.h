#ifndef ConstantBufferParameterWriter_h
#define ConstantBufferParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"

namespace Sand
{
	class ConstantBufferParameterWriter : public ParameterWriter
	{
	public:
		ConstantBufferParameterWriter();
		virtual ~ConstantBufferParameterWriter();

		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		virtual RenderParameter* GetRenderParameterRef();

		void SetRenderParameterRef( ConstantBufferParameter* pParam );
		void SetValue( ResourceProxyPtr Value );

	protected:
		ConstantBufferParameter* m_pParameter;
		ResourceProxyPtr m_Value;
	};
};
#endif