#ifndef FFBX_MESH_H
#define FFBX_MESH_H

#include <FBXSDK/2017.0.1/inc/fbxsdk.h>
#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/Geometry.h"

namespace Sand
{
	GeometryPtr ParseMesh( FbxNode* pNode , uint32_t& vertex_layer );
}
#endif