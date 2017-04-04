#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Object/UnorderedAccessParameter.h"

using namespace Sand;

UnorderedAccessParameter::UnorderedAccessParameter( std::wstring name )
	:RenderParameter( name )
{
	// 默认视图对象
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
	// 检测数据是否发生变化
	if( 0 != memcmp( pData , &m_iUnorderedAccessID , sizeof( int ) ) )
	{
		// 不一致
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