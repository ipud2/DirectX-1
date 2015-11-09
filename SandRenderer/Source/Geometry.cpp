#include "PCH.h"
#include "Geometry.h"
#include "BufferConfig.h"
#include "Renderer.h"

using namespace Sand;

Geometry::Geometry()
{
	m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_iVertexStructureSize = 0;
	m_iVertexCount = 0;
}

Geometry::~Geometry()
{

}

void Geometry::AddFace( int index_1 , int index_2 , int index_3 )
{
	m_vIndices.push_back( index_1 );
	m_vIndices.push_back( index_2 );
	m_vIndices.push_back( index_3 );
}

void Geometry::AddElement( VertexElement* pElement )
{
	// 先判断该类元素是否已经存在
	int index = -1;
	for( unsigned int i = 0; i < m_vElements.size(); i++ )
	{
		if( m_vElements[i]->m_SemanticName == pElement->m_SemanticName )
		{
			index = i;
		}
	}

	if( index == -1 )
	{
		// 说明目前不存在该字段
		m_vElements.push_back( pElement );
	}
	else
	{
		delete m_vElements[index];		// 释放原来的元素
		m_vElements[index] = pElement;	// 设置新元素
	}
}

void Geometry::LoadToBuffer()
{
	// --------------创建Vertex Buffer 和 Index Buffer的ResourceProxy对象--------------------

	// 计算顶点列表中顶点数目
	CalculateVertexCount();

	// 计算顶点结构大小
	CalculateVertexStructureSize();

	if( m_iVertexStructureSize > 0 )
	{
		// 计算保存所有顶点数据所需的字节大小
		unsigned int length = m_iVertexStructureSize * m_iVertexCount;

		// 创建数组用于保存所有顶点数据
		char* pData = new char[length];

		for( int i = 0; i < m_iVertexCount; i++ )
		{
			int offset = 0;
			for( int j = 0; j < m_vElements.size(); j++ )
			{
				// 将顶点各属性数据逐个拷贝
				memcpy( pData + i * m_iVertexStructureSize + offset , m_vElements[j]->GetDataPtr( i ) , m_vElements[j]->GetElementSizeInBytes() );
				offset += m_vElements[j]->GetElementSizeInBytes();
			}
		}

		// -------------------------------创建顶点缓存----------------------------------

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = reinterpret_cast< void* >( pData );
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		// 创建顶点缓存描述
		BufferConfig config;
		config.SetDefaultVertexBuffer( length , false );

		// 创建Vertex Buffer
		m_VertexBuffer = Renderer::Get()->CreateVertexBuffer( &config , &data );

		// -----------------------------创建索引缓存-----------------------------------
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = &m_vIndices[0];
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		BufferConfig config;
		config.SetDefaultIndexBuffer( m_vIndices.size() * sizeof( unsigned int ) , false );
		// 创建Index Buffer
		m_IndexBuffer = Renderer::Get()->CreateIndexBuffer( &config , &data );
	}
}

int Geometry::CalculateVertexCount()
{
	// 计算顶点列表中顶点数目

	if( m_vElements.size() != 0 )
	{
		m_iVertexCount = m_vElements[0]->GetCount();
	}
	else
	{
		m_iVertexCount = 0;
	}

	return 0;
}

int Geometry::CalculateVertexStructureSize()
{
	// 计算顶点结构大小

	int VertexStructureSize = 0;

	for( auto pVertexElement : m_vElements )
	{
		VertexStructureSize += pVertexElement->GetElementSizeInBytes();
	}

	return VertexStructureSize;
}