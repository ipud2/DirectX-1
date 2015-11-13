template<class T>
TGrowableBuffer<T>::TGrowableBuffer()
	:m_uiMaxElementCount( 0 ) ,
	m_uiElementCount( 0 ) ,
	m_bUploadNeeded( false ) ,
	m_pDataArray( nullptr )
{

}

template<class T>
TGrowableBuffer<T>::~TGrowableBuffer()
{
	SAFE_DELETE_ARRAY( m_pDataArray );
}

template<class T>
void TGrowableBuffer<T>::SetMaxElementCount( unsigned int max )
{
	if( max != m_uiMaxElementCount )
	{
		T* pNewArray = new T[max];

		int CopyElementCount = m_uiElementCount

		if( m_uiElementCount > max )
		{
			CopyElementCount = max;
		}

		if( CopyElementCount > 0 )
		{
			memcpy( pNewArray , m_pDataArray , CopyElementCount * sizeof( T ) );
		}

		m_uiMaxElementCount = max;
		
		SAFE_DELETE_ARRAY( m_pDataArray );
		m_pDataArray = pNewArray;

		// 删除原资源
		DeleteResource();

		// 创建新资源
		CreateResource( m_uiMaxElementCount );

		m_bUploadNeeded = true;
	}
}

template<class T>
unsigned int TGrowableBuffer<T>::GetMaxElementCount()
{
	return m_uiMaxElementCount;
}

template<class T>
unsigned int TGrowableBuffer<T>::GetCurrentELementCount()
{
	return m_uiElementCount;
}

template<class T>
void TGrowableBuffer<T>::AddElement( const T& element )
{
	EnsureCapacity();

	m_pDataArray[m_uiElementCount] = element;
	m_uiElementCount++;

	m_bUploadNeeded = true;
}


template<class T>
void TGrowableBuffer<T>::ResetData()
{
	m_uiElementCount = 0;

	m_bUploadNeeded = false;
}

template<class T>
void TGrowableBuffer<T>::EnsureCapacity()
{
	if( m_uiElementCount + 1 > m_uiMaxElementCount )
	{
		SetMaxElementCount(m_uiMaxElementCount + 1024)；
	}
}