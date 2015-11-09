#include "PCH.h"
#include "SamplerParameter.h"

using namespace Sand;

SamplerParameter::SamplerParameter()
{
	m_iSamplerID = -1;
}

SamplerParameter::SamplerParameter( SamplerParameter& copy )
{
	m_iSamplerID = copy.m_iSamplerID;
}

SamplerParameter::~SamplerParameter()
{

}

void SamplerParameter::SetParameter( void * pData )
{
	// 检测数据是否发生变化
	if( 0 != memcmp( pData , &m_iSamplerID , sizeof( int ) ) )
	{
		// 不一致
		m_iSamplerID = *reinterpret_cast< int* >( pData );
	}
}

const ParameterType SamplerParameter::GetParameterType()
{
	return PT_SAMPLER;
}

int SamplerParameter::GetValue()
{
	return m_iSamplerID;
}