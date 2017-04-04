#ifndef SamplerParameterWriter_h
#define SamplerParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"

namespace Sand
{
	class SamplerParameterWriter : public ParameterWriter
	{
	public:
		SamplerParameterWriter();
		virtual ~SamplerParameterWriter();

		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
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