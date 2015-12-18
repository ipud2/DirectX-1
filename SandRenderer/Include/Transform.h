#ifndef Transform_h
#define Transform_h

#include "PCH.h"
#include "Vector3f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"

namespace Sand
{
	/*
		�任��
	*/
	class Transform
	{
	public:
		Transform();
		~Transform();

		// access
		Vector3f& GetPositionRef();
		Matrix3f& GetRotationRef();
		Vector3f& GetScaleRef();

		void UpdateLocal();
		void UpdateWorld( const Matrix4f& parent );
		void UpdateWorld();

		const Matrix4f& GetLocalMatrix() const;
		const Matrix4f& GetWorldMatrix() const;
		Matrix4f& GetLocalMatrix();
		Matrix4f& GetWorldMatrix();

		// ������ͼ����
		Matrix4f GetView() const;

		// ���������input��Local Space�任��World Space
		Vector4f LocalToWorldSpace( const Vector4f& input );
		// ���������input��World Space��Local Space
		Vector4f WorldToLocalSpace( const Vector4f& input );

		// ��������Local Space�任��World Space
		Vector3f TransformVectorLocalToWorld( const Vector3f& input );
		// ��������World Space�任��Local Space
		Vector3f TransformVectorWorldToLocal( const Vector3f& input );

		// �����Local Space�任��World Space
		Vector3f TransformPointLocalToWorld( const Vector3f& input );
		// �����World Space�任��Local Space
		Vector3f TransformPointWorldToLocal( const Vector3f& input );

	protected:
		Vector3f m_Translate;		// ƽ��
		Matrix3f m_Rotate;			// ��ת����
		Vector3f m_Scaled;			// ����
		Matrix4f m_World;			// �������
		Matrix4f m_Local;			// �ֲ�����
	};
};
#endif