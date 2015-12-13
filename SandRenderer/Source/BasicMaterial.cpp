#include "PCH.h"
#include "BasicMaterial.h"

using namespace Sand;

BasicMaterial::BasicMaterial()
	:m_pData( nullptr )
{
	// 创建StructureParameterWriter对象
	m_pMaterialWriter = Parameters.GetStructureParameterWriter( L"Mat" , sizeof( BasicMaterialStructure ) );

	m_pData = new BasicMaterialStructure;
}

BasicMaterial::~BasicMaterial()
{
	
}

void BasicMaterial::SetMaterialData( const Vector4f& AmbientMaterial , const Vector4f& DiffuseMaterial , const Vector4f& SpecularMaterial , const Vector4f& Reflect )
{
	m_pData->AmbientMaterial = AmbientMaterial;

	m_pData->DiffuseMaterial = DiffuseMaterial;

	m_pData->SpecularMaterial = SpecularMaterial;

	m_pData->ReflectMaterial = Reflect;

	m_pMaterialWriter->SetValue( reinterpret_cast< char* >( m_pData ) , sizeof( BasicMaterialStructure ) );
}