#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Object/UnorderedAccessParameter.h"

using namespace Sand;

UnorderedAccessParameter::UnorderedAccessParameter( std::wstring name )
	:RenderParameter( name )
{
	// Ĭ����ͼ����
	m_iUnorderedAccessID = 0;
}

UnorderedAccessParameter::UnorderedAccessParameter( UnorderedAccessParameter& copy )
	: RenderParameter( copy )
{
	m_iUnorderedAccessID = copy.m_iUnorderedAccessID;
}

UnorderedAccessParameter::~UnorderedAccessParameter()
{

}

void UnorderedAccessParameter::SetParameterData( void * pData )
{
	// ��������Ƿ����仯
	if( 0 != memcmp( pData , &m_iUnorderedAccessID , sizeof( int ) ) )
	{
		// ��һ��
		m_iUnorderedAccessID = *reinterpret_cast< int* >( pData );
	}
}

const ParameterType UnorderedAccessParameter::GetParameterType()
{
	return PT_UNORDERED_ACCESS;
}

int UnorderedAccessParameter::GetResourceViewID()
{
	return m_iUnorderedAccessID;
}