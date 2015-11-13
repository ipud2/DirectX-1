#ifndef ParameterWriter_h
#define ParameterWriter_h

#include "RenderParameter.h"
#include "BaseNumericTypeRenderParameter.h"
#include "IParameterManager.h"

namespace Sand
{
	class ParameterWriter
	{
	public:
		ParameterWriter();
		virtual ~ParameterWriter();

		virtual RenderParameter* GetRenderParameterRef() = 0;

		virtual void WriteParameter( IParameterManager* pParamMgr ) = 0;

		virtual void InitializeParameter() = 0;
	};
};
#endif