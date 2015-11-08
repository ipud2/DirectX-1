#ifndef SpatialController_h
#define SpatialController_h

#include "IController.h"
#include "Vector3f.h"
#include "Entity.h"

namespace Sand
{
	// 
	template<typename T>
	class SpatialController : public IController<T>
	{
	public:
		SpatialController();
		SpatialController( const Vector3f& Rotation , const Vector3f& Translate );
		~SpatialController();

		virtual void Update( float time );

		void SetRotation( const Vector3f& xyz );
		void SetTranslation( const Vector3f& translation );

		Vector3f GetRotation();
		Vector3f GetTranslation();

		// -----------旋转----------------
		void RotateBy( const Vector3f& xyz );
		void RotateXBy( const Vector3f& x );
		void RotateYBy( const Vector3f& y );
		void RotateZBy( const Vector3f& z );

		// ------------平移-----------------------
		void TranslateBy( Vector3f& xyz );
		void TranslateXBy( const float x );
		void TranslateYBy( const float y );
		void TranslateZBy( const float z );

		
		// ------------Move---------------------
		void MoveForward( const float dist );
		void MoveBackward( const float dist );
		void MoveRight( const float dist );
		void MoveLeft( const float dist );
		void MoveUp( const float dist );
		void MoveDown( const float dist );

	protected:
		// 旋转
		Vector3f m_Rotation;
		// 平移
		Vector3f m_Translate;
	};

#include "SpatialController.inl"
};
#endif