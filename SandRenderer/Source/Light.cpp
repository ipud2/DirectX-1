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
		�������еĲ���
	*/
	m_LightParameterWriters.UpdateRenderParam( pParamMgr );
}