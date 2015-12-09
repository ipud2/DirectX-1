template<typename T>
OrientationController<T>::OrientationController()
{
	m_Rotate.MakeIdentity();
}

template<typename T>
OrientationController<T>::~OrientationController()
{

}

template<typename T>
void OrientationController<T>::Update( float time )
{
	if ( m_pEntity )
	{
		m_pEntity->GetTransformRef().GetRotationRef() = m_Rotate;
	}
}

template<typename T>
void OrientationController<T>::Pitch( float angle )
{
	/*
		����right��ת

		ֻ����תup��look��������
	*/

	// ������ת��������World.GetBasisX() , ��תangle
	Matrix3f R;
	R.RotateAxis( m_Rotate.GetRow( 0 ) , angle );

	Vector3f Up = m_Rotate.GetRow( 1 ) * R;
	Vector3f Look = m_Rotate.GetRow( 2 ) * R;

	Look.Normalize();

	Vector3f Right = Up.Cross( Look );
	Right.Normalize();

	Up = Look.Cross( Right );
	Up.Normalize();

	m_Rotate.SetRow( 0 , Right );
	m_Rotate.SetRow( 1 , Up );
	m_Rotate.SetRow( 2 , Look );
}

template<typename T>
void OrientationController<T>::RotateY( float angle )
{
	/*
		����Y����ת
	*/

	Matrix3f R;
	R.RotationY( angle );

	Vector3f Right = m_Rotate.GetRow( 0 ) * R;
	Vector3f Up = m_Rotate.GetRow( 1 ) * R;
	Vector3f Look = m_Rotate.GetRow( 2 ) * R;

	Look.Normalize();

	Right = Up.Cross( Look );
	Right.Normalize();

	Up = Look.Cross( Right );
	Up.Normalize();

	m_Rotate.SetRow( 0 , Right );
	m_Rotate.SetRow( 1 , Up );
	m_Rotate.SetRow( 2 , Look );
}