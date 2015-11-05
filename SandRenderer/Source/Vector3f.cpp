#include "PCH.h"
#include "Vector3f.h"

using namespace Sand;

Vector3f::Vector3f()
{

}

Vector3f::Vector3f( float X , float Y , float Z )
{
	x = X;
	y = Y;
	z = Z;
}

Vector3f::Vector3f( const Vector3f& Vector )
{
	x = Vector.x;
	y = Vector.y;
	z = Vector.z;
}

void Vector3f::MakeZero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

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

void Vector3f::Clamp()
{
	if( x < 0.0f )	x = 0.0f;
	if( x > 1.0f )	x = 1.0f;

	if( y < 0.0f )	y = 0.0f;
	if( y > 1.0f )	y = 1.0f;

	if( z < 0.0f )	z = 0.0f;
	if( z > 1.0f )	z = 1.0f;
}

float Vector3f::Dot( const Vector3f& A ) const
{
	return ( x * A.x + y * A.y + z * A.z );
}

Vector3f Vector3f::Cross( const Vector3f& Vector ) const
{
	Vector3f vRet;

	/*
	x , y		Vector.y	Vector.z	Vector.x
	y , z		-Vector.x	-Vector.y	-Vector.z
	z , x
	*/
	vRet.z = y * Vector.z - z * Vector.y;
	vRet.y = z * Vector.x - x * Vector.z;
	vRet.z = x * Vector.y - y * Vector.x;

	return vRet;
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
		return Cross( Vector3f( 1.0f , 0.0f , 0.0f ) );
	}
	else if( yAbs == minVal )
	{
		return Cross( Vector3f( 0.0f , 1.0f , 0.0f ) );
	}
	else
	{
		return Cross( Vector3f( 0.0f , 0.0f , 1.0f ) );
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

Vector3f& Vector3f::operator= ( const Vector3f& Vector )
{
	x = Vector.x;
	y = Vector.y;
	z = Vector.z;

	return ( *this );
}

float Vector3f::operator[] ( int iPos ) const
{
	if( iPos == 0 )	return x;
	if( iPos == 1 )	return y;
	return z;
}

float& Vector3f::operator[] ( int iPos )
{
	if( iPos == 0 )	return x;
	if( iPos == 1 )	return y;
	return z;
}

bool Vector3f::operator== ( const Vector3f& Vector ) const
{
	if( ( x - Vector.x ) * ( x - Vector.x ) > 0.01f )
	{
		return false;
	}
	if( ( y - Vector.y ) * ( y - Vector.y ) > 0.01f )
	{
		return false;
	}
	if( ( z - Vector.z ) * ( z - Vector.z ) > 0.01f )
	{
		return false;
	}

	return true;
}

bool Vector3f::operator!= ( const Vector3f& Vector ) const
{
	return ( !( *this == Vector ) );
}

Vector3f Vector3f::operator+ ( const Vector3f& Vector ) const
{
	Vector3f sum;

	sum.x = x + Vector.x;
	sum.y = y + Vector.y;
	sum.z = z + Vector.z;

	return sum;
}

Vector3f Vector3f::operator- ( const Vector3f& Vector ) const
{
	Vector3f diff;

	diff.x = x - Vector.x;
	diff.y = y - Vector.y;
	diff.z = z - Vector.z;

	return diff;
}

Vector3f Vector3f::operator* ( const Vector3f& Vector ) const
{
	Vector3f prod;

	prod.x = x * Vector.x;
	prod.y = y * Vector.y;
	prod.z = z * Vector.z;

	return prod;
}

Vector3f Vector3f::operator* ( float fScalar ) const
{
	Vector3f prod;

	prod.x = x * fScalar;
	prod.y = y * fScalar;
	prod.z = z * fScalar;

	return prod;
}

Vector3f Vector3f::operator/ ( float fScalar ) const
{
	Vector3f quot;

	if( fScalar != 0.0f )
	{
		float fInvScalar = 1.0f / fScalar;

		quot.x = x * fInvScalar;
		quot.y = y * fInvScalar;
		quot.z = z * fInvScalar;
	}
	else
	{
		quot.MakeZero();
	}

	return quot;
}

Vector3f Vector3f::operator/ ( const Vector3f& Vector ) const
{
	Vector3f quot;
	quot.x = Vector.x != 0.0f ? x / Vector.x : 0.0f;
	quot.y = Vector.y != 0.0f ? y / Vector.y : 0.0f;
	quot.z = Vector.z != 0.0f ? z / Vector.z : 0.0f;

	return quot;
}

Vector3f Vector3f::operator- ( ) const
{
	Vector3f neq;

	neq.x = -x;
	neq.y = -y;
	neq.z = -z;

	return neq;
}

Vector3f& Vector3f::operator+= ( const Vector3f& Vector )
{
	x += Vector.x;
	y += Vector.y;
	z += Vector.z;

	return ( *this );
}

Vector3f& Vector3f::operator-= ( const Vector3f& Vector )
{
	x -= Vector.x;
	y -= Vector.y;
	z -= Vector.z;

	return ( *this );
}

Vector3f& Vector3f::operator*= ( float fScalar )
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;

	return ( *this );
}

Vector3f& Vector3f::operator*= ( const Vector3f& Vector )
{
	x *= Vector.x;
	y *= Vector.y;
	z *= Vector.z;

	return ( *this );
}

Vector3f& Vector3f::operator/= ( float fScalar )
{
	if( fScalar != 0.0f )
	{
		float fInvScalar = 1.0f / fScalar;

		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
	}
	else
	{
		MakeZero();
	}

	return ( *this );
}

Vector3f& Vector3f::operator/= ( const  Vector3f& Vector )
{
	x = Vector.x != 0.0f ? x / Vector.x : 0.0f;
	y = Vector.y != 0.0f ? y / Vector.y : 0.0f;
	z = Vector.z != 0.0f ? z / Vector.z : 0.0f;

	return ( *this );
}

Vector3f Vector3f::Clamp( const Vector3f& A )
{
	// A 为const ,不能修改其值
	Vector3f vec = A;
	vec.Clamp();

	return vec;
}

Vector3f Vector3f::Cross( const Vector3f& A , const Vector3f& B )
{
	return A.Cross( B );
}

float Vector3f::Dot( const Vector3f& A , const Vector3f& B )
{
	return A.Dot( B );
}

float Vector3f::LengthSq( const Vector3f& A )
{
	return Dot( A , A );
}

Vector3f Vector3f::Normalize( const Vector3f& A )
{
	Vector3f vec = A;
	vec.Normalize();

	return vec;
}

Vector3f Vector3f::Perpendicular( const Vector3f& A )
{
	Vector3f vec = A;
	return vec.Perpendicular();
}