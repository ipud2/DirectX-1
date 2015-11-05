#ifndef PipelineManager_h
#define PipelineManager_h

#include "Resource.h"

#include "RasterizerStage.h"
#include "OutputMergeStage.h"

#include "Vector4f.h"

namespace Sand
{
	/*
		该类用于管理管线的各个阶段
	*/
	class PipelineManager
	{
	public:
		PipelineManager();
		~PipelineManager();

		void SetDeviceContext( DeviceContextComPtr pContext , D3D_FEATURE_LEVEL FeatureLevel );
		ID3D11DeviceContext* GetDeviceContext();
		

		void ClearRenderTargets();
		void ApplyRenderTargets();

		//************************************
		// Method:    ClearBuffers
		// FullName:  Sand::PipelineManager::ClearBuffers
		// Access:    public 
		// Returns:   void
		// Qualifier: 重置render target view 和 depth stencil view中的值
		// Parameter: Vector4f & color
		// Parameter: float depth
		// Parameter: UINT stencil
		//************************************
		void ClearBuffers( Vector4f& color , float depth = 1.0f , UINT stencil = 0 );


		void SaveTextureScreenShot( int ID , std::wstring filename );

	public:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		DeviceContextComPtr m_pContext;

		RasterizerStage m_RasterizerStage;
		OutputMergeStage m_OutputMergeStage;
	};
}

#endif