#ifndef BoolParameterWriter_h
#define BoolParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"
#include "Engine/Parameter/Parameters/Numeric/Scalar/BoolParameter.h"

namespace Sand
{
	class BoolParameterWriter : public ParameterWriter
	{
	public:
		BoolParameterWriter();
		virtual ~BoolParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();

		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );

		/*
			����ǰ��Value���õ�Parameter��
		*/
		virtual void InitializeParameter();

		void SetValue( const bool& value );
		bool GetValue();

		void SetRenderParameterRef( BoolParameter* pParam );

	protected:
		bool m_Value;
		BoolParameter* m_pParameter;
	};
};
#endif