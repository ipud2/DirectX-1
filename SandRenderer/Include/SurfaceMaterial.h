#ifndef SurfaceMaterial_h
#define SurfaceMaterial_h

#include "ParameterContainer.h"

namespace Sand
{
	class SurfaceMaterial
	{
	public:
		SurfaceMaterial();
		virtual ~SurfaceMaterial();

		void UpdateRenderParams( IParameterManager* pParameterManager );

	protected:
		ParameterContainer Parameters;
	};
};
#endif