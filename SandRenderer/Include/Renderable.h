#ifndef Renderable_h
#define Renderable_h

#include "InputAssemblerStageExecutor.h"
#include "Effect.h"
#include "SurfaceMaterial.h"

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

		void SetSurfaceMaterial( SurfaceMaterial* pSurfaceMaterial );
		SurfaceMaterial* GetSurfaceMaterial();

	public:
		InputAssemblerStageExecutorPtr IAStageExecutor;

		EffectPtr ShaderEffect;

		SurfaceMaterial* Material;
	};
}
#endif