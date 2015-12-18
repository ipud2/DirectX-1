#ifndef Transform_h
#define Transform_h

#include "PCH.h"
#include "Vector3f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"

namespace Sand
{
	/*
		变换类
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

		// 返回视图矩阵
		Matrix4f GetView() const;

		// 将齐次坐标input从Local Space变换到World Space
		Vector4f LocalToWorldSpace( const Vector4f& input );
		// 将齐次坐标input从World Space到Local Space
		Vector4f WorldToLocalSpace( const Vector4f& input );

		// 将向量从Local Space变换到World Space
		Vector3f TransformVectorLocalToWorld( const Vector3f& input );
		// 将向量从World Space变换到Local Space
		Vector3f TransformVectorWorldToLocal( const Vector3f& input );

		// 将点从Local Space变换到World Space
		Vector3f TransformPointLocalToWorld( const Vector3f& input );
		// 将点从World Space变换到Local Space
		Vector3f TransformPointWorldToLocal( const Vector3f& input );

	protected:
		Vector3f m_Translate;		// 平移
		Matrix3f m_Rotate;			// 旋转矩阵
		Vector3f m_Scaled;			// 缩放
		Matrix4f m_World;			// 世界矩阵
		Matrix4f m_Local;			// 局部矩阵
	};
};
#endif