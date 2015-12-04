#ifndef Vector3fParameterWriter_h
#define Vector3fParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class Vector3fParameterWriter : public ParameterWriter
	{
	public:
		Vector3fParameterWriter();
		virtual ~Vector3fParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();
		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		void SetValue( const Vector3f& Value );
		Vector3f GetValue();

		void SetRenderParameterRef( Vector3fParameter* pParam );

	protected:
		Vector3fParameter* m_pParameter;
		Vector3f m_Value;
	};
};
#endif