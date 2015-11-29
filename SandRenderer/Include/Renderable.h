#ifndef Renderable_h
#define Renderable_h

#include "InputAssemblerStageExecutor.h"
#include "Material.h"
#include "SurfaceProperty.h"

namespace Sand
{
	class Renderable
	{
	public:
		Renderable();
		~Renderable();

	public:
		void SetMaterial( MaterialPtr pMaterial );
		MaterialPtr GetMaterial();

		void SetGeometry( InputAssemblerStageExecutorPtr pExecutor );
		InputAssemblerStageExecutorPtr GetGeometry();

		void SetSurfaceProperty( SurfacePropertyPtr pSurfaceProperty );
		SurfacePropertyPtr GetSurfaceProperty();

	public:
		InputAssemblerStageExecutorPtr IAStageExecutor;

		MaterialPtr Mat;

		SurfacePropertyPtr Property;
	};
}
#endif