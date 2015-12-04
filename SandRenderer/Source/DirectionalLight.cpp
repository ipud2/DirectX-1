#include "PCH.h"
#include "DirectionalLight.h"

using namespace Sand;

DirectionalLight::DirectionalLight( int ElementCount )
	:m_iElementCount( ElementCount ) ,
	m_pDirectionLightStructure( nullptr )
{
	m_pDirectionLightStructure = new DirectionalLightStructure[m_iElementCount];
	m_pDirectionalLightStructureWriter = m_LightParameterWriters.GetStructureParameterWriter( L"Light", sizeof( DirectionalLightStructure ) * m_iElementCount );
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::SetDirectionalLight( const Vector4f & AmbientLight , const Vector4f& DiffuseLight , const Vector4f& SpecularLight , const Vector4f& LightDirection , int index )
{
	m_pDirectionLightStructure[index].AmbientLight = AmbientLight;
	m_pDirectionLightStructure[index].DiffuseLight = DiffuseLight;
	m_pDirectionLightStructure[index].SpecularLight = SpecularLight;
	m_pDirectionLightStructure[index].LightDirection = LightDirection;

	m_pDirectionalLightStructureWriter->SetValue( reinterpret_cast< char* >( m_pDirectionLightStructure ) , sizeof( DirectionalLightStructure ) * m_iElementCount );
}