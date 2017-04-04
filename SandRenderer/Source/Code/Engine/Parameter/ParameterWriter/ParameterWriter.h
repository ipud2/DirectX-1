#ifndef ParameterWriter_h
#define ParameterWriter_h

#include "Engine/Parameter/Parameters/BaseClass/RenderParameter.h"
#include "Engine/Parameter/Parameters/BaseClass/BaseNumericTypeRenderParameter.h"
#include "Engine/Parameter/IParameterManager.h"

namespace Sand
{
	class ParameterWriter
	{
	public:
		ParameterWriter();
		virtual ~ParameterWriter();

		virtual RenderParameter* GetRenderParameterRef() = 0;

		/*
			After Set Value
			We need call the function to Update Value of Parameter
		*/
		virtual void UpdateValueToParameter( IParameterManager* pParamMgr ) = 0;

		/*
			Set Current Value to Parameter
		*/
		virtual void InitializeParameter() = 0;
	};
};
#endif