#ifndef Vector2fParameterWriter_h
#define Vector2fParameterWriter_h

#include "Engine/Parameter/ParameterWriter/ParameterWriter.h"

namespace Sand
{
	class Vector2fParameterWriter : public ParameterWriter
	{
	public:
		Vector2fParameterWriter();
		virtual ~Vector2fParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();
		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		void SetValue( const Vector2f& Value );
		Vector2f GetValue();

		void SetRenderParameterRef( Vector2fParameter* pParam );

	protected:
		Vector2fParameter* m_pParameter;
		Vector2f m_Value;
	};
};
#endif