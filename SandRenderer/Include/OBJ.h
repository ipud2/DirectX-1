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
		// һ�����������������
		std::array<int , 3> PositionIndices;
		std::array<int , 3> NormalIndices;
		std::array<int , 3> CoordinateIndices;
	}OBJFace;

	typedef struct
	{
		// ÿ��SubObjectʹ��ͬһ������
		// �����ɶ�������
		std::wstring MaterialName;
		std::vector<OBJFace> Faces;
	}OBJSubObject;

	typedef struct
	{
		// ÿ�������ɶ�����������
		std::wstring name;
		std::vector<OBJSubObject> SubObjects;
	}OBJObject;


	//// ���ݲֿ⣬ͳһ�����ڴ�
	//std::vector<Vector3f> Position;
	//std::vector<Vector3f> Normal;
	//std::vector<Vector2f> Coordinate;

	//std::vector<Object> Objects;
	//std::vector<std::wstring> MaterialList;
}

#endif