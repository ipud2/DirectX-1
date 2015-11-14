#ifndef SamplerParameterWriter_h
#define SamplerParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class SamplerParameterWriter : public ParameterWriter
	{
	public:
		SamplerParameterWriter();
		virtual ~SamplerParameterWriter();

		virtual void WriteParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();
		virtual RenderParameter* GetRenderParameterRef();

		void SetRenderParameterRef( SamplerParameter* pParamRef );
		void SetValue( int Value );

	protected:
		SamplerParameter* m_pParameter;
		int m_Value;
	};
}

#endif