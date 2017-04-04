#include "TArray.h"
#include "AllocationPolicies.h"

template<typename T>
TArray<T>::TArray()
{
	m_iSize = 0;
	m_iCapacity = 0;
	m_pData = nullptr;
}

template<class T>
inline TArray<T>::TArray( std::initializer_list<T> InitList )
{
	CopyToEmpty( InitList.begin() , ( int32 )InitList.size() , 0 , 0 );
}

template<class T>
template<class OtherType>
inline TArray<T>::TArray( const TArray<OtherType>& Other )
{
	CopyToEmpty( Other.GetData() , Other.Size() , 0 , 0 );
}

template<class T>
inline TArray<T>::TArray( const TArray& Other )
{
	CopyToEmpty( Other.GetData() , Other.Size() , 0 , 0 );
}

template<class T>
inline TArray<T>::TArray( const TArray& Other , int32 ExtraSlack )
{
	CopyToEmpty( Other.GetData() , Other.Size() , 0 , ExtraSlack );
}

template<class T>
inline TArray<T>& TArray<T>::operator=( std::initializer_list<T> InitList )
{
	DestructItems( GetData() , m_iSize );

	CopyToEmpty( InitList.begin() , ( int32 )InitList.size() , m_iCapacity , 0 );

	return *this;
}

template<class T>
inline TArray<T>& TArray<T>::operator=( const TArray<T>& Other )
{
	if( this != &Other )
	{
		DestructItems( GetData() , m_iSize );

		CopyToEmpty( Other.GetData() , Other.Size() , m_iCapacity , 0 );
	}

	return *this;
}

template<typename T>
TArray<T>::~TArray()
{
	DestructItems( GetData() , m_iSize );
	m_pData = nullptr;
}

template<typename T>
T& TArray<T>::At( uint32 pos )
{
	assert( pos >= 0 && pos < m_iSize );
	return m_pData[pos];
}

template<typename T>
const T& TArray<T>::At( uint32 pos ) const
{
	assert( pos >= 0 && pos < m_iSize );
	return m_pData[pos];
}

template<typename T>
T& TArray<T>::operator[]( uint32 pos )
{
	return m_pData[pos];
}

template<typename T>
const T& TArray<T>::operator[]( uint32 pos ) const
{
	return m_pData[pos];
}

template<typename T>
T& TArray<T>::Front()
{
	return m_pData[0];
}

template<typename T>
const T& TArray<T>::Front() const
{
	return m_pData[0];
}

template<typename T>
T& TArray<T>::Back()
{
	return m_pData[m_iSize - 1];
}

template<typename T>
const T& TArray<T>::Back() const
{
	return m_pData[m_iSize - 1];
}

template<typename T>
T* TArray<T>::GetData()
{
	return m_pData;
}

template<typename T>
const T* TArray<T>::GetData() const
{
	return m_pData;
}

template<typename T>
uint32 TArray<T>::Size() const
{
	return m_iSize;
}

template<typename T>
void TArray<T>::Reserve( uint32 NewCapacity )
{
	if (NewCapacity > (uint32)m_iCapacity)
	{
		ResizeTo( NewCapacity );
	}
}

template<typename T>
uint32 TArray<T>::Capacity() const
{
	return m_iCapacity;
}

template<typename T>
void TArray<T>::Shrink()
{
	if( m_iCapacity != m_iSize )
	{
		ResizeTo( m_iSize );
	}
}

template<typename T>
void TArray<T>::Clear()
{
	m_iSize = 0;
}

template<typename T>
void TArray<T>::InsertUninitialized( int32 index , int32 Count /* = 1 */ )
{
	assert(Count >= 0 && ( index >= 0 ) && index <= m_iSize );

	const int32 oldSize= m_iSize;
	if( ( m_iSize += Count) > m_iCapacity )
	{
		ResizeGrow( oldSize );
	}

	T* pData = GetData() + index;
	RelocateConstructItems<T>(pData + Count, pData, oldSize - index);
}

template<typename T>
void TArray<T>::InsertZeroed( int32 Index , int32 Count /* = 1 */ )
{
	InsertUninitialized( Index , Count );

	for (int i = 0; i < Count; i++)
	{
		*(m_pData + Index) = T();
	}
	//memset( m_pData + Index , 0 , Count * sizeof( T ) );
}

template<typename T>
void TArray<T>::Insert( const TArray<T>& Items , const int32 Index )
{
	assert( this != Items );

	InsertUninitialized( Index , Items.Size() );

	T* pData = Items.GetData();
	for( int32 iStartIndex = 0; iStartIndex < Items.Size(); iStartIndex++ )
	{
		new ( m_pData + iStartIndex + Index ) Items[iStartIndex];
	}
}

