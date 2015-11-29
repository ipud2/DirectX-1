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

		void SetRenderParams( IParameterManager* pParameterManager );

	protected:
		ParameterContainer Parameters;
	};

	typedef std::shared_ptr<SurfaceProperty> SurfacePropertyPtr;
};
#endif