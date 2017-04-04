#include <Engine/PCH.h>
#include "Engine/Math/SMath.h"

Sand::Vector4f Sand::Multipy( Sand::Vector4f& v , Sand::Matrix4f& m )
{
	Sand::Vector4f Out;

	Out.x = v.x * m( 0 , 0 ) + v.y * m( 1 , 0 ) + v.z * m( 2 , 0 ) + v.w * m( 3 , 0 );
	Out.y = v.x * m( 0 , 1 ) + v.y * m( 1 , 1 ) + v.z * m( 2 , 1 ) + v.w * m( 3 , 1 );
	Out.z = v.x * m( 0 , 2 ) + v.y * m( 1 , 2 ) + v.z * m( 2 , 2 ) + v.w * m( 3 , 2 );
	Out.w = v.x * m( 0 , 3 ) + v.y * m( 1 , 3 ) + v.z * m( 2 , 3 ) + v.w * m( 3 , 3 );

	return Out;
}

Sand::Vector4f Sand::Multipy( Sand::Vector3f& v , Sand::Matrix4f& m )
{
	Sand::Vector4f Out;

	Out.x = v.x * m( 0 , 0 ) + v.y * m( 1 , 0 ) + v.z * m( 2 , 0 ) + m( 3 , 0 );
	Out.y = v.x * m( 0 , 1 ) + v.y * m( 1 , 1 ) + v.z * m( 2 , 1 ) + m( 3 , 1 );
	Out.z = v.x * m( 0 , 2 ) + v.y * m( 1 , 2 ) + v.z * m( 2 , 2 ) + m( 3 , 2 );
	Out.w = v.x * m( 0 , 3 ) + v.y * m( 1 , 3 ) + v.z * m( 2 , 3 ) + m( 3 , 3 );

	return Out;
}

Sand::Vector3f Sand::MultipyNormal( Sand::Vector3f& v , Sand::Matrix4f& m )
{
	Sand::Vector3f Out;

	Matrix4f t = m;
	t = t.Inverse().Transpose();

	Out.x = v.x * t( 0 , 0 ) + v.y * t( 1 , 0 ) + v.z * t( 2 , 0 );
	Out.y = v.x * t( 0 , 1 ) + v.y * t( 1 , 1 ) + v.z * t( 2 , 1 );
	Out.z = v.x * t( 0 , 2 ) + v.y * t( 1 , 2 ) + v.z * t( 2 , 2 );

	return Out;
}

bool Sand::IsZero( Sand::Vector3f& v )
{
	if ( v.x > -EPSILON && v.x < EPSILON && v.y > -EPSILON && v.y < EPSILON && v.z > -EPSILON && v.z < EPSILON )
	{
		return true;
	}

	return false;
}