template<typename T>
void TArray<T>::Insert( const T* Ptr , int32 Count , int32 Index )
{
	assert( Ptr != nullptr );

	InsertUninitialized( Index , Count );

	ConstructItems<T>( GetData() + Index , Ptr , Count );
}

template<typename T>
void TArray<T>::Insert( uint32 pos , const T& value )
{
	if( !CheckAddress( &value ) )
	{
		return;
	}

	InsertUninitialized( pos , 1 );
	new ( GetData() + pos )	T( value );
}

template<typename T>
void TArray<T>::RemoveAtImpl( int32 Index , int32 Count , bool bAllowShrinking )
{
	if( Count )
	{
		assert( Index >= 0 && Index + Count <= m_iSize );

		DestructItems( GetData() + Index , Count );

		int iNumToMove = m_iSize - Index - Count;
		if( iNumToMove )
		{
			std::memmove( GetData() + Index , GetData() + Index + Count , sizeof( T ) * iNumToMove );
		}

		m_iSize -= Count;

		if( bAllowShrinking )
		{
			ResizeShrink();
		}
	}
}

template<typename T>
template<typename CountType>
void TArray<T>::Remove( int32 Index , CountType Count , bool bAllowShrinking = true )
{
	RemoveAtImpl( Index , Count , bAllowShrinking );
}

template<typename T>
void TArray<T>::Remove( int32 Index )
{
	RemoveAtImpl( Index , 1 , true );
}

template<typename T>
int32 TArray<T>::Remove( const T& Item )
{
	assert( &Item < GetData() || &Item >= ( GetData() + m_iCapacity ) );

	return RemoveAll( [&Item]( T& Element )
	{
		return Element == Item;
	} )
}

template<class T>
template<class PREDICATE_CLASS>
inline int32 TArray<T>::RemoveAll( const PREDICATE_CLASS & Predicate )
{
	const int32 OriginalNum = m_iSize;
	if( !OriginalNum )
	{
		return 0;
	}

	int32 WriteIndex = 0;
	int32 ReadIndex = 0;
	bool NotMatch = !Predicate( GetData()[ReadIndex] );
	do 
	{
		int32 RunStartIndex = ReadIndex++;
		while( ReadIndex < OriginalNum && NotMatch == !Predicate( GetData()[ReadIndex] ) )
		{
			ReadIndex++;
		}

		int RunLength = ReadIndex - RunStartIndex;
		if( NotMatch )
		{
			// this was a non-matching run,we need to remove it
			if( WriteIndex != RunStartIndex )
			{
				std::memmove( &GetData()[WriteIndex] , &GetData()[RunStartIndex] , sizeof( T ) * RunLength );
			}

			WriteIndex += RunLength;
		}
		else
		{
			// this was a matching run, delete it
			DestructItems( &GetData()[RunStartIndex] , RunLength );
		}

		// alternate search.
		NotMatch = !NotMatch;
	} while( ReadIndex < OriginalNum );

	m_iSize = WriteIndex;

	return OriginalNum - m_iSize;
}

template<class T>
inline int32 TArray<T>::RemoveSingle( const T & Item )
{
	int32 Index = Find( Item );
	if( Index != INDEX_NONE )
	{
		return 0;
	}

	auto* pRemovePtr = GetData() + Index;

	DestructItems( pRemovePtr , 1 );

	const int32 NextIndex = Index + 1;
	RelocateConstructItems<T>( pRemovePtr , pRemovePtr + 1 , m_iSize - ( Index + 1 ) );

	--m_iSize;

	return 1;
}

template<typename T>
inline int32 TArray<T>::Find( const T& Item ) const
{
	const T* Start = GetData();
	for( const T* pData = Start , *pEnd = pData + m_iSize; pData != pEnd; pData++ )
	{
		if( *pData == Item )
		{
			return static_cast< int32 >( pData - Start );
		}
	}

	return INDEX_NONE;
}

template<typename T>
inline bool TArray<T>::Find( const T& Item , int32& Index ) const
{
	Index = this->Find( Item );
	return Index != INDEX_NONE;
}

template<typename T>
uint32 TArray<T>::GetTypeSize() const
{
	return sizeof( T );
}

template<typename T>
inline uint32 TArray<T>::GetAllocatedSize() const
{
	return m_iCapacity * sizeof( T );
}

template<typename T>
inline int32 TArray<T>::GetSlack() const
{
	return m_iCapacity - m_iSize;
}

template<class T>
template<typename KeyType>
inline const T * TArray<T>::FindByKey( const KeyType & Key ) const
{
	return const_cast< TArray* >( this )->FindByKey( Key );
}

