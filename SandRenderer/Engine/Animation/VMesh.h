#ifndef V_MESH_H
#define V_MESH_H

#include <Vector2f.h>
#include <Vector3f.h>
#include <Vector4f.h>
#include <vector>
#include "VVertex.h"
#include "Matrix4f.h"
#include "VTriangle.h"

namespace Sand
{
	class VMesh
	{
	public:
		VMesh( EInputMask mask );

		void Clear();

		std::vector<VVertex>&	GetVertexList();
		std::vector<VTriangle>&	GetTriangleList();
		EInputMask				GetInputMask();
		void					SetTransform( Matrix4f& localMatrix );
		void					SetName( const char* name );
		Matrix4f&				GetTransform();

	protected:
		std::vector<VVertex>		m_vVertices;
		std::vector<VTriangle>		m_vTriangle;
		EInputMask					m_eInputMask;
		Matrix4f					m_LocalTransform;
		char						m_Name[256];
	};
}
#endif