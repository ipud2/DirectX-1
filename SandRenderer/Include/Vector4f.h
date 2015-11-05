#ifndef Vector4f_h
#define Vector4f_h

namespace Sand
{
	class Vector2f;
	class Vector3f;

	class Vector4f
	{
	public:
		Vector4f();
		Vector4f( float x , float y , float z , float w );
		Vector4f( const Vector3f& Vector , float w );
		Vector4f( const Vector4f& Vector );

		void Clamp();
		float Dot( const Vector4f& vector );
		void MakeZero();
		void Normalize();
		float Magnitude();

		Vector4f& operator= ( const Vector4f& Vector );

		float operator[] ( int iPos ) const;
		float& operator[] ( int iPos );

		bool operator== ( const Vector4f& Vector ) const;
		bool operator!= ( const Vector4f& Vector ) const;

		Vector4f operator+ ( const Vector4f& Vector ) const;
		Vector4f operator- ( const Vector4f& Vector ) const;
		Vector4f operator* ( float fScalar ) const;
		Vector4f operator* ( const Vector4f& Vector ) const;
		Vector4f operator/ ( float fScalar ) const;
		Vector4f operator/ ( const Vector4f& Vector ) const;
		Vector4f operator- ( ) const;

		Vector4f& operator+= ( const Vector4f& Vector );
		Vector4f& operator-= ( const Vector4f& Vector );
		Vector4f& operator*= ( float fScalar );
		Vector4f& operator*= ( const Vector4f& Vector );
		Vector4f& operator/= ( float fScalar );
		Vector4f& operator/= ( const Vector4f& Vector );

		unsigned int toARGB();
		unsigned int toRGBA();

		void fromARGB( unsigned int color );

		Vector3f xyz() const;
		Vector2f xy() const;

	public:
		float x;
		float y;
		float z;
		float w;
	};
};

#endif