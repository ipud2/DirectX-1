#ifndef Matrix3f_h
#define Matrix3f_h

#include "Vector3f.h"

namespace Sand
{
	class Matrix3f
	{
	public:
		Matrix3f();
		Matrix3f( bool bZero );
		Matrix3f( const Matrix3f& Matrix );
		Matrix3f( float fM11 , float fM12 , float fM13 ,
				  float fM21 , float fM22 , float fM23 ,
				  float fM31 , float fM32 , float fM33 );

		void RotationX( float fRadians );
		void RotationY( float fRadians );
		void RotationZ( float fRadians );

		void Rotation( Vector3f& Rot );
		void RotationZYX( Vector3f& Rot );
		void RotationEuler( Vector3f& Axis , float Angle );
		void Orthonormalize();

		void MakeZero();
		void MakeIdentity();
		void MakeTranspose();

		Matrix3f Zero();
		Matrix3f Identity();
		Matrix3f Transpose();

		Matrix3f& operator= ( const Matrix3f& Matrix );

		float operator() ( int iRow , int iCol ) const;
		float& operator() ( int iRow , int iCol );
		float operator[] ( int iPos ) const;
		float& operator[] ( int iPos );

		void SetRow( int iRow , const Vector3f& Vector );
		Vector3f GetRow( int iRow ) const;
		void SetColumn( int iCol , const Vector3f& Vector );
		Vector3f GetColumn( int iCol ) const;

		bool operator== ( const Matrix3f& Matrix ) const;
		bool operator!= ( const Matrix3f& Matrix ) const;

		Matrix3f operator+ ( const Matrix3f& Matrix ) const;
		Matrix3f operator- ( const Matrix3f& Matrix ) const;
		Matrix3f operator* ( const Matrix3f& Matrix ) const;
		Matrix3f operator* ( float fScalar ) const;
		Matrix3f operator/ ( float fScalar ) const;
		Matrix3f operator- ( ) const;

		Matrix3f& operator+= ( const Matrix3f& Matrix );
		Matrix3f& operator-= ( const Matrix3f& Matrix );
		Matrix3f& operator*= ( const Matrix3f& Maatrix );
		Matrix3f& operator*= ( float fScalar );
		Matrix3f& operator/= ( float fScalar );

		Vector3f operator* ( const Vector3f& rKV ) const;

	protected:
		float m_afEntry[3 * 3];		// array float => af

		static int I( int iRow , int iCol );	// iRow * N + iCol
	};
}

#endif