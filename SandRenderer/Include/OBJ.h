#ifndef OBJ_h
#define OBJ_h

#include <vector>
#include <array>
#include "Vector2f.h"
#include "Vector3f.h"
#include "ResourceProxy.h"

namespace Sand
{
	struct OBJFace
	{
		// 一个面由三个顶点组成
		std::array<int , 3> PositionIndices;
		std::array<int , 3> NormalIndices;
		std::array<int , 3> CoordinateIndices;
	};

	struct OBJSubObject
	{
		// 每个SubObject使用同一个纹理
		// 并且由多个面组成
		std::string MaterialName;
		std::vector<OBJFace> Faces;

		OBJSubObject()
		{
			MaterialName = "";
		}
	};

	struct OBJObject
	{
		// 每个物体由多个子物体组成
		std::string name;
		std::vector<OBJSubObject> SubObjects;
	};
};
#endif