template<typename T>
SpatialController::SpatialController()
	:m_Rotation( 0.0f , 0.0f , 0.0f ) ,
	m_Translate( 0.0f , 0.0f , 0.0f )
{

}

template<typename T>
SpatialController::SpatialController( const Vector3f& Rotation , const Vector3f& Translate )
{
	m_Rotation = Rotation;
	m_Translate = Translate;
}

template<typename T>
SpatialController::~SpatialController()
{

}

template<typename T>
void SpatialController::Update( float time )
{
	// 让物体的发生旋转和平移
	if( m_pEntity )
	{
		// 设置旋转和平移
		m_pEntity->GetTransformRef().GetRotation().Rotate( m_Rotation );
		m_pEntity->GetTransformRef().GetTranslate() = m_Translate;
	}
}

template<typename T>
void SpatialController::SetRotation( const Vector3f& xyz )
{
	m_Rotation = xyz;
}

template<typename T>
void SpatialController::SetTranslation( const Vector3f& translation )
{
	m_Translate = translation;
}

template<typename T>
Vector3f SpatialController::GetRotation()
{
	return m_Rotation;
}

template<typename T>
Vector3f SpatialController::GetTranslation()
{
	return m_Translate;
}

template<typename T>
void SpatialController::RotateBy( const Vector3f& xyz )
{
	m_Rotation += xyz;
}

template<typename T>
void SpatialController::RotateXBy( const Vector3f& x )
{
	m_Rotation.x += x;
}

template<typename T>
void SpatialController::RotateYBy( const Vector3f& y )
{
	m_Rotation.y += y;
}

template<typename T>
void SpatialController::RotateZBy( const Vector3f& z )
{
	m_Rotation.z += z;
}

template<typename T>
void SpatialController::TranslateBy( Vector3f& xyz )
{
	m_Translate += xyz;
}

template<typename T>
void SpatialController::TranslateXBy( const float x )
{
	m_Translate.x += x;
}

template<typename T>
void SpatialController::TranslateYBy( const float y )
{
	m_Translate.y += y;
}

template<typename T>
void SpatialController::TranslateZBy( const float z )
{
	m_Translate.z += z;
}

template<typename T>
void SpatialController::MoveForward( const float dist )
{
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotation().GetRow( 2 ) * dist;
	}
}

template<typename T>
void SpatialController::MoveBackward( const float dist )
{
	// TO DO-----------
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotation().GetRow( 2 ) * dist;
	}
}

template<typename T>
void SpatialController::MoveLeft( const float dist )
{
	// TO DO-----------
	if( m_pEntity )
	{
		m_Translate -= m_pEntity->GetTransformRef().GetRotation.GetRow( 0 ) * dist;
	}
}

template<typename T>
void SpatialController::MoveRight( const float dist )
{
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotation.GetRow( 0 ) * dist;
	}
}

template<typename T>
void SpatialController::MoveUp( const float dist )
{
	if( m_pEntity )
	{
		m_Translate += m_pEntity->GetTransformRef().GetRotation.GetRow( 1 ) * dist;
	}
}

template<typename T>
void SpatialController::MoveDown( const float dist )
{
	// TO DO-----------
	if( m_pEntity )
	{
		m_Translate -= m_pEntity->GetTransformRef().GetRotation.GetRow( 1 ) * dist;
	}
}