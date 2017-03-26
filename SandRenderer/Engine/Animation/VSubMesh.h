#ifndef V_SUB_MESH_H
#define V_SUB_MESH_H

#include "Vector2f.h"

class VMesh;

class VSubMesh
{
public:
	VSubMesh();

	~VSubMesh();

public:
	VMesh* GetMesh();

	void SetMesh( VMesh* pMesh );

protected:
	int m_iVertexOffsets[2];		// Sub Mesh First Vertex - End Vertex
	int m_iIndexOffsets[2];			// Sub Mesh First Index - End Index
	VMesh* m_pMesh;
};
#endif