template<class T>
template<typename KeyType>
inline T * TArray<T>::FindByKey( const KeyType & Key )
{
	for( T* RESTRICT pData = GetData() , *RESTRICT pDataEnd = pData + m_iSize; pData != pDataEnd; ++pData )
	{
		if( *pData == Key )
		{
			return pData;
		}
	}

	return nullptr;
}

template<class T>
template<typename Predicate>
inline T * TArray<T>::FindByPredicate( Predicate Pred )
{
	for( T* RESTRICT pData = GetData() , *RESTRICT pDataEnd = pData + m_iSize; pData != pDataEnd; ++pData )
	{
		if( Pred( *pData ) )
		{
			return pData;
		}
	}

	return nullptr;
}

template<class T>
template<typename Predicate>
inline TArray<T> TArray<T>::FilterByPredicate( Predicate Pred ) const
{
	TArray<T> FilterResult;

	for( const T* RESTRICT pData = GetData() , *RESTRICT pDataEnd = pData + m_iSize; pData != pDataEnd; ++pData )
	{
		if( Pred( *pData ) )
		{
			FilterResult.Add( *pData );
		}
	}
	return FilterResult;
}

template<class T>
template<typename ComparisonType>
inline bool TArray<T>::Contains( const ComparisonType & Item ) const
{
	for( const T* RESTRICT pData = GetData(), *RESTRICT pDataEnd = pData + m_iSize; pData != pDataEnd; ++pData )
	{
		if( *pData == Item )
		{
			return true;
		}
	}

	return false;
}

template<class T>
template<typename KeyType>
inline int32 TArray<T>::IndexOfByKey( const KeyType & Key ) const
{
	const T* RESTRICT Start = GetData();

	for( const T* RESTRICT pData = Start , *RESTRICT pDataEnd = Start + m_iSize; pData != pDataEnd; ++pData )
	{
		if( *pData == Key )
		{
			return static_const<int32>( pData - Start );
		}
	}

	return INDEX_NONE;
}

template<class T>
template<typename Predicate>
inline int32 TArray<T>::IndexOfByPredicate( Predicate Pred ) const
{
	const T* RESTRICT pData = GetData();

	for( const T* RESTRICT pData = Start , *RESTRICT pDataEnd = Start + m_iSize; pData != pDataEnd; ++pData )
	{
		if( Pred( *pData ) )
		{
			return static_cast< int32 >( pData - Start );
		}
	}

	return INDEX_NONE;
}

template<class T>
template<typename ...ArgsType>
inline int32 TArray<T>::Emplace( ArgsType && ...Args )
{
	const int32 Index = AddUninitialized( 1 );
	new( GetData() + Index )T( Forward<ArgsType>( Args )... );
	return Index;
}

template<typename T>
int32 TArray<T>::AddUninitialized( int32 Count = -1 )
{
	assert( m_iSize >= 0 && m_iCapacity >= m_iSize && Count >= 0 );

	const int32 OldNum = m_iSize;
	if( ( m_iSize += Count ) > m_iCapacity )
	{
		ResizeGrow( OldNum );
	}

	return OldNum;
}

template<class T>
inline int32 TArray<T>::Add( T && Item )
{
	assert( &Item < GetData() || &Item >= ( GetData() + m_iCapacity ) );

	return Emplace( MoveTemp( Item ) );
}

template<class T>
inline int32 TArray<T>::Add( const T & Item )
{
	return Emplace( Item );
}

template<class T>
inline int32 TArray<T>::AddZeroed( int32 Count )
{
	const int32 Index = AddUninitialized( Count );
	std::memset( ( uint8* )GetData() + Index * sizeof( T ) , 0 , sizeof( T ) * Count );
	return Index;
}

template<class T>
inline int32 TArray<T>::AddUnique( const T & Item )
{
	// ArgsType will be instantiated as const T&
	return AddUniqueImpl( Item );
}

template<class T>
inline int32 TArray<T>::AddUnique( T && Item )
{
	return AddUniqueImpl( MoveTemp( Item ) );
}

template<class T>
template<typename ArgsType>
inline int32 TArray<T>::AddUniqueImpl( ArgsType && Args )
{
	int32 Index;
	if( Find( Args , Index ) )
	{
		return Index;
	}

	return Add(Forward<ArgsType>(Args))£»
}

template<typename T>
void TArray<T>::Push( T& Item )
{
	Add( MoveTemp( Item ) );
}

template<typename T>
void TArray<T>::Push( const T& Item )
{
	Add( Item );
}

template<class T>
inline T TArray<T>::Pop( bool bAllowShrinking )
{
	T Result = MoveTemp( GetData()[m_iSize - 1] );
	Remove( m_iSize - 1 , 1 , bAllowShrinking );
	return Result;
}

template<class T>
inline void TArray<T>::Empty( int32 Slack )
{
	DestructItems( GetData() , m_iSize);

	m_iSize = 0;

	if( m_iCapacity != Slack )
	{
		ResizeTo( Slack );
	}
}


