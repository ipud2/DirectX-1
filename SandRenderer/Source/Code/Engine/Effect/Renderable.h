#ifndef Renderable_h
#define Renderable_h

#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/InputAssemblerStageExecutor.h"
#include "Engine/Effect/Effect.h"
#include "Engine/Material/Material.h"

namespace Sand
{
	class Renderable
	{
	public:
		Renderable();
		~Renderable();

	public:
		void SetEffect( EffectPtr pShaderEffect );
		EffectPtr GetEffect();

		void SetGeometry( InputAssemblerStageExecutorPtr pExecutor );
		InputAssemblerStageExecutorPtr GetGeometry();

		void SetMaterial( Material* pMat );
		Material* GetMaterial();

	public:
		InputAssemblerStageExecutorPtr IAStageExecutor;

		EffectPtr ShaderEffect;

		//SurfaceMaterial* Material;
		Material* pMaterial;
	};
}
#endif