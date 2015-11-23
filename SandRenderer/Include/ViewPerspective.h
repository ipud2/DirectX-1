#ifndef ViewPerspective_h
#define ViewPerspective_h

#include "SceneRenderTask.h"

namespace Sand
{
	class ViewPerspective : public SceneRenderTask
	{
	public:
		ViewPerspective( Renderer& renderer , ResourceProxyPtr RenderTarget , ResourceProxyPtr DepthTarget = nullptr );
		virtual ~ViewPerspective();

		virtual void Update( float fTime );
		virtual void QueuePreTasks( Renderer* pRenderer );
		virtual void ExecuteTask( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );
		
		void SetRenderTargets( ResourceProxyPtr RenderTarget , ResourceProxyPtr DepthTarget = nullptr );

		virtual std::wstring GetName();

	protected:
		ResourceProxyPtr m_RenderTarget;
		ResourceProxyPtr m_DepthTarget;
	};
}
#endif