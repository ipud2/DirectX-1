#include "PCH.h"
#include "ConstantBuffer.h"

using namespace Sand;

ConstantBuffer::ConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer )
{
	m_Buffer = pBuffer;
}

ConstantBuffer::~ConstantBuffer()
{

}

void ConstantBuffer::AddElement( ConstantBufferElementDesc element )
{
	m_vElements.push_back( element );
}

ResourceType ConstantBuffer::GetType()
{
	return RT_CONSTANTBUFFER;
}

void ConstantBuffer::Update( PipelineManager* pPipelineManager )
{

}