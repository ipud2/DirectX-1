#include <Engine/PCH.h>
#include "Engine/Math/Matrix3f.h"
#include "Engine/Math/Vector3f.h"

using namespace Sand;

Matrix3f::Matrix3f()
{

}

Matrix3f::Matrix3f( bool bZero )
{
	if( bZero )
	{
		memset( m_afEntry , 0 , 3 * 3 * sizeof( float ) );
	}
}

Matrix3f::Matrix3f( const Matrix3f& Matrix )
{
	memcpy( m_afEntry , ( void* )&Matrix , 9 * sizeof( float ) );
}

Matrix3f::Matrix3f( float fM11 , float fM12 , float fM13 ,
					float fM21 , float fM22 , float fM23 ,
					float fM31 , float fM32 , float fM33 )
{
	m_afEntry[0] = fM11;
	m_afEntry[1] = fM12;
	m_afEntry[2] = fM13;

	m_afEntry[3] = fM21;
	m_afEntry[4] = fM22;
	m_afEntry[5] = fM23;

	m_afEntry[6] = fM31;
	m_afEntry[7] = fM32;
	m_afEntry[8] = fM33;
}

Matrix3f& Matrix3f::operator= ( const Matrix3f& Matrix )
{
	memcpy( m_afEntry , Matrix.m_afEntry , 9 * sizeof( float ) );

	return *this;
}

void Matrix3f::RotationX( float fRadians )
{
	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	m_afEntry[0] = 1.0f;	m_afEntry[1] = 0.0f;	m_afEntry[2] = 0.0f;
	m_afEntry[3] = 0.0f;	m_afEntry[4] = fCos;	m_afEntry[5] = fSin;
	m_afEntry[6] = 0.0f;	m_afEntry[7] = -fSin;	m_afEntry[8] = fCos;
}

void Matrix3f::RotationY( float fRadians )
{
	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	m_afEntry[0] = fCos;	m_afEntry[1] = 0.0f;	m_afEntry[2] = -fSin;
	m_afEntry[3] = 0.0f;	m_afEntry[4] = 1.0f;	m_afEntry[5] = 0.0f;
	m_afEntry[6] = fSin;	m_afEntry[7] = 0.0f;	m_afEntry[8] = fCos;
}

void Matrix3f::RotationZ( float fRadians )
{
	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	m_afEntry[0] = fCos;	m_afEntry[1] = fSin;	m_afEntry[2] = 0.0f;
	m_afEntry[3] = -fSin;	m_afEntry[4] = fCos;	m_afEntry[5] = 0.0f;
	m_afEntry[6] = 0.0f;	m_afEntry[7] = 0.0f;	m_afEntry[8] = 1.0f;
}

void Matrix3f::Rotation( Vector3f& Rot )
{
	Matrix3f mRot1;
	Matrix3f mRot2;

	mRot1.RotationZ( Rot.z );
	mRot2.RotationX( Rot.x );
	mRot1 *= mRot2;
	mRot2.RotationY( Rot.y );
	mRot1 *= mRot2;
	*this = mRot1;
}

void Matrix3f::RotationZYX( Vector3f& Rot )
{
	Matrix3f mRot1;
	Matrix3f mRot2;

	mRot1.RotationZ( Rot.z );
	mRot2.RotationY( Rot.y );
	mRot1 *= mRot2;
	mRot2.RotationX( Rot.x );
	mRot1 *= mRot2;
	*this = mRot1;
}

void Matrix3f::RotationEuler( Vector3f& Axis , float Angle )
{
	float s = sinf( Angle );
	float c = cosf( Angle );
	float t = 1 - c;

	m_afEntry[0] = t * Axis.x * Axis.x + c;				m_afEntry[1] = Axis.x * Axis.y * t + Axis.z * s;	m_afEntry[2] = Axis.x * Axis.z * t - Axis.y * s;
	m_afEntry[3] = Axis.x * Axis.y * t - Axis.z * s;	m_afEntry[4] = Axis.y * Axis.y * t + c;				m_afEntry[5] = Axis.y * Axis.z * t + Axis.x * s;
	m_afEntry[6] = Axis.x * Axis.z * t + Axis.y * s;	m_afEntry[7] = Axis.y * Axis.z * t - Axis.x * s;	m_afEntry[8] = Axis.z * Axis.z * t + c;
}

