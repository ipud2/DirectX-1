template<typename T>
SpatialController< T >::SpatialController()
	:m_Rotation( 0.0f , 0.0f , 0.0f ) ,
	m_Translate( 0.0f , 0.0f , 0.0f )
{

}

template<typename T>
SpatialController<T>::SpatialController( const Vector3f& Rotation , const Vector3f& Translate )
{
	m_Rotation = Rotation;
	m_Translate = Translate;
}

template<typename T>
SpatialController< T >::~SpatialController()
{

}

template<typename T>
void SpatialController< T >::Update( float time )
{
	// 让物体的发生旋转和平移
	if( m_pEntity )
	{
		// 设置旋转和平移
		m_pEntity->GetTransformRef().GetRotationRef().Rotation( m_Rotation );
		m_pEntity->GetTransformRef().GetPositionRef() = m_Translate;
	}
}

template<typename T>
void SpatialController< T >::SetRotation( const Vector3f& xyz )
{
	m_Rotation = xyz;
}

template<typename T>
void SpatialController< T >::SetTranslation( const Vector3f& translation )
{
	m_Translate = translation;
}

template<typename T>
Vector3f SpatialController< T >::GetRotation()
{
	return m_Rotation;
}

template<typename T>
Vector3f SpatialController< T >::GetTranslation()
{
	return m_Translate;
}

template<typename T>
void SpatialController< T >::RotateBy( const Vector3f& xyz )
{
	m_Rotation += xyz;
}

template<typename T>
void SpatialController< T >::RotateXBy( const Vector3f& x )
{
	m_Rotation.x += x;
}

template<typename T>
void SpatialController< T >::RotateYBy( const Vector3f& y )
{
	m_Rotation.y += y;
}

template<typename T>
void SpatialController< T >::RotateZBy( const Vector3f& z )
{
	m_Rotation.z += z;
}

template<typename T>
void SpatialController< T >::TranslateBy( Vector3f& xyz )
{
	m_Translate += xyz;
}

template<typename T>
void SpatialController< T >::TranslateXBy( const float x )
{
	m_Translate.x += x;
}

template<typename T>
void SpatialController< T >::TranslateYBy( const float y )
{
	m_Translate.y += y;
}

template<typename T>
void SpatialController< T >::TranslateZBy( const float z )
{
	m_Translate.z += z;
}

template<typename T>
void SpatialController< T >::MoveForward( const float dist )
{
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotationRef().GetRow( 2 ) * dist;
	}
}

template<typename T>
void SpatialController< T >::MoveBackward( const float dist )
{
	// TO DO-----------
	if( m_pEntity )
	{
		m_Translate -= m_pEntity->GetTransformRef().GetRotationRef().GetRow( 2 ) * dist;
	}
}

template<typename T>
void SpatialController< T >::MoveLeft( const float dist )
{
	// TO DO-----------
	if( m_pEntity )
	{
		m_Translate -= m_pEntity->GetTransformRef().GetRotationRef().GetRow( 0 ) * dist;
	}
}

template<typename T>
void SpatialController< T >::MoveRight( const float dist )
{
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotationRef().GetRow( 0 ) * dist;
	}
}

template<typename T>
void SpatialController< T >::MoveUp( const float dist )
{
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotationRef().GetRow( 1 ) * dist;
	}
}

template<typename T>
void SpatialController< T >::MoveDown( const float dist )
{
	// TO DO-----------
	if( m_pEntity )
	{
		m_Translate -= m_pEntity->GetTransformRef().GetRotationRef().GetRow( 1 ) * dist;
	}
}