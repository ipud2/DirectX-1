#ifndef UnorderedAccessParameterWriter_h
#define UnorderedAccessParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"

namespace Sand
{
	class UnorderedAccessParameterWriter : public ParameterWriter
	{
	public:
		UnorderedAccessParameterWriter();
		virtual ~UnorderedAccessParameterWriter();

		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		virtual RenderParameter* GetRenderParameterRef();

		void SetRenderParameterRef( UnorderedAccessParameter* pParam );
		void SetValue( ResourceProxyPtr Value );
		void SetInitCount( int Count );

	protected:
		RenderParameter* m_pParameter;
		ResourceProxyPtr m_Value;
		int m_iCount;
	};
}
#endif