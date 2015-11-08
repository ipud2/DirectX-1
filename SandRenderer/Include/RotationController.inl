template<typename T>
RotationController::RotationController()
	:m_Axis( 0.0f , 1.0f , 0.0f ) ,
	m_Speed( 0.25f )
{
	// 默认沿着Y轴旋转
}

template<typename T>
RotationController::RotationController( Vector3f Axis , float speed )
{
	m_Axis = Axis;
	m_Speed = speed;
}

template<typename T>
RotationController::~RotationController()
{

}

template<typename T>
void RotationController::Update( float time )
{
	if( m_pEntity )
	{
		// 计算绕轴Axis旋转，速度为speed，旋转了time时间之后，对应的旋转矩阵
		Matrix3f delta;
		delta.RotationEuler( m_Axis , time * m_Speed );

		Matrix3f rotation = m_pEntity->GetTransformRef().GetRotation();
		m_pEntity->GetTransform().GetRotation() = rotation * delta;
	}
}

template<typename T>
void RotationController::SetAxis( Vector3f axis )
{
	m_Axis = axis;
}

template<typename T>
void RotationController::SetSpeed( float speed )
{
	m_Speed = speed;
}