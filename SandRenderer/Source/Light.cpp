#include "PCH.h"
#include "Light.h"

using namespace Sand;

Light::Light()
	:m_LightParameterWriters()
{

}

Light::~Light()
{

}

void Light::UpdateRenderParams( IParameterManager* pParamMgr )
{
	/*
		更新所有的参数
	*/
	m_LightParameterWriters.UpdateRenderParam( pParamMgr );
}