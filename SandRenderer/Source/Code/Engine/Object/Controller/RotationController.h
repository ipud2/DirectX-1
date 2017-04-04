#ifndef RotationController_h
#define RotationController_h

#include "Engine/Object/Controller/IController.h"
#include "Engine/Math/Vector3f.h"
#include "Engine/Math/Matrix3f.h"

namespace Sand
{
	/*
		�������Զ���ת
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
		// ��ת��
		Vector3f m_Axis;
		// ��ת�ٶ�
		float m_Speed;
	};

#include "RotationController.inl"
};
#endif