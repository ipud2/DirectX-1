#ifndef Vector3f_h
#define Vector3f_h

#include <cassert>

namespace Sand
{
	class Vector3f
	{
	public:
		inline Vector3f()
			:x( 0 ) , y( 0 ) , z( 0 )
		{

		}

		inline Vector3f( float _x , float _y , float _z )
			: x( _x ) , y( _y ) , z( _z )
		{

		}

		inline Vector3f( const Vector3f& rhs )
			: x( rhs.x ) , y( rhs.y ) , z( rhs.z )
		{

		}

		inline Vector3f( const float rhs[3] )
			: x( rhs[0] ) , y( rhs[1] ) , z( rhs[2] )
		{

		}

		static Vector3f Zero()
		{
			return Vector3f( 0.0f , 0.0f , 0.0f );
		}

	public:
		inline Vector3f& operator= ( const Vector3f& rhs )
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;

			return *this;
		}

		inline Vector3f operator+ ( const Vector3f& rhs ) const
		{
			return Vector3f( x + rhs.x , y + rhs.y , z + rhs.z );
		}

		inline Vector3f operator- ( const Vector3f& rhs ) const
		{
			return Vector3f( x - rhs.x , y - rhs.y , z - rhs.z );
		}

		inline Vector3f operator* ( const float scale ) const
		{
			return Vector3f( x * scale , y * scale , z * scale );
		}

		inline Vector3f operator* ( const Vector3f& rhs ) const
		{
			return Vector3f( x * rhs.x , y * rhs.y , z * rhs.z );
		}

		inline Vector3f operator- ( ) const
		{
			return Vector3f( -x , -y , -z );
		}

		inline Vector3f& operator+= ( const Vector3f& rhs )
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		inline Vector3f& operator-= ( const Vector3f& rhs )
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		inline Vector3f& operator*= ( const float scale )
		{
			x *= scale;
			y *= scale;
			z *= scale;

			return *this;
		}

		inline Vector3f& operator*= ( const Vector3f& rhs )
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		inline friend Vector3f operator* ( const float lhs , const Vector3f& rhs )
		{
			return Vector3f( lhs * rhs.x , lhs * rhs.y , lhs * rhs.z );
		}

		inline float operator[] ( int index ) const
		{
			assert( index < 3 );

			return m[index];
		}

		inline float& operator[] ( int index )
		{
			assert( index < 3 );

			return m[index];
		}

		inline bool operator== ( const Vector3f& Vector ) const
		{
			if ( ( x - Vector.x ) * ( x - Vector.x ) > 0.01f )
			{
				return false;
			}
			if ( ( y - Vector.y ) * ( y - Vector.y ) > 0.01f )
			{
				return false;
			}
			if ( ( z - Vector.z ) * ( z - Vector.z ) > 0.01f )
			{
				return false;
			}

			return true;
		}

		inline bool operator!= ( const Vector3f& Vector ) const
		{
			return ( !( *this == Vector ) );
		}

	public:
		inline friend float dot( const Vector3f& lhs , const Vector3f& rhs )
		{
			return ( lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z );
		}

		inline friend Vector3f cross( const Vector3f& lhs , const Vector3f& rhs )
		{
			return Vector3f( lhs.y * rhs.z - lhs.z * rhs.y ,
							 lhs.z * rhs.x - lhs.x * rhs.z ,
							 lhs.x * rhs.y - lhs.y * rhs.x );
		}

		inline friend void Clamp( Vector3f& rhs )
		{
			if ( rhs.x < 0.0f )
			{
				rhs.x = 0.0f;
			}
			else if ( rhs.x > 1.0f )
			{
				rhs.x = 1.0f;
			}

			if ( rhs.y < 0.0f )
			{
				rhs.y = 0.0f;
			}
			else if ( rhs.y > 1.0f )
			{
				rhs.y = 1.0f;
			}

			if ( rhs.z < 0.0f )
			{
				rhs.z = 0.0f;
			}
			else if ( rhs.z > 1.0f )
			{
				rhs.z = 1.0f;
			}
		}

		inline void MakeZero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

	public:
		void Normalize();
		float Magnitude();
		Vector3f Perpendicular();

		static Vector3f Random();
		static Vector3f Normalize( Vector3f& A );

	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float m[3];
		};
	};
};
#endif