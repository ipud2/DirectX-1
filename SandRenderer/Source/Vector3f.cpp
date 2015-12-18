#include "PCH.h"
#include "Vector3f.h"

using namespace Sand;

void Vector3f::Normalize()
{
	float Mag = Magnitude();

	if( 0.0f == Mag )	Mag = 0.0001f;

	float fInvMag = ( 1.0f / Mag );

	x *= fInvMag;
	y *= fInvMag;
	z *= fInvMag;
}

float Vector3f::Magnitude()
{
	float fLenght = 0.0f;

	fLenght += x * x;
	fLenght += y * y;
	fLenght += z * z;

	return ( sqrtf( fLenght ) );
}

Vector3f Vector3f::Perpendicular()
{
	float xAbs = fabs( x );
	float yAbs = fabs( y );
	float zAbs = fabs( z );

	float minVal = min( min( xAbs , yAbs ) , zAbs );

	// 若xAbs为最小值，则要么xAbs为0.0f
	// 要么xAbs比0.0f大，但比其他两个大
	// 如果xAbs是0.0f，则说明向量在y，z平面
	// 则(1.0f , 0.0f , 0.0f)与其不共线，
	// 则Cross得到的结果正是和原向量垂直的
	// 如果xAbs不是0.0f,但却是最小值，
	// 那么说明该向量肯定不会与(1.0f , 0.0f , 0.0f)共线
	// 所以Cross得到的结果也正是我们想要的
	// yAbs,zAbs为最小值的情况同理
	if( xAbs == minVal )
	{
		return cross( *this , Vector3f( 1.0f , 0.0f , 0.0f ) );
	}
	else if( yAbs == minVal )
	{
		return cross( *this , Vector3f( 0.0f , 1.0f , 0.0f ) );
	}
	else
	{
		return cross( *this , Vector3f( 0.0f , 0.0f , 1.0f ) );
	}
}

Vector3f Vector3f::Random()
{
	// 范围在-1.0f ~ 1.0f
	float x = static_cast< float >( ( double )rand() / RAND_MAX ) * 2.0f - 1.0f;
	float y = static_cast< float >( ( double )rand() / RAND_MAX ) * 2.0f - 1.0f;
	float z = static_cast< float >( ( double )rand() / RAND_MAX ) * 2.0f - 1.0f;

	Vector3f random = Vector3f( x , y , z );
	random.Normalize();

	return ( random );
}

Vector3f Vector3f::Normalize( Vector3f& A )
{
	A.Normalize();

	return A;
}