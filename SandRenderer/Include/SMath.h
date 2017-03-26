#ifndef MATH_H
#define MATH_H

#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"

namespace Sand
{
	Vector4f Multipy( Vector3f& v , Matrix4f& m );

	Vector3f MultipyNormal( Vector3f& v , Matrix4f& m );
	
	Vector4f Multipy( Vector4f& v , Matrix4f& m );

	bool IsZero( Vector3f& v );
}
#endif