#ifndef SamplerParameter_h
#define SamplerParameter_h

#include "Engine/Parameter/Parameters/BaseClass/RenderParameter.h"

namespace Sand
{
	class SamplerParameter : public RenderParameter
	{
	public:
		SamplerParameter( std::wstring name );
		SamplerParameter( SamplerParameter& copy );
		virtual ~SamplerParameter();

		virtual void SetParameterData( void * pData );

		virtual const ParameterType GetParameterType();

		int GetSamplerResourceID();

	protected:
		int m_iSamplerID;
	};
};
#endif