void Matrix3f::Orthonormalize()
{
	// 使用施密特正交化方法
	float fInvLength = static_cast< float >( 1.0f / sqrtf( m_afEntry[0] * m_afEntry[0] + m_afEntry[3] * m_afEntry[3] + m_afEntry[6] * m_afEntry[6] ) );

	m_afEntry[0] *= fInvLength;
	m_afEntry[3] *= fInvLength;
	m_afEntry[6] *= fInvLength;

	float fDot0 = m_afEntry[0] * m_afEntry[1] + m_afEntry[3] * m_afEntry[4] + m_afEntry[6] * m_afEntry[7];

	m_afEntry[1] -= fDot0 * m_afEntry[0];
	m_afEntry[4] -= fDot0 * m_afEntry[3];
	m_afEntry[7] -= fDot0 * m_afEntry[6];

	fInvLength = static_cast< float >( 1.0f / sqrtf( m_afEntry[1] * m_afEntry[1] + m_afEntry[4] * m_afEntry[4] + m_afEntry[7] * m_afEntry[7] ) );

	m_afEntry[1] *= fInvLength;
	m_afEntry[4] *= fInvLength;
	m_afEntry[7] *= fInvLength;

	float fDot1 = m_afEntry[0] * m_afEntry[2] + m_afEntry[3] * m_afEntry[5] + m_afEntry[6] * m_afEntry[8];
	float fDot2 = m_afEntry[1] * m_afEntry[2] + m_afEntry[4] * m_afEntry[5] + m_afEntry[7] * m_afEntry[8];

	m_afEntry[2] -= ( fDot1 * m_afEntry[0] + fDot2 * m_afEntry[1] );
	m_afEntry[5] -= ( fDot1 * m_afEntry[3] + fDot2 * m_afEntry[4] );
	m_afEntry[8] -= ( fDot1 * m_afEntry[6] + fDot2 * m_afEntry[7] );

	fInvLength = static_cast< float >( 1.0f / sqrtf( m_afEntry[2] * m_afEntry[2] + m_afEntry[5] * m_afEntry[5] + m_afEntry[8] * m_afEntry[8] ) );

	m_afEntry[2] *= fInvLength;
	m_afEntry[5] *= fInvLength;
	m_afEntry[8] *= fInvLength;
}

float Matrix3f::operator[] ( int iPos ) const
{
	return ( m_afEntry[iPos] );
}

float& Matrix3f::operator[] ( int iPos )
{
	return m_afEntry[iPos];
}

float Matrix3f::operator() ( int iRow , int iCol ) const
{
	return ( m_afEntry[I( iRow , iCol )] );
}

float& Matrix3f::operator() ( int iRow , int iCol )
{
	return ( m_afEntry[I( iRow , iCol )] );
}

bool Matrix3f::operator== ( const Matrix3f& Matrix ) const
{
	// 比较m_afEntry和Matrix.m_afEntry中的前9 * sizeof(float)个字节
	// 该函数按字节比较
	// 如果相等，则返回0
	return ( memcmp( m_afEntry , Matrix.m_afEntry , 3 * 3 * sizeof( float ) ) == 0 );
}

bool Matrix3f::operator!= ( const Matrix3f& Matrix ) const
{
	return ( memcmp( m_afEntry , Matrix.m_afEntry , 3 * 3 * sizeof( float ) ) != 0 );
}

Matrix3f Matrix3f::operator+ ( const Matrix3f& Matrix ) const
{
	Matrix3f sum;

	for( int i = 0; i < 3 * 3; i++ )
	{
		sum.m_afEntry[i] = m_afEntry[i] + Matrix.m_afEntry[i];
	}

	return sum;
}

