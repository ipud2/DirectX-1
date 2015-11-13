#ifndef UnorderedAccessParameter_h
#define UnorderedAccessParameter_h

#include "RenderParameter.h"

namespace Sand
{
	class UnorderedAccessParameter : public RenderParameter
	{
	public:
		UnorderedAccessParameter( std::wstring name );
		UnorderedAccessParameter( UnorderedAccessParameter& copy );
		virtual ~UnorderedAccessParameter();

		virtual void SetParameterData( void * pData );

		virtual const ParameterType GetParameterType();

		int GetResourceViewID();

	protected:
		int m_iUnorderedAccessID;
	};
};
#endif