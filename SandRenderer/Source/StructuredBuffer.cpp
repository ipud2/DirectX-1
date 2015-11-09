#include "PCH.h"
#include "StructuredBuffer.h"

using namespace Sand;

StructuredBuffer::StructuredBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer )
{
	m_Buffer = pBuffer;
}

StructuredBuffer::~StructuredBuffer()
{

}

ResourceType StructuredBuffer::GetType()
{
	return RT_STRUCTUREDBUFFER;
}