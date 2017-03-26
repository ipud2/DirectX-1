#include "PCH.h"
#include "VMesh.h"
#include "Matrix4f.h"

using namespace Sand;

VMesh::VMesh( EInputMask eInputMask )
{
	m_vVertices.clear();
	m_vVertices.clear();
	m_vTriangle.clear();

	m_eInputMask = eInputMask;

	m_Name[0] = '\0';
}

void VMesh::Clear()
{
	m_vVertices.clear();
	m_vTriangle.clear();
}

std::vector<VVertex>& VMesh::GetVertexList()
{
	return m_vVertices;
}

std::vector<VTriangle>& VMesh::GetTriangleList()
{
	return m_vTriangle;
}

EInputMask VMesh::GetInputMask()
{
	return m_eInputMask;
}

void VMesh::SetTransform( Matrix4f& localMatrix )
{
	m_LocalTransform = localMatrix;
}

void VMesh::SetName( const char* name )
{
	ZeroMemory( m_Name , 256 );
	strcpy_s( m_Name , name );
}

Matrix4f& VMesh::GetTransform()
{
	return m_LocalTransform;
}