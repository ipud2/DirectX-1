#include "PCH.h"
#include "Buffer.h"

using namespace Sand;

Buffer::Buffer()
{
	ZeroMemory( &m_DesiredDesc , sizeof( m_DesiredDesc ) );
	ZeroMemory( &m_ActualDesc , sizeof( m_ActualDesc ) );
}

Buffer::~Buffer()
{

}

D3D11_BUFFER_DESC Buffer::GetActualBufferDesc()
{
	// 从缓存中获取当前描述
	ZeroMemory( &m_ActualDesc , sizeof( m_ActualDesc ) );

	if( m_Buffer )
	{
		m_Buffer->GetDesc( &m_ActualDesc );
	}

	return m_ActualDesc;
}

D3D11_BUFFER_DESC Buffer::GetDesiredBufferDesc()
{
	return m_DesiredDesc;
}

void Buffer::SetDesiredBufferDesc( D3D11_BUFFER_DESC desc )
{
	m_DesiredDesc = desc;
}

UINT Buffer::GetByteWidth()
{
	D3D11_BUFFER_DESC Description = GetActualBufferDesc();

	return Description.ByteWidth;
}

void Buffer::SetByteWidth( UINT ByteWidth )
{
	m_DesiredDesc.ByteWidth = ByteWidth;
}

D3D11_USAGE Buffer::GetUsage()
{
	D3D11_BUFFER_DESC Description = GetActualBufferDesc();

	return Description.Usage;
}

void Buffer::SetUsage( D3D11_USAGE usage )
{
	m_DesiredDesc.Usage = usage;
}

UINT Buffer::GetBindFlags()
{
	D3D11_BUFFER_DESC Description = GetActualBufferDesc();

	return Description.BindFlags;
}

void Buffer::SetBindFlags( UINT BindFlags )
{
	m_DesiredDesc.BindFlags = BindFlags;
}

UINT Buffer::GetCPUAccessFlags()
{
	D3D11_BUFFER_DESC Description = GetActualBufferDesc();

	return Description.CPUAccessFlags;
}

void Buffer::SetCPUAccessFlags( UINT CPUAccessFlags )
{
	m_DesiredDesc.CPUAccessFlags = CPUAccessFlags;
}

UINT Buffer::GetMiscFlags()
{
	D3D11_BUFFER_DESC Description = GetActualBufferDesc();

	return Description.MiscFlags;
}

void Buffer::SetMiscFlags( UINT MiscFlags )
{
	m_DesiredDesc.MiscFlags = MiscFlags;
}

UINT Buffer::GetStructureByteStride()
{
	D3D11_BUFFER_DESC Description = GetActualBufferDesc();

	return Description.StructureByteStride;
}

void Buffer::SetStructureByteStride( UINT StructureByteStride )
{
	m_DesiredDesc.StructureByteStride = StructureByteStride;
}

ID3D11Resource* Buffer::GetResource()
{
	return m_Buffer.Get();
}