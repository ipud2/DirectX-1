#ifndef MatrixParameterWriter_h
#define MatrixParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class MatrixParameterWriter : public ParameterWriter
	{
	public:
		MatrixParameterWriter();
		virtual ~MatrixParameterWriter();

		virtual RenderParameter* GetRenderParameterRef();
		virtual void WriteParameter( IParameterManager* pParamMgr );
		virtual void InitializeParameter();

		void SetValue( const Matrix4f& Value );
		Matrix4f GetValue();

		void SetRenderParameterRef( MatrixParameter* pParam );

	protected:
		MatrixParameter* m_pParameter;
		Matrix4f m_Value;
	};
};
#endif