#include <Engine/PCH.h>
#include "Engine/Resource/Buffer/VertexBuffer.h"

using namespace Sand;

VertexBuffer::VertexBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer )
{
	m_Buffer = pBuffer;
}

VertexBuffer::~VertexBuffer()
{

}

ResourceType VertexBuffer::GetType()
{
	return RT_VERTEXBUFFER;
}

void VertexBuffer::SetVertexStructureSize( int size )
{
	m_iVertexStructureSize = size;
}

void VertexBuffer::SetVertexCount( int count )
{
	m_iVertexCount = count;
}