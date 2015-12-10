#include "PCH.h"
#include "SurfaceMaterial.h"

using namespace Sand;

SurfaceMaterial::SurfaceMaterial()
{
	
}

SurfaceMaterial::~SurfaceMaterial()
{
	
}

void SurfaceMaterial::UpdateRenderParams( IParameterManager* pParameterManager )
{
	Parameters.UpdateRenderParam( pParameterManager );
}