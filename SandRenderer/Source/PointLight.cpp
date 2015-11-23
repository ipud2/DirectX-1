#include "PCH.h"
#include "PointLight.h"
#include "PositionExtractorController.h"

using namespace Sand;

PointLight::PointLight()
	:m_PositionWriter( nullptr )
{
	// ����Writer
	m_PositionWriter = Parameters.SetValueToVectorParameterWriter( L"LightPosition" , Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) );

	// ����һ����������ר��������ȡλ��
	PositionExtractorController<Entity>* pPositionExtractorController = new PositionExtractorController < Entity > ;
	pPositionExtractorController->SetParameterWriter( m_PositionWriter );
	GetBody()->GetControllersRef().Attach( pPositionExtractorController );
}

PointLight::~PointLight()
{

}