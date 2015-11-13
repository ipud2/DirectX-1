#ifndef MatrixArrayParameterWriter_h
#define MatrixArrayParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class MatrixArrayParameterWriter : public ParameterWriter
	{
	public:
		MatrixArrayParameterWriter();
		virtual ~MatrixArrayParameterWriter();

		virtual void InitializeParameter();
		virtual void WriteParameter( IParameterManager* pParamMgr );
		virtual RenderParameter* GetRenderParameterRef();

		void SetRenderParameterRef( MatrixArrayParameter* pParameter );
		
		void SetValue( Matrix4f* pValue , int Count );

	protected:
		MatrixArrayParameter* m_pParameter;
		Matrix4f* m_pValue;
		int m_iCount;
	};
}

#endif