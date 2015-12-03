#include "PCH.h"
#include "SurfaceProperty.h"

using namespace Sand;

SurfaceProperty::SurfaceProperty()
{
	
}

SurfaceProperty::~SurfaceProperty()
{
	
}

void SurfaceProperty::UpdateRenderParams( IParameterManager* pParameterManager )
{
	Parameters.UpdateRenderParam( pParameterManager );
}