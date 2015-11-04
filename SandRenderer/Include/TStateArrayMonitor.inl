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

	// 重新确定start slot 和 end slot

	// sister state 不存在
	// 则默认重新加载整个数组
	if( m_pSister == nullptr )
	{
		m_bUpdateNeeded = true;
		m_uiStartSlot = 0;
		m_uiEndSlot = N - 1;

		return;
	}

	// 我们的行为将会取决于新的状态是否与sister state匹配
	bool bSameAsSister = SameAsSister( slot );

	if( ( !m_bUpdateNeeded ) && ( !bSameAsSister ) )
	{
		// 不需要更新且与new state 与sister state 不一致
		// 由于与sister state不一致，则我们将m_bUpdateNeed设置为true
		m_bUpdateNeeded = true;

		// 之前没有更新的，这次slot上的状态被改变了，则只需要更新这一个slot的状态
		m_uiStartSlot = slot;
		m_uiEndSlot = slot;
	}


	if( m_bUpdateNeeded )
	{
		// 需要更新

		if( slot < m_uiStartSlot )
		{
			if( !bSameAsSister )
			{
				// 与sister state的不同，则要更新区间的statrt slot更改为该slot
				m_uiStartSlot = slot;
			}
		}
		else if( slot == m_uiStartSlot )
		{
			if( bSameAsSister )
			{
				// 在没设置该slot的状态为new state之前，更新区间为start slot ~ end slot
				// 现在设置之后，若该slot的new state与sister state对应slot的state一样
				// 则更新区间不应该再包括该slot（也就是start slot）
				// 应该在start slot ~ end slot这段区间（不包括start slot）中找到最小的
				// 且与sister state中对应slot的state不同的第一个slot
				SearchFromBelow();
			}
		}
		else if( m_uiStartSlot < slot && slot < m_uiEndSlot )
		{
			// 这段slot区间的state本来就要更新
		}
		else if( slot == m_uiEndSlot )
		{
			// 在没设置该slot的new state之前，更新区间为start slot ~ end slot
			// 现在在该slot上设置了new state，且该slot等于end slot 
			// 而且new state与sister state中对应slot（即end slot）的相同
			// 则说明end slot对应的state不需要再更新了
			// 则应该找到从end slot往start slot查找
			// 找到第一个与sister state对应slot状态不同的slot
			if( bSameAsSister )
			{
				SearchFromAbove();
			}
		}
		else if( m_uiEndSlot < slot )
		{
			if( !bSameAsSister )
			{
				// 在没设置该slot的new state之前，更新区间为start slot ~ end slot
				// 现在在该slot上设置了new state而且与sister state上对应slot的state不同
				// 因此该slot也需要更新，且该slot > m_uiEndSlot ， 所以扩展更新区间
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
	// 从m_uiStartSlot ==》 m_uiEndSlot
	// 找到第一个和Sister State不同的slot
	// m_uiStartSlot ~ m_uiEndSlot
	// 是需要更新状态的slot
	// 这样避免了我们每次都更新所有slot的state
	for( ; m_uiStartSlot < m_uiEndSlot; m_uiStartSlot++ )
	{
		if( !SameAsSister( m_uiStartSlot ) )
		{
			break;
		}
	}


	if( m_uiStartSlot == m_uiEndSlot && SameAsSister( m_uiStartSlot ) )
	{
		// 说明与sister slot完全相同，则不需要更新shader中的状态
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