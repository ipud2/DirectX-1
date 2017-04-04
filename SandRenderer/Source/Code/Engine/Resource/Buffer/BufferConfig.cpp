#include <Engine/PCH.h>
#include "Engine/Resource/Buffer/BufferConfig.h"

using namespace Sand;

BufferConfig::BufferConfig()
{
	SetDefaults();
}

BufferConfig::~BufferConfig()
{

}

void BufferConfig::SetDefaults()
{
	m_State.Usage = D3D11_USAGE_DEFAULT;
	m_State.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_State.MiscFlags = 0;
	m_State.ByteWidth = 1;
	m_State.StructureByteStride = 0;
}

void BufferConfig::SetDefaultConstantBuffer( UINT size , bool dynamic )
{
	
	m_State.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_State.MiscFlags = 0;
	m_State.StructureByteStride = 0;
	m_State.ByteWidth = size;

	if( dynamic )
	{
		m_State.Usage = D3D11_USAGE_DYNAMIC;
		m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_State.Usage = D3D11_USAGE_IMMUTABLE;
		m_State.CPUAccessFlags = 0;
		
	}
}

void BufferConfig::SetDefaultVertexBuffer( UINT size , bool dynamic )
{
	m_State.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_State.MiscFlags = 0;
	m_State.StructureByteStride = 0;
	m_State.ByteWidth = size;

	if( dynamic )
	{
		m_State.Usage = D3D11_USAGE_DYNAMIC;
		m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_State.Usage = D3D11_USAGE_IMMUTABLE;
		m_State.CPUAccessFlags = 0;
	}
}

void BufferConfig::SetDefaultIndexBuffer( UINT size , bool dynamic )
{
	m_State.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_State.MiscFlags = 0;
	m_State.StructureByteStride = 0;
	m_State.ByteWidth = size;

	if( dynamic )
	{
		m_State.Usage = D3D11_USAGE_DYNAMIC;
		m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_State.Usage = D3D11_USAGE_IMMUTABLE;
		m_State.CPUAccessFlags = 0;
	}
}

void BufferConfig::SetDefaultStructureBuffer( UINT size , UINT structureSize )
{
	m_State.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	m_State.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_State.StructureByteStride = structureSize;
	m_State.ByteWidth = size * structureSize;
	m_State.Usage = D3D11_USAGE_DEFAULT;
	m_State.CPUAccessFlags = 0;
}

void BufferConfig::SetBindFlags( UINT BindFlags )
{
	m_State.BindFlags = BindFlags;
}

void BufferConfig::SetByteWidth( UINT width )
{
	m_State.ByteWidth = width;
}

void BufferConfig::SetCPUAccessFlags( UINT CpuAccessFlags )
{
	m_State.CPUAccessFlags = CpuAccessFlags;
}

void BufferConfig::SetMiscFlags( UINT MiscFlags )
{
	m_State.MiscFlags = MiscFlags;
}

void BufferConfig::SetStructureByteStride( UINT StructureByteStride )
{
	m_State.StructureByteStride = StructureByteStride;
}

void BufferConfig::SetUsage( D3D11_USAGE usage )
{
	m_State.Usage = usage;
}

D3D11_BUFFER_DESC BufferConfig::GetBufferDesc()
{
	return m_State;
}