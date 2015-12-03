#ifndef StructureParameterWriter_h
#define StructureParameterWriter_h

#include "ParameterWriter.h"

namespace Sand
{
	class StructureParameterWriter : public ParameterWriter
	{
	public:
		StructureParameterWriter();
		virtual ~StructureParameterWriter();

		virtual void InitializeParameter();
		virtual void UpdateValueToParameter( IParameterManager* pParamMgr );
		virtual RenderParameter* GetRenderParameterRef();

		void SetRenderParameterRef( StructureParameter* pParameter );

		void SetValue( char* pData , int Size );

	protected:
		StructureParameter* m_pStructureParamter;
		char* m_pData;
	};
};
#endif