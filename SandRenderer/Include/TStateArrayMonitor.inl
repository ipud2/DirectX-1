template < class T , unsigned int N >
TStateArrayMonitor<T , N>::TStateArrayMonitor( T initialState ) :
m_uiStartSlot( 0 ) ,
m_uiEndSlot( 0 ) ,
m_bUpdateNeeded( false ) ,

m_InitialState( initialState ) ,
m_pSister( nullptr )
{
	InitializeStates();

	ResetTracking();
}

template < class T , unsigned int N >
TStateArrayMonitor<T , N>::~TStateArrayMonitor()
{

}

template < class T , unsigned int N >
void TStateArrayMonitor<T , N>::SetSister( TStateArrayMonitor<T , N>* pSister )
{
	m_pSister = pSister;
}

template < class T , unsigned int N >
void TStateArrayMonitor<T , N>::ResetTracking()
{
	m_uiStartSlot = m_uiEndSlot = 0;
	m_bUpdateNeeded = false;
}

template < class T , unsigned int N >
void TStateArrayMonitor<T , N>::SetState( unsigned int slot , T State )
{
	assert( slot < N );

	m_States[slot] = State;

	// ����ȷ��start slot �� end slot

	// sister state ������
	// ��Ĭ�����¼�����������
	if( m_pSister == nullptr )
	{
		m_bUpdateNeeded = true;
		m_uiStartSlot = 0;
		m_uiEndSlot = N - 1;

		return;
	}

	// ���ǵ���Ϊ����ȡ�����µ�״̬�Ƿ���sister stateƥ��
	bool bSameAsSister = SameAsSister( slot );

	if( ( !m_bUpdateNeeded ) && ( !bSameAsSister ) )
	{
		// ����Ҫ��������new state ��sister state ��һ��
		// ������sister state��һ�£������ǽ�m_bUpdateNeed����Ϊtrue
		m_bUpdateNeeded = true;

		// ֮ǰû�и��µģ����slot�ϵ�״̬���ı��ˣ���ֻ��Ҫ������һ��slot��״̬
		m_uiStartSlot = slot;
		m_uiEndSlot = slot;
	}


	if( m_bUpdateNeeded )
	{
		// ��Ҫ����

		if( slot < m_uiStartSlot )
		{
			if( !bSameAsSister )
			{
				// ��sister state�Ĳ�ͬ����Ҫ���������statrt slot����Ϊ��slot
				m_uiStartSlot = slot;
			}
		}
		else if( slot == m_uiStartSlot )
		{
			if( bSameAsSister )
			{
				// ��û���ø�slot��״̬Ϊnew state֮ǰ����������Ϊstart slot ~ end slot
				// ��������֮������slot��new state��sister state��Ӧslot��stateһ��
				// ��������䲻Ӧ���ٰ�����slot��Ҳ����start slot��
				// Ӧ����start slot ~ end slot������䣨������start slot�����ҵ���С��
				// ����sister state�ж�Ӧslot��state��ͬ�ĵ�һ��slot
				SearchFromBelow();
			}
		}
		else if( m_uiStartSlot < slot && slot < m_uiEndSlot )
		{
			// ���slot�����state������Ҫ����
		}
		else if( slot == m_uiEndSlot )
		{
			// ��û���ø�slot��new state֮ǰ����������Ϊstart slot ~ end slot
			// �����ڸ�slot��������new state���Ҹ�slot����end slot 
			// ����new state��sister state�ж�Ӧslot����end slot������ͬ
			// ��˵��end slot��Ӧ��state����Ҫ�ٸ�����
			// ��Ӧ���ҵ���end slot��start slot����
			// �ҵ���һ����sister state��Ӧslot״̬��ͬ��slot
			if( bSameAsSister )
			{
				SearchFromAbove();
			}
		}
		else if( m_uiEndSlot < slot )
		{
			if( !bSameAsSister )
			{
				// ��û���ø�slot��new state֮ǰ����������Ϊstart slot ~ end slot
				// �����ڸ�slot��������new state������sister state�϶�Ӧslot��state��ͬ
				// ��˸�slotҲ��Ҫ���£��Ҹ�slot > m_uiEndSlot �� ������չ��������
				// m_uiEndSlot = slot;
				m_uiEndSlot = slot;
			}
		}
	}
}

template < class T , unsigned int N >
bool TStateArrayMonitor<T , N>::SameAsSister( unsigned int slot )
{
	assert( slot < N );

	return ( m_States[slot] == m_pSister->GetState[slot] );
}

template < class T , unsigned int N >
void TStateArrayMonitor<T , N>::SearchFromBelow()
{
	// ��m_uiStartSlot ==�� m_uiEndSlot
	// �ҵ���һ����Sister State��ͬ��slot
	// m_uiStartSlot ~ m_uiEndSlot
	// ����Ҫ����״̬��slot
	// ��������������ÿ�ζ���������slot��state
	for( ; m_uiStartSlot < m_uiEndSlot; m_uiStartSlot++ )
	{
		if( !SameAsSister( m_uiStartSlot ) )
		{
			break;
		}
	}


	if( m_uiStartSlot == m_uiEndSlot && SameAsSister( m_uiStartSlot ) )
	{
		// ˵����sister slot��ȫ��ͬ������Ҫ����shader�е�״̬
		ResetTracking();
	}
}

template < class T , unsigned int N >
void TStateArrayMonitor<T , N>::SearchFromAbove()
{
	for( ; m_uiEndSlot > m_uiStartSlot; m_uiEndSlot-- )
	{
		if( !SameAsSister( m_uiEndSlot ) )
		{
			break;
		}
	}

	if( m_uiEndSlot == m_uiStartSlot && SameAsSister( m_uiEndSlot ) )
	{
		ResetTracking();
	}
}

template < class T , unsigned int N >
bool TStateArrayMonitor<T , N>::IsUpdateNeed()
{
	return m_bUpdateNeeded;
}

template < class T , unsigned int N >
unsigned int TStateArrayMonitor<T , N>::GetStartSlot()
{
	return  m_uiStartSlot;
}

template < class T , unsigned int N >
unsigned int TStateArrayMonitor<T , N>::GetEndSlot()
{
	return m_uiEndSlot;
}

template < class T , unsigned int N >
unsigned int TStateArrayMonitor<T , N>::GetRange()
{
	return ( m_uiEndSlot - m_uiStartSlot + 1 );
}

template < class T , unsigned int N >
void TStateArrayMonitor<T , N>::InitializeStates()
{
	for( int i = 0; i < N; i++ )
	{
		SetState( i , m_InitialState );
	}
}

template < class T , unsigned int N >
T TStateArrayMonitor<T , N>::GetState( unsigned int slot ) const
{
	assert( slot < N );

	return m_States[slot];
}

template < class T , unsigned int N >
T* TStateArrayMonitor<T , N>::GetFirstSlotLocation()
{
	return ( &m_States[m_uiStartSlot] );
}

template < class T , unsigned int N >
T* TStateArrayMonitor<T , N>::GetSlotLocation( unsigned int slot )
{
	assert( slot < N );

	return ( &m_States[slot] );
}