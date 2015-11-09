#include "PCH.h"
#include "VertexElement.h"

using namespace Sand;

std::string VertexElement::PositionSemantic = "POSITION";
std::string VertexElement::NormalSemantic = "NORMAL";
std::string VertexElement::TexCoordSemantic = "TEXCOORD";
std::string VertexElement::TangentSemantic = "TANGENT";

VertexElement::VertexElement( int tuple , int elementCount )
{
	m_iTuple = tuple;
	m_iCount = elementCount;

	m_pfData = new float[m_iTuple * elementCount];
}

VertexElement::~VertexElement()
{
	delete[] m_pfData;
}

// 获取单个元素的大小，以字节表示
int VertexElement::GetElementSizeInBytes()
{
	return ( m_iTuple * sizeof( float ) );
}

int VertexElement::GetCount()
{
	return m_iCount;
}

int VertexElement::GetTuple()
{
	return m_iTuple;
}

void* VertexElement::GetDataPtr( int i )
{
	// 索引为i的元素的地址
	return ( &m_pfData[m_iTuple * i] );
}

float* VertexElement::Get1fTupleDataPtr( int i )
{
	return ( &m_pfData[m_iTuple * i] );
}

Vector2f* VertexElement::Get2fTupleDataPtr( int i )
{
	return ( ( Vector2f* )( &m_pfData[2 * i] ) );
}

Vector3f* VertexElement::Get3fTupleDataPtr( int i )
{
	return ( ( Vector3f* )( &m_pfData[3 * i] ) );
}

Vector4f* VertexElement::Get4fTupleDataPtr( int i )
{
	return ( ( Vector4f* )( &m_pfData[4 * i] ) );
}

float* VertexElement::operator[]( int i )
{
	return ( &m_pfData[m_iTuple * i] );
}

const float* VertexElement::operator[] ( int i ) const
{
	return ( &m_pfData[m_iTuple * i] );
}