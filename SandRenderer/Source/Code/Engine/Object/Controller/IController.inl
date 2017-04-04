template<typename T>
IController<T>::IController()
{
	m_pEntity = nullptr;
}

template<typename T>
IController<T>::~IController()
{

}

template<typename T>
void IController<T>::SetEntity( T* pEntity )
{
	m_pEntity = pEntity;
}

template<typename T>
T* IController<T>::GetEntity()
{
	return m_pEntity;
}