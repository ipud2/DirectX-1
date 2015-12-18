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

	// ��xAbsΪ��Сֵ����ҪôxAbsΪ0.0f
	// ҪôxAbs��0.0f�󣬵�������������
	// ���xAbs��0.0f����˵��������y��zƽ��
	// ��(1.0f , 0.0f , 0.0f)���䲻���ߣ�
	// ��Cross�õ��Ľ�����Ǻ�ԭ������ֱ��
	// ���xAbs����0.0f,��ȴ����Сֵ��
	// ��ô˵���������϶�������(1.0f , 0.0f , 0.0f)����
	// ����Cross�õ��Ľ��Ҳ����������Ҫ��
	// yAbs,zAbsΪ��Сֵ�����ͬ��
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
	// ��Χ��-1.0f ~ 1.0f
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