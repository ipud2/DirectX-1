#ifndef FFBX_MESH_H
#define FFBX_MESH_H

#include <fbxsdk.h>
#include "Geometry.h"

namespace Sand
{
	GeometryPtr ParseMesh( FbxNode* pNode , uint32_t& vertex_layer );
}
#endif