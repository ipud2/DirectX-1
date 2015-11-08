#ifndef OBJ_h
#define OBJ_h

#include <vector>
#include <array>
#include "Vector2f.h"
#include "Vector3f.h"

namespace Sand
{
	typedef struct
	{
		// 一个面由三个顶点组成
		std::array<int , 3> PositionIndices;
		std::array<int , 3> NormalIndices;
		std::array<int , 3> CoordinateIndices;
	}OBJFace;

	typedef struct
	{
		// 每个SubObject使用同一个纹理
		// 并且由多个面组成
		std::wstring MaterialName;
		std::vector<OBJFace> Faces;
	}OBJSubObject;

	typedef struct
	{
		// 每个物体由多个子物体组成
		std::wstring name;
		std::vector<OBJSubObject> SubObjects;
	}OBJObject;


	//// 数据仓库，统一保存在此
	//std::vector<Vector3f> Position;
	//std::vector<Vector3f> Normal;
	//std::vector<Vector2f> Coordinate;

	//std::vector<Object> Objects;
	//std::vector<std::wstring> MaterialList;
}

#endif