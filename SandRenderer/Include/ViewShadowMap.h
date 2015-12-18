#ifndef ViewShadowMap_h
#define ViewShadowMap_h

#include "SceneRenderTask.h"

namespace Sand
{
	class ViewShadowMap : public SceneRenderTask
	{
	public:
		ViewShadowMap( Renderer& renderer , ResourceProxyPtr DepthTarget , int ViewPortWidth , int ViewPortHeight);
		virtual ~ViewShadowMap();

		virtual void Update( float fTime );
		virtual void QueuePreTasks( Renderer* pRenderer );
		virtual void ExecuteTask( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

		virtual std::wstring GetName();

	protected:
		ResourceProxyPtr m_DepthTarget;
	};
}
#endif