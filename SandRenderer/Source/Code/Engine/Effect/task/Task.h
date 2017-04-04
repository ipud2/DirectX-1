#ifndef Task_h
#define Task_h

#include "Engine/Pipeline/PipelineManager.h"
#include "Engine/Parameter/IParameterManager.h"

namespace Sand
{
	class Task
	{
	public:
		Task();
		virtual ~Task();

		virtual void Update( float fTime ) = 0;
		virtual void QueuePreTasks( Renderer* pRenderer ) = 0;
		virtual void ExecuteTask( PipelineManager* pPipelineManager , IParameterManager* pParameterManager ) = 0;

		virtual void SetRenderParams( IParameterManager* pParamManager ) = 0;
		virtual void SetUsageParams( IParameterManager* pParamManager ) = 0;

		virtual std::wstring GetName() = 0;
	};
};
#endif