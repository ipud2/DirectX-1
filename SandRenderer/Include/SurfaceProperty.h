#ifndef SurfaceProperty_h
#define SurfaceProperty_h

#include "ParameterContainer.h"

namespace Sand
{
	class SurfaceProperty
	{
	public:
		SurfaceProperty();
		virtual ~SurfaceProperty();

		void UpdateRenderParams( IParameterManager* pParameterManager );

	protected:
		ParameterContainer Parameters;
	};
};
#endif