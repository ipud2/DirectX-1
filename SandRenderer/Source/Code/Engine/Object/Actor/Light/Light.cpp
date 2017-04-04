#include <Engine/PCH.h>
#include "Engine/Object/Actor/Light/Light.h"

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
		�������еĲ���
	*/
	m_LightParameterWriters.UpdateRenderParam( pParamMgr );
}