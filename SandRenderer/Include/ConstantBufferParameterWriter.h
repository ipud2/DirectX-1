#ifndef ConstantBufferParameterWriter_h
#define ConstantBufferParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class ConstantBufferParameterWriter : public ParameterWriter
	{
	public:
		ConstantBufferParameterWriter();
		virtual ~ConstantBufferParameterWriter();

		virtual void WriteParameter( IParameterManager* pParamMgr );
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