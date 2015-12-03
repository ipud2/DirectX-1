#ifndef VectorParameterWriter_h
#define VectorParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class VectorParameterWriter : public ParameterWriter
	{
	public:
		VectorParameterWriter();
		virtual ~VectorParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();
		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		void SetValue( const Vector4f& Value );
		Vector4f GetValue();

		void SetRenderParameterRef( VectorParameter* pParam );

	protected:
		VectorParameter* m_pParameter;
		Vector4f m_Value;
	};
};
#endif