#ifndef RotationController_h
#define RotationController_h

#include "IController.h"
#include "Vector3f.h"
#include "Matrix3f.h"

namespace Sand
{
	/*
		让物体自动旋转
	*/
	template<typename T>
	class RotationController : public IController < T > 
	{
	public:
		RotationController();
		RotationController( Vector3f Axis , float speed );
		virtual ~RotationController();

		virtual void Update( float time );

		void SetAxis( Vector3f axis );
		void SetSpeed( float speed );

	protected:
		// 旋转轴
		Vector3f m_Axis;
		// 旋转速度
		float m_Speed;
	};

#include "RotationController.inl"
};
#endif