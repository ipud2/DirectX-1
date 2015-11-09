#ifndef UnorderedAccessParameter_h
#define UnorderedAccessParameter_h

#include "RenderParameter.h"

namespace Sand
{
	class UnorderedAccessParameter : public RenderParameter
	{
	public:
		UnorderedAccessParameter();
		UnorderedAccessParameter( UnorderedAccessParameter& copy );
		virtual ~UnorderedAccessParameter();

		virtual void SetParameter( void * pData );

		virtual const ParameterType GetParameterType();

		int GetValue();

	protected:
		int m_iUnorderedAccessID;
	};
};
#endif