template<class T>
inline void TArray<T>::Resize( int32 NewNum , bool bAllowShrinking )
{
	if( NewNum > m_iSize )
	{
		const int32 Diff = NewNum - m_iSize;
		const int32 Index = AddUninitialized( Diff );

		DefaultConstructItems<T>( &GetData()[Index] , Diff );
	}
	else if( NewNum < m_iSize )
	{
		Remove( NewNum , m_iSize - NewNum , bAllowShrinking );
	}
}

template<class T>
inline void TArray<T>::ResizeZeroed( int32 NewNum , bool bAllowShrinking )
{
	if( NewNum > m_iSize )
	{
		AddZeroed( NewNum - m_iSize );
	}
	else if( NewNum < m_iSize )
	{
		Remove( NewNum , m_iSize - NewNum , bAllowShrinking );
	}
}

template<class T>
inline void TArray<T>::ResizeUninitialized( int32 NewNum , bool bAllowShrinking /* = true */ )
{
	if( NewNum > m_iSize )
	{
		AddUninitialized( NewNum - m_iSize );
	}
	else if( NewNum < m_iSize )
	{
		Remove( NewNum , m_iSize - NewNum , bAllowShrinking );
	}
}

template<typename T>
void TArray<T>::ResizeGrow( int32 OldNum )
{
	// calc new array capacity.
	int iGrow = SIZE_T( m_iSize ) + 3 * SIZE_T( m_iSize ) / 8 + 16;
	if( m_iSize > iGrow )		// m_iSize and m_iCapacity are stored in 32-bit signed integers so we must be careful not to overflow here.
	{
		iGrow = Max_int32;
	}

	m_iCapacity = iGrow;

	// realloc
	if( m_iCapacity > 0 )
	{
		void* newRealloc = ::realloc( m_pData , m_iCapacity * sizeof( T ) );
		m_pData = ( T* )newRealloc;
	}
	else
	{
		::free( m_pData );
		m_pData = nullptr;
	}
}

template<typename T>
void TArray<T>::ResizeTo( int32 NewCapacity )
{
	if( NewCapacity != m_iCapacity )
	{
		m_iCapacity = NewCapacity;
		if( m_iCapacity )
		{
			void* pNewAlloc = ::realloc( m_pData , m_iCapacity * sizeof( T ) );
			m_pData = ( T* )pNewAlloc;
		}
		else
		{
			::free( m_pData );
			m_pData = nullptr;
		}
	}
}

template<typename T>
bool TArray<T>::CheckAddress( const T* Addr ) const
{
	if( Addr < GetData() || Addr > GetData() + m_iCapacity )
	{
		return false;
	}

	return true;
}

template<class T>
inline void TArray<T>::Sort()
{
	::Sort( GetData() , m_iSize );
}

template<typename T>
void TArray<T>::ResizeShrink()
{
	const int32 NewCapacity = DefaultCalculateSlackShrink( m_iSize , m_iCapacity , sizeof( T ) );
	if( NewCapacity != m_iCapacity )
	{
		m_iCapacity = NewCapacity;
		assert( m_iCapacity >= m_iSize );

		if( m_iCapacity )
		{
			void* NewRealloc = ::realloc( m_pData , m_iCapacity * sizeof( T ) );
			m_pData = ( T* )NewRealloc;
		}
		else
		{
			::free( m_pData );
			m_pData = nullptr;
		}
	}
}

template<class T>
template<class PREDICATE_CLASS>
inline void TArray<T>::Sort( const PREDICATE_CLASS & Predicate )
{
	::Sort( GetData() , m_iSize , Predicate );
}

template<typename T>
template<typename OtherType>
void TArray<T>::CopyToEmpty( const OtherType* OtherData , int32 OtherNum , int32 PrevMax , int32 ExtraSlack )
{
	assert( ExtraSlack >= 0 );
	m_iSize = OtherNum;

	if( OtherNum || ExtraSlack || PrevMax )
	{
		ResizeForCopy( OtherNum + ExtraSlack , PrevMax );
		ConstructItems<T>( GetData() , OtherData , OtherNum );
	}
}

template<typename T>
void TArray<T>::ResizeForCopy( int32 NewMax , int32 PrevMax )
{
	if( NewMax )
	{
		NewMax = DefaultCalculateSlackReserve( NewMax , sizeof( T ) );
	}

	if( NewMax != PrevMax )
	{
		if(NewMax)
		{
			void* pNewAlloc = ::realloc( m_pData , NewMax * sizeof( T ) );
			m_pData = ( T* )pNewAlloc;
		}
		else
		{
			::free( m_pData );
			m_pData = nullptr;
		}
	}

	m_iCapacity = NewMax;
}