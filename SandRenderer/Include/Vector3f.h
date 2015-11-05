#ifndef Vector3f_h
#define Vector3f_h

namespace Sand
{
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f( float x , float y , float z );
		Vector3f( const Vector3f& Vector );

		// 向量操作
		void Clamp();
		void MakeZero();
		void Normalize();
		float Magnitude();
		float Dot( const Vector3f& A ) const;
		Vector3f Cross( const Vector3f& A ) const;
		Vector3f Perpendicular();

		// 静态向量操作
		static Vector3f Clamp( const Vector3f& A );
		static Vector3f Normalize( const Vector3f& A );
		static float LengthSq( const Vector3f& A );
		static Vector3f Cross( const Vector3f& A , const Vector3f& B );
		static float Dot( const Vector3f& A , const Vector3f& B );
		static Vector3f Perpendicular( const Vector3f& A );
		static Vector3f Random();

		Vector3f& operator= ( const Vector3f& Vector );

		float operator[] ( int iPos ) const;
		float& operator[] ( int iPos );

		bool operator== ( const Vector3f& Vector ) const;
		bool operator!= ( const Vector3f& Vector ) const;

		Vector3f operator+ ( const Vector3f& Vector ) const;
		Vector3f operator- ( const Vector3f& Vector ) const;
		Vector3f operator* ( const Vector3f& Vector ) const;
		Vector3f operator* ( float fScalar ) const;
		Vector3f operator/ ( const Vector3f& Vector ) const;
		Vector3f operator/ ( float fScalar ) const;
		Vector3f operator- ( ) const;

		Vector3f& operator+= ( const Vector3f& Vector );
		Vector3f& operator-= ( const Vector3f& Vector );
		Vector3f& operator*= ( const Vector3f& Vector );
		Vector3f& operator*= ( float fScalar );
		Vector3f& operator/= ( const Vector3f& Vector );
		Vector3f& operator/= ( float fScalar );

	public:
		float x;
		float y;
		float z;
	};
};
#endif