#include "PCH.h"
#include "SurfaceProperty.h"

using namespace Sand;

SurfaceProperty::SurfaceProperty()
{
	
}

SurfaceProperty::~SurfaceProperty()
{
	
}

void SurfaceProperty::SetRenderParams( IParameterManager* pParameterManager )
{
	Parameters.SetRenderParams( pParameterManager );
}