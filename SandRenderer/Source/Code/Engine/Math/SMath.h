#ifndef MATH_H
#define MATH_H

#include "Engine/Math/Vector3f.h"
#include "Engine/Math/Vector4f.h"
#include "Engine/Math/Matrix3f.h"
#include "Engine/Math/Matrix4f.h"

namespace Sand
{
	Vector4f Multipy( Vector3f& v , Matrix4f& m );

	Vector3f MultipyNormal( Vector3f& v , Matrix4f& m );
	
	Vector4f Multipy( Vector4f& v , Matrix4f& m );

	bool IsZero( Vector3f& v );
}
#endif