#include <Engine/PCH.h>
#include "Engine/Resource/Buffer/IndexBuffer.h"

using namespace Sand;

IndexBuffer::IndexBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer )
{
	m_Buffer = pBuffer;
}

IndexBuffer::~IndexBuffer()
{

}

ResourceType IndexBuffer::GetType()
{
	return RT_INDEXBUFFER;
}

void IndexBuffer::SetIndexCount( int count )
{
	m_iIndexCount = count;
}

void IndexBuffer::SetIndexSize( int size )
{
	m_iIndexSize = size;
}