Matrix3f Matrix3f::operator- ( const Matrix3f& Matrix ) const
{
	Matrix3f diff;

	for( int i = 0; i < 3 * 3; i++ )
	{
		diff.m_afEntry[i] = m_afEntry[i] - Matrix.m_afEntry[i];
	}

	return diff;
}

Matrix3f Matrix3f::operator* ( const Matrix3f& Matrix ) const
{
	Matrix3f prod;

	prod.m_afEntry[0] = m_afEntry[0] * Matrix.m_afEntry[0] + m_afEntry[1] * Matrix.m_afEntry[3] + m_afEntry[2] * Matrix.m_afEntry[6];
	prod.m_afEntry[1] = m_afEntry[0] * Matrix.m_afEntry[1] + m_afEntry[1] * Matrix.m_afEntry[4] + m_afEntry[2] * Matrix.m_afEntry[7];
	prod.m_afEntry[2] = m_afEntry[0] * Matrix.m_afEntry[2] + m_afEntry[1] * Matrix.m_afEntry[5] + m_afEntry[2] * Matrix.m_afEntry[8];

	prod.m_afEntry[3] = m_afEntry[3] * Matrix.m_afEntry[0] + m_afEntry[4] * Matrix.m_afEntry[3] + m_afEntry[5] * Matrix.m_afEntry[6];
	prod.m_afEntry[4] = m_afEntry[3] * Matrix.m_afEntry[1] + m_afEntry[4] * Matrix.m_afEntry[4] + m_afEntry[5] * Matrix.m_afEntry[7];
	prod.m_afEntry[5] = m_afEntry[3] * Matrix.m_afEntry[2] + m_afEntry[4] * Matrix.m_afEntry[5] + m_afEntry[5] * Matrix.m_afEntry[8];

	prod.m_afEntry[6] = m_afEntry[6] * Matrix.m_afEntry[0] + m_afEntry[7] * Matrix.m_afEntry[3] + m_afEntry[8] * Matrix.m_afEntry[6];
	prod.m_afEntry[7] = m_afEntry[6] * Matrix.m_afEntry[1] + m_afEntry[7] * Matrix.m_afEntry[4] + m_afEntry[8] * Matrix.m_afEntry[7];
	prod.m_afEntry[8] = m_afEntry[6] * Matrix.m_afEntry[2] + m_afEntry[7] * Matrix.m_afEntry[5] + m_afEntry[8] * Matrix.m_afEntry[8];

	return prod;
}

Matrix3f Matrix3f::operator* ( float fScalar ) const
{
	Matrix3f prod;

	for( int i = 0; i < 3 * 3; i++ )
	{
		prod.m_afEntry[i] = m_afEntry[i] * fScalar;
	}

	return prod;
}

Matrix3f Matrix3f::operator/ ( float fScalar ) const
{
	Matrix3f quot;
	if( fScalar != 0.0f )
	{
		float fInvScalar = 1.0f / fScalar;

		for( int i = 0; i < 3 * 3; i++ )
		{
			quot.m_afEntry[i] = m_afEntry[i] * fInvScalar;
		}
	}
	else
	{
		for( int i = 0; i < 3 * 3; i++ )
		{
			quot.m_afEntry[i] = 0.0f;
		}
	}

	return quot;
}

Matrix3f Matrix3f::operator- ( ) const
{
	Matrix3f neq;

	for( int i = 0; i < 3 * 3; i++ )
	{
		neq.m_afEntry[i] = -m_afEntry[i];
	}

	return neq;
}

Matrix3f& Matrix3f::operator+= ( const Matrix3f& Matrix )
{
	for( int i = 0; i < 3 * 3; i++ )
	{
		m_afEntry[i] += Matrix.m_afEntry[i];
	}

	return ( *this );
}

Matrix3f& Matrix3f::operator-= ( const Matrix3f& Matrix )
{
	for( int i = 0; i < 3 * 3; i++ )
	{
		m_afEntry[i] -= Matrix.m_afEntry[i];
	}

	return ( *this );
}

