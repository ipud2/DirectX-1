#ifndef Vector2f_h
#define Vector2f_h

namespace Sand
{
	class Vector2f
	{
	public:
		Vector2f();
		Vector2f( float x , float y );
		Vector2f( const Vector2f& Vector );

		void Clamp();
		void MakeZero();
		void Normalize();
		float Magnitude();	// ³¤¶È

		Vector2f& operator= ( const Vector2f& Vector );

		// ²Ù×÷·ûÖØÔØ
		float operator[] ( int iPos ) const;
		float& operator[] ( int iPos );

		bool operator== ( const Vector2f& Vector ) const;
		bool operator!= ( const Vector2f& Vector ) const;

		Vector2f operator+ ( const Vector2f& Vector ) const;
		Vector2f operator- ( const Vector2f& Vector ) const;
		Vector2f operator* ( const Vector2f& Vector ) const;
		Vector2f operator* ( float fScalar ) const;
		Vector2f operator/ ( float fScalar ) const;
		Vector2f operator- ( ) const;

		Vector2f& operator+= ( const Vector2f& Vector );
		Vector2f& operator-= ( const Vector2f& Vector );
		Vector2f& operator*= ( float fScalar );
		Vector2f& operator/= ( float fScalar );

	public:
		float x;
		float y;
	};
};
#endif