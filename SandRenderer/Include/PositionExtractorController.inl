template<typename T>
PositionExtractorController<T>::PositionExtractorController()
	:m_pWriter( nullptr )
{

}

template<typename T>
PositionExtractorController<T>::~PositionExtractorController()
{

}

template<typename T>
void PositionExtractorController<T>::Update( float fTime )
{
	// ÏÈÅÐ¶ÏÊÇ·ñ´æÔÚ
	if( nullptr != m_pEntity && nullptr != m_pWriter )
	{
		Vector3f WorldPosition = m_pEntity->GetTransformRef().TransformPointLocalToWorld( m_pEntity->GetTransformRef().GetPositionRef() );
		m_pWriter->SetValue( Vector4f( WorldPosition , 1.0f ) );
	}
}

template<typename T>
void PositionExtractorController<T>::SetParameterWriter( VectorParameterWriter* pWriter )
{
	m_pWriter = pWriter;
}