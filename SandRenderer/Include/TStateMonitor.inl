template<class T>
TStateMonitor<T>::TStateMonitor( T initializeState )
	:m_bUploadNeeded( false ) ,

	m_InitializeState( initializeState ) ,
	m_State( initializeState ) ,

	m_pSister( nullptr )
{
	InitializeState();
	ResetTracking();
}

template<class T>
TStateMonitor<T>::~TStateMonitor()
{

}

template<class T>
void TStateMonitor<T>::SetSister( TStateMonitor<T>* pSister )
{
	m_pSister = pSister;
}

template<class T>
bool TStateMonitor<T>::SameAsSister()
{
	return ( m_State == m_pSister->GetState() );
}

template<class T>
void TStateMonitor<T>::SetState( T state )
{
	m_State = state;

	if( m_pSister == nullptr )
	{
		m_bUploadNeeded = true;

		return;
	}

	m_bUploadNeeded = !SameAsSister();
}

template<class T>
T TStateMonitor<T>::GetState() const
{
	return m_State;
}

template<class T>
bool TStateMonitor<T>::IsUpdateNeeded()
{
	return m_bUploadNeeded;
}

template<class T>
void TStateMonitor<T>::InitializeState()
{
	SetState( m_InitializeState );
}

template<class T>
void TStateMonitor<T>::ResetTracking()
{
	m_bUploadNeeded = false;
}