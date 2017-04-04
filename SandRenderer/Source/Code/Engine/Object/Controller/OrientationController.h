/*
	���ר��
	���������ת�ӽ�
	����ʵ�壬��ʹ�øÿ�����������SpatialController�е�Rotate���ͻ
*/
#ifndef OrientationController_h
#define OrientationController_h

#include "Engine/Object/Controller/IController.h"
#include "Engine/Math/Matrix3f.h"
#include "Engine/Math/Matrix4f.h"
#include "Engine/Object/Scene/Entity.h"
#include "Engine/Object/Scene/Node.h"

namespace Sand
{
	template<typename T>
	class OrientationController : public IController< T > 
	{
	public:
		OrientationController();
		~OrientationController();

		virtual void Update( float time );

		void Pitch( float angle );

		void RotateY( float angle );

		void SetLook( const Vector3f& Dir );

	protected:
		Matrix3f m_Rotate;
	};

#include "OrientationController.inl"
};
#endif