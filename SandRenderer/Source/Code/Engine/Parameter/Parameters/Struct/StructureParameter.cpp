#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Struct/StructureParameter.h"

using namespace Sand;

StructureParameter::StructureParameter( std::wstring name , int size )
	:BaseNumericTypeRenderParameter( name )
{
	m_Size = size;

	m_pData = new char[m_Size];
}

StructureParameter::StructureParameter( StructureParameter& copy )
	:BaseNumericTypeRenderParameter( copy )
{
	if ( m_Size != copy.m_Size )
	{
		delete[] m_pData;

		m_pData = new char[copy.m_Size];

		m_Size = copy.m_Size;
	}

	memcpy( m_pData , copy.m_pData , m_Size );
}

StructureParameter::~StructureParameter()
{
	delete[] m_pData;
	m_pData = nullptr;
}

void StructureParameter::SetParameterData( void* pData )
{
	// 检测是否一致,默认大小一致
	if ( 0 != memcmp( pData , m_pData , m_Size ) )
	{
		memcpy( m_pData , pData , m_Size );
		m_Identifier++;
	}
}

const ParameterType StructureParameter::GetParameterType()
{
	return PT_STRUCTURE;
}

char* StructureParameter::GetStructureData()
{
	return m_pData;
}

int StructureParameter::GetStructureSize()
{
	return m_Size;
}