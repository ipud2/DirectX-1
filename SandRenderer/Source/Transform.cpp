#include "PCH.h"
#include "Transform.h"

using namespace Sand;

Transform::Transform()
{
	// 默认值
	m_Translate.MakeZero();
	m_Rotate.MakeIdentity();
	m_Scaled = Vector3f( 1.0f , 1.0f , 1.0f );	

	m_World.MakeIdentity();
	m_Local.MakeIdentity();
}

Transform::~Transform()
{

}

Vector3f& Transform::GetTranslate()
{
	return m_Translate;
}

Matrix3f& Transform::GetRotation()
{
	return m_Rotate;
}

Vector3f& Transform::GetScale()
{
	return m_Scaled;
}

void Transform::UpdateLocal()
{
	// 根据translate ， scaled ， rotate计算local matrix
	m_Local.MakeIdentity();
	m_Local.SetRotation( m_Rotate );
	m_Local.SetTranslate( m_Translate );
	m_Local = Matrix4f::ScaleMatrix( m_Scaled ) * m_Local;
}

void Transform::UpdateWorld( const Matrix4f& parent )
{
	m_World = m_Local * parent;
}

void Transform::UpdateWorld()
{
	// 没有parent矩阵，
	m_World = m_Local;
}

const Matrix4f& Transform::GetLocalMatrix() const
{
	return m_Local;
}

const Matrix4f& Transform::GetWorldMatrix() const
{
	return m_World;
}

Matrix4f& Transform::GetLocalMatrix()
{
	return m_Local;
}

Matrix4f& Transform::GetWorldMatrix()
{
	return m_World;
}

Matrix4f Transform::GetView() const
{
	Vector3f Eye;
	Vector3f LookAt;
	Vector3f Up;

	Eye = m_World.GetTranslate();
	LookAt = m_World.GetTranslate() + m_World.GetBasisZ();
	Up = m_World.GetBasisY();

	return Matrix4f::LookAtLHMatrix( Eye , LookAt , Up );
}

Vector4f Transform::LocalToWorldSpace( const Vector4f& input )
{
	Vector4f result = GetWorldMatrix() * input;

	return result;
}

Vector4f Transform::WorldToLocalSpace( const Vector4f& input )
{
	Vector4f result = GetWorldMatrix().Inverse() * input;

	return result;
}

Vector3f Transform::TransformVectorLocalToWorld( const Vector3f& input )
{
	Vector4f result = LocalToWorldSpace( Vector4f( input , 0.0f ) );

	return result.xyz();
}

Vector3f Transform::TransformVectorWorldToLocal( const Vector3f& input )
{
	Vector4f result = WorldToLocalSpace( Vector4f( input , 0.0f ) );

	return result.xyz();
}

Vector3f Transform::TransformPointLocalToWorld( const Vector3f& input )
{
	Vector4f result = LocalToWorldSpace( Vector4f( input , 1.0f ) );

	return result.xyz();
}

Vector3f Transform::TransformVectorWorldToLocal( const Vector3f& input )
{
	Vector4f result = WorldToLocalSpace( Vector4f( input , 1.0f ) );

	return result.xyz();
}