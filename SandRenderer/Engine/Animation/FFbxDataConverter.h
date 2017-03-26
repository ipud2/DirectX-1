#ifndef FFBX_DATA_CONVERTER_H
#define FFBX_DATA_CONVERTER_H

#include "Vector4f.h"
#include "Matrix4f.h"
#include "fbxsdk.h"

namespace Sand
{
	class FFbxDataConverter
	{
	public:
		static Vector3f ConvertPos( FbxVector4 Vector );
		static Vector3f ConvertDir( FbxVector4 Vector );
		static Vector3f ConvertScale( FbxDouble3 Vector );
		static Vector3f ConvertScale( FbxDouble4 Vector );
		static Matrix4f ConvertMatrix( FbxAMatrix Matrix );
	};
}
#endif