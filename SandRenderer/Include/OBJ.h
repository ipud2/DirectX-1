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
		// һ�����������������
		std::array<int , 3> PositionIndices;
		std::array<int , 3> NormalIndices;
		std::array<int , 3> CoordinateIndices;
	};

	struct OBJSubObject
	{
		// ÿ��SubObjectʹ��ͬһ������
		// �����ɶ�������
		std::string MaterialName;
		std::vector<OBJFace> Faces;

		OBJSubObject()
		{
			MaterialName = "";
		}
	};

	struct OBJObject
	{
		// ÿ�������ɶ�����������
		std::string name;
		std::vector<OBJSubObject> SubObjects;
	};
};
#endif