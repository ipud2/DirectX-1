#ifndef TGrowableBuffer_h
#define TGrowableBuffer_h

#include "Engine/Pipeline/PipelineManager.h"
#include "Engine/Resource/Buffer/BufferConfig.h"

namespace Sand
{
	template < class T > 
	class TGrowableBuffer
	{
	public:
		TGrowableBuffer();
		virtual ~TGrowableBuffer();

		void SetMaxElementCount( unsigned int max );
		unsigned int GetMaxElementCount();
		unsigned int GetCurrentELementCount();

		void AddElement( const T& element );

		virtual void UploadData( PipelineManager* pPipeline ) = 0;
		void ResetData();

		virtual ResourceProxyPtr GetBuffer() = 0;

	protected:
		virtual void CreateResource( unsigned int elments ) = 0;
		virtual void DeleteResource() = 0;

		void EnsureCapacity();

	protected:
		unsigned int m_uiMaxElementCount;
		unsigned int m_uiElementCount;

		bool m_bUploadNeeded;

		T* m_pDataArray;
	};

#include "TGrowableBuffer.inl"
};
#endif