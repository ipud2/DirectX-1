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
	// ���жϸ���Ԫ���Ƿ��Ѿ�����
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
		// ˵��Ŀǰ�����ڸ��ֶ�
		m_vElements.push_back( pElement );
	}
	else
	{
		delete m_vElements[index];		// �ͷ�ԭ����Ԫ��
		m_vElements[index] = pElement;	// ������Ԫ��
	}
}

void Geometry::LoadToBuffer()
{
	// --------------����Vertex Buffer �� Index Buffer��ResourceProxy����--------------------

	// ���㶥���б��ж�����Ŀ
	CalculateVertexCount();

	// ���㶥��ṹ��С
	CalculateVertexStructureSize();

	if( m_iVertexStructureSize > 0 )
	{
		// ���㱣�����ж�������������ֽڴ�С
		unsigned int length = m_iVertexStructureSize * m_iVertexCount;

		// �����������ڱ������ж�������
		char* pData = new char[length];

		for( int i = 0; i < m_iVertexCount; i++ )
		{
			int offset = 0;
			for( int j = 0; j < m_vElements.size(); j++ )
			{
				// ����������������������
				memcpy( pData + i * m_iVertexStructureSize + offset , m_vElements[j]->GetDataPtr( i ) , m_vElements[j]->GetElementSizeInBytes() );
				offset += m_vElements[j]->GetElementSizeInBytes();
			}
		}

		// -------------------------------�������㻺��----------------------------------

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = reinterpret_cast< void* >( pData );
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		// �������㻺������
		BufferConfig config;
		config.SetDefaultVertexBuffer( length , false );

		// ����Vertex Buffer
		m_VertexBuffer = Renderer::Get()->CreateVertexBuffer( &config , &data );

		// -----------------------------������������-----------------------------------
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = &m_vIndices[0];
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		BufferConfig config;
		config.SetDefaultIndexBuffer( m_vIndices.size() * sizeof( unsigned int ) , false );
		// ����Index Buffer
		m_IndexBuffer = Renderer::Get()->CreateIndexBuffer( &config , &data );
	}
}

int Geometry::CalculateVertexCount()
{
	// ���㶥���б��ж�����Ŀ

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
	// ���㶥��ṹ��С

	int VertexStructureSize = 0;

	for( auto pVertexElement : m_vElements )
	{
		VertexStructureSize += pVertexElement->GetElementSizeInBytes();
	}

	return VertexStructureSize;
}