Matrix3f& Matrix3f::operator*= ( const Matrix3f& Matrix )
{
	// 复制数据
	Matrix3f temp = *this;

	m_afEntry[0] = temp.m_afEntry[0] * Matrix.m_afEntry[0] + temp.m_afEntry[1] * Matrix.m_afEntry[3] + temp.m_afEntry[2] * Matrix.m_afEntry[6];
	m_afEntry[1] = temp.m_afEntry[0] * Matrix.m_afEntry[1] + temp.m_afEntry[1] * Matrix.m_afEntry[4] + temp.m_afEntry[2] * Matrix.m_afEntry[7];
	m_afEntry[2] = temp.m_afEntry[0] * Matrix.m_afEntry[2] + temp.m_afEntry[1] * Matrix.m_afEntry[5] + temp.m_afEntry[2] * Matrix.m_afEntry[8];

	m_afEntry[3] = temp.m_afEntry[3] * Matrix.m_afEntry[0] + temp.m_afEntry[4] * Matrix.m_afEntry[3] + temp.m_afEntry[5] * Matrix.m_afEntry[6];
	m_afEntry[4] = temp.m_afEntry[3] * Matrix.m_afEntry[1] + temp.m_afEntry[4] * Matrix.m_afEntry[4] + temp.m_afEntry[5] * Matrix.m_afEntry[7];
	m_afEntry[5] = temp.m_afEntry[3] * Matrix.m_afEntry[2] + temp.m_afEntry[4] * Matrix.m_afEntry[5] + temp.m_afEntry[5] * Matrix.m_afEntry[8];

	m_afEntry[6] = temp.m_afEntry[6] * Matrix.m_afEntry[0] + temp.m_afEntry[7] * Matrix.m_afEntry[3] + temp.m_afEntry[8] * Matrix.m_afEntry[6];
	m_afEntry[7] = temp.m_afEntry[6] * Matrix.m_afEntry[1] + temp.m_afEntry[7] * Matrix.m_afEntry[4] + temp.m_afEntry[8] * Matrix.m_afEntry[7];
	m_afEntry[8] = temp.m_afEntry[6] * Matrix.m_afEntry[2] + temp.m_afEntry[7] * Matrix.m_afEntry[5] + temp.m_afEntry[8] * Matrix.m_afEntry[8];

	return *this;
}

Matrix3f& Matrix3f::operator*= ( float fScalar )
{
	for( int i = 0; i < 3 * 3; i++ )
	{
		m_afEntry[i] *= fScalar;
	}

	return ( *this );
}

Matrix3f& Matrix3f::operator/= ( float fScalar )
{
	if( fScalar != 0.0f )
	{
		float fInvScalar = 1.0f / fScalar;

		for( int i = 0; i < 3 * 3; i++ )
		{
			m_afEntry[i] *= fInvScalar;
		}
	}
	else
	{
		for( int i = 0; i < 3 * 3; i++ )
		{
			m_afEntry[i] = 0.0f;
		}
	}

	return ( *this );
}

void Matrix3f::MakeZero()
{
	memset( m_afEntry , 0 , 3 * 3 * sizeof( float ) );
}

void Matrix3f::MakeIdentity()
{
	for( int iRow = 0; iRow < 3; iRow++ )
	{
		for( int iCol = 0; iCol < 3; iCol++ )
		{
			if( iRow == iCol )
			{
				m_afEntry[I( iRow , iCol )] = 1.0f;
			}
			else
			{
				m_afEntry[I( iRow , iCol )] = 0.0f;
			}
		}
	}
}

void Matrix3f::MakeTranspose()
{
	Matrix3f mTranspose;

	for( int iRow = 0; iRow < 3; iRow++ )
	{
		for( int iCol = 0; iCol < 3; iCol++ )
		{
			mTranspose.m_afEntry[I( iRow , iCol )] = m_afEntry[I( iCol , iRow )];
		}
	}

	memcpy( m_afEntry , mTranspose.m_afEntry , 3 * 3 * sizeof( float ) );
}

