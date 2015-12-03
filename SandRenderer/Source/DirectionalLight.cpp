#include "PCH.h"
#include "DirectionalLight.h"

using namespace Sand;

DirectionalLight::DirectionalLight( int ElementCount )
	:m_iElementCount( ElementCount ) ,
	m_pDirectionLightStructure( nullptr )
{
	m_pDirectionLightStructure = new DirectionalLightStructure[m_iElementCount];
	m_pDirectionalLightStructureWriter = m_LightParameterWriters.SetValueToStructureParameterWriter( L"Light" , reinterpret_cast< char* >( m_pDirectionLightStructure ) , sizeof( DirectionalLightStructure ) * m_iElementCount );

	m_pDirectionLightStructure[0].AmbientLight = Vector4f( 0.25f , 0.25f , 0.25f , 0.25f );
	m_pDirectionLightStructure[0].DiffuseLight = Vector4f( 0.5f , 0.5f , 0.5f , 1.0f );
	m_pDirectionLightStructure[0].SpecularLight = Vector4f( 1.0f , 1.0f , 1.0f , 1.0f );
	m_pDirectionLightStructure[0].LightDirection = Vector4f( 0.707f , -0.707f , 0.0f , 1.0f );

	m_pDirectionLightStructure[1].AmbientLight = Vector4f( 0.2f , 0.2f , 0.2f , 1.0f );
	m_pDirectionLightStructure[1].DiffuseLight = Vector4f( 1.4f , 1.4f , 1.4f , 1.0f );
	m_pDirectionLightStructure[1].SpecularLight = Vector4f( 0.3f , 0.3f , 0.3f , 16.0f );
	m_pDirectionLightStructure[1].LightDirection = Vector4f( -0.707f , 0.0f , 0.707f , 1.0f );

	m_pDirectionalLightStructureWriter->SetValue( reinterpret_cast< char* >( m_pDirectionLightStructure ) , sizeof( DirectionalLightStructure ) * 2 );
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