#ifndef Renderable_h
#define Renderable_h

#include "InputAssemblerStageExecutor.h"
#include "Material.h"

namespace Sand
{
	class Renderable
	{
	public:
		enum ENTITYTYPE
		{
			GUI_TEXT , 
			GUI , 
			ALPHA , 
			SKY , 
			BACKGROUND , 
			GEOMETRY , 
			NUMPASSES
		};

		Renderable();
		~Renderable();

	public:
		void SetMaterial( MaterialPtr pMaterial );
		MaterialPtr GetMaterial();

		void SetGeometry( InputAssemblerStageExecutorPtr pExecutor );
		InputAssemblerStageExecutorPtr GetGeometry();

	public:
		ENTITYTYPE iPass;

		InputAssemblerStageExecutorPtr IAStageExecutor;

		MaterialPtr Mat;
	};
}
#endif