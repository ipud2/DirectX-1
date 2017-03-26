#include "PCH.h"
#include "VSubMesh.h"

VSubMesh::VSubMesh()
{
	m_iVertexOffsets[0] = m_iVertexOffsets[1] = 0;
	m_iIndexOffsets[0] = m_iIndexOffsets[1] = 0;

	m_pMesh = nullptr;
}

VSubMesh::~VSubMesh()
{

}

VMesh* VSubMesh::GetMesh()
{
	return m_pMesh;
}

void VSubMesh::SetMesh( VMesh* pMesh )
{
	m_pMesh = pMesh;
}