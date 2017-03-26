#ifndef FBX_INFO_HEADER_H
#define FBX_INFO_HEADER_H

#include <Vector3f.h>
#include <vector>

struct MorphInfo
{
	std::vector<int> MorphVertex;
	std::vector<Sand::Vector3f> VertexDelta;
};
#endif