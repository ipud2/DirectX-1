#include "PCH.h"
#include "UnorderedAccessParameter.h"

using namespace Sand;

UnorderedAccessParameter::UnorderedAccessParameter()
{
	m_iUnorderedAccessID = -1;
}

UnorderedAccessParameter::UnorderedAccessParameter( UnorderedAccessParameter& copy )
{
	m_iUnorderedAccessID = copy.m_iUnorderedAccessID;
}

UnorderedAccessParameter::~UnorderedAccessParameter()
{

}

void UnorderedAccessParameter::SetParameter( void * pData )
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

int UnorderedAccessParameter::GetValue()
{
	return m_iUnorderedAccessID;
}