Matrix3f Matrix3f::Zero()
{
	Matrix3f Return = Matrix3f( true );

	return Return;
}

Matrix3f Matrix3f::Identity()
{
	Matrix3f Iden;

	for( int iRow = 0; iRow < 3; iRow++ )
	{
		for( int iCol = 0; iCol < 3; iCol++ )
		{
			if( iRow == iCol )
			{
				Iden[I( iRow , iCol )] = 1.0f;
			}
			else
			{
				Iden[I( iRow , iCol )] = 0.0f;
			}
		}
	}

	return Iden;
}

Matrix3f Matrix3f::Transpose()
{
	Matrix3f mTranspose;

	for( int iRow = 0; iRow < 3; iRow++ )
	{
		for( int iCol = 0; iCol < 3; iCol++ )
		{
			mTranspose[I( iRow , iCol )] = m_afEntry[I( iCol , iRow )];
		}
	}

	return mTranspose;
}

int Matrix3f::I( int iRow , int iCol )
{
	return ( iRow * 3 + iCol );
}

// matrix * vector
Vector3f Matrix3f::operator* ( const Vector3f& Vector ) const
{
	Vector3f prod;

	prod.x = m_afEntry[0] * Vector.x + m_afEntry[1] * Vector.y + m_afEntry[2] * Vector.z;
	prod.y = m_afEntry[3] * Vector.x + m_afEntry[4] * Vector.y + m_afEntry[5] * Vector.z;
	prod.z = m_afEntry[6] * Vector.x + m_afEntry[7] * Vector.y + m_afEntry[8] * Vector.z;

	return prod;
}

void Matrix3f::SetRow( int iRow , const Vector3f& Vector )
{
	for( int iCol = 0; iCol < 3; iCol++ )
	{
		m_afEntry[I( iRow , iCol )] = Vector[iCol];
	}
}

Vector3f Matrix3f::GetRow( int iRow ) const
{
	Vector3f vRow;

	for( int iCol = 0; iCol < 3; iCol++ )
	{
		vRow[iCol] = m_afEntry[I( iRow , iCol )];
	}

	return vRow;
}

void Matrix3f::SetColumn( int iCol , const Vector3f& Vector )
{
	for( int iRow = 0; iRow < 3; iRow++ )
	{
		m_afEntry[I( iRow , iCol )] = Vector[iRow];
	}
}

Vector3f Matrix3f::GetColumn( int iCol ) const
{
	Vector3f vCol;

	for( int iRow = 0; iRow < 3; iRow++ )
	{
		vCol[iRow] = m_afEntry[I( iRow , iCol )];
	}

	return vCol;
}

void Matrix3f::RotateAxis( Vector3f& Axis , float angle )
{
	float x = Axis.x;
	float y = Axis.y;
	float z = Axis.z;

	float Cos = cosf( angle );
	float OneSubCos = 1 - cosf( angle );
	float Sin = sinf( angle );

	m_afEntry[0] = x * x * OneSubCos + Cos;		m_afEntry[1] = x * y * OneSubCos + z * Sin;		m_afEntry[2] = x * z * OneSubCos - y * Sin;
	m_afEntry[3] = x * y * OneSubCos - z * Sin;	m_afEntry[4] = y * y * OneSubCos + Cos;			m_afEntry[5] = y * z * OneSubCos + x * Sin;
	m_afEntry[6] = x * z * OneSubCos + y * Sin;	m_afEntry[7] = y * z * OneSubCos - x * Sin;		m_afEntry[8] = z * z * OneSubCos + Cos;
}

//Vector3f operator* ( const Vector3f& v , const Matrix3f& matrix )
//{
//	return Vector3f( v.x * matrix[0] + v.y * matrix[3] + v.z * matrix[6] ,
//					 v.x * matrix[1] + v.y * matrix[4] + v.z * matrix[7] ,
//					 v.x * matrix[2] + v.y * matrix[5] + v.z * matrix[8] );
//}