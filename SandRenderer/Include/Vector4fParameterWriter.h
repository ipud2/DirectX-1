#ifndef Vector4fParameterWriter_h
#define Vector4fParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class Vector4fParameterWriter : public ParameterWriter
	{
	public:
		Vector4fParameterWriter();
		virtual ~Vector4fParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();
		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		void SetValue( const Vector4f& Value );
		Vector4f GetValue();

		void SetRenderParameterRef( Vector4fParameter* pParam );

	protected:
		Vector4fParameter* m_pParameter;
		Vector4f m_Value;
	};
};
#endif