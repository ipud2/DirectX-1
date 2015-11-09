#ifndef SamplerParameter_h
#define SamplerParameter_h

#include "RenderParameter.h"

namespace Sand
{
	class SamplerParameter : public RenderParameter
	{
	public:
		SamplerParameter();
		SamplerParameter( SamplerParameter& copy );
		virtual ~SamplerParameter();

		virtual void SetParameter( void * pData );

		virtual const ParameterType GetParameterType();

		int GetValue();

	protected:
		int m_iSamplerID;
	};
};
#endif