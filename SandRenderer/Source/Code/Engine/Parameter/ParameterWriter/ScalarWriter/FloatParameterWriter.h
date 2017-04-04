#ifndef FloatParameterWriter_h
#define FloatParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"
#include "Engine/Parameter/Parameters/Numeric/Scalar/FloatParameter.h"

namespace Sand
{
	class FloatParameterWriter : public ParameterWriter
	{
	public:
		FloatParameterWriter();
		virtual ~FloatParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();

		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );

		/*
		将当前的Value设置到Parameter中
		*/
		virtual void InitializeParameter();

		void SetValue( const float& value );
		float GetValue();

		void SetRenderParameterRef( FloatParameter* pParam );

	protected:
		float m_Value;
		FloatParameter* m_pParameter;
	};
};
#endif