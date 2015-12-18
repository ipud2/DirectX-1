#ifndef SceneRenderTask_h
#define SceneRenderTask_h

#include "Task.h"

namespace Sand
{
	class Entity;
	class Scene;

	enum VIEW_TYPE
	{
		VT_PERSPECTIVE ,
		VT_SHADOW_MAP ,
		VT_NUM_VIEW_TYPES
	};

	class SceneRenderTask : public Task
	{
	public:
		SceneRenderTask();
		virtual ~SceneRenderTask();

		virtual void SetRenderParams( IParameterManager* pParamManager );
		virtual void SetUsageParams( IParameterManager* pParamManager );

		virtual void SetScene( Scene* pScene );

		/*	
			View Port
		*/
		void SetViewPortID( int ViewPortID , unsigned int index = 0 );
		void SetViewPortCount( unsigned int count );
		void ConfigureViewPortsToRasterizerStage( PipelineManager* pPipeline );
		const ViewPort& GetViewPort( unsigned int slot );

		// 设置背景颜色
		virtual void SetBackColor( const Vector4f& color );
		
		/*
			设置View Matrix和Proj Matrix
		*/
		virtual void SetViewMatrix( const Matrix4f& matrix );
		virtual void SetProjMatrix( const Matrix4f& matrix );
		Matrix4f GetViewMatrix();
		Matrix4f GetProjMatrix();

	protected:
		Scene* m_pScene;

		// 背景颜色
		Vector4f m_vColor;

		// 视口设置
		int m_iViewPorts[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		unsigned int m_uiViewPortCount;

		// 变换矩阵
		Matrix4f ViewMatrix;
		Matrix4f ProjMatrix;
	};
};
#endif