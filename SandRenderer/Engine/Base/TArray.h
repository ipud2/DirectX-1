#ifndef TARRAY_H
#define TARRAY_H

#include "PCH.h"
#include "Sorting.h"
#include "TEnableIf.h"

namespace Array_Private
{
	template<typename FromArrayType , typename ToArrayType>
	struct TCanMoveTArrayPointerBetweenArrayTypes
	{
		typedef typename FromArrayType::ElementType FromElementType;
		typedef typename ToArrayType::ElementType ToElementType;
		enum
		{
			Value = TAreTypesEqual<FromElementType , ToElementType>::Value || TIsBitwiseConstructible<FromElementType , ToElementType>::Value
		};
	};
}

template<class T>
class TArray
{
public:
	typedef T ElementType;
public:
	// default constructor. constructs an empty container.
	TArray();

	// Initializer list constructor.
	TArray( std::initializer_list<T> InitList );

	template<typename OtherType>
	explicit TArray( const TArray<OtherType>& Other );

	TArray( const TArray& Other );

	TArray( const TArray& Other , int32 ExtraSlack );

	TArray& operator = ( std::initializer_list<T> InitList );

	// copy assignment operator. Replaces the contents with a copy of the contents of other.
	TArray& operator=( const TArray& other );

	~TArray();

private:
	template<typename FromArrayType , typename ToArrayType>
	static FORCEINLINE typename TEnableIf<Array_Private::TCanMoveTArrayPointerBetweenArrayTypes<FromArrayType, ToArrayType>::Value>::Type MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray, int32 PreMax)
	{
		SAFE_FREE(ToArray.m_pData);
		ToArray.m_pData = FromArray.GetData();

		ToArray.m_iCapacity		= FromArray.m_iCapacity;
		ToArray.m_iSize			= FromArray.m_iSize;
		FromArray.m_iCapacity	= 0;
		FromArray.m_iSize		= 0;
	}

	template<typename FromArrayType , typename ToArrayType>
	static FORCEINLINE typename TEnableIf<!Array_Private::TCanMoveTArrayPointerBetweenArrayTypes<FromArrayType, ToArrayType>::Value>::Type MoveOrCopy(ToArrayType& ToArray, FromArrayType& FromArray, int32 PreMax)
	{
		ToArray.CopyToEmpty(FromArray.GetData(), FromArray.Num(), PreMax, 0);
	}
public:
	TArray(TArray&& Other)
	{
		MoveOrCopy(*this, Other, 0);
	}

	template<typename OtherElementType>
	FORCEINLINE explicit TArray(TArray<OtherElementType>&& Other)
	{
		MoveOrCopy(*this, Other, 0);
	}

	// Helper function returning the size of the inner type.
	// @returns Size in bytes of array type.
	uint32 GetTypeSize() const;

	// Helper function returning the amount of memory allocated by this container.
	// @returns Num of bytes allocated by this container.
	uint32 GetAllocatedSize() const;

	// Helper function returning the number of slack in the array in elements.
	int32 GetSlack() const;

	// Replaces the contents with count copies of value value.
	//bool Assign( uint32 count , const T& value );

	// returns a reference to the element at specified location pos, with bounds checking.
	// if pos is not within the range of the container, should thrown except.
	T& At( uint32 pos );
	const T& At( uint32 pos ) const;

	// returns a reference to the element at specified location pos.
	// No bounds checking is performed.
	T& operator[]( uint32 pos );
	const T& operator[]( uint32 pos ) const;

	// Returns a reference to the first element in the container.
	// Calling Front on an empty container is undefined.
	T& Front();
	const T& Front() const;

	// Returns reference to the last element in the container.
	// Calling back on an empty container is undefined.
	T& Back();
	const T& Back() const;

	// Returns pointer to the underlying array serving as element storage.
	// The pointer is such that range[data(); data() + size()) is always a valid range.
	// even if the container is empty (data() is not dereferenceable in the case)
	T* GetData();
	const T* GetData() const;

	// Checks if the container has no elements.
	bool IsEmpty() const
	{
		return m_iSize == 0;
	}

	// Returns the number of elements in the container.
	uint32 Size() const;

	// increase the capacity of the container to a value that's greater or equal to new_cap.
	// if new_cap is greater than the current capacity(), new storage is allocated,
	// otherwise the method does nothing.
	void Reserve( uint32 new_cap );

	// Returns the number of elements that the container has currently allocated space for.
	uint32 Capacity() const;

	/*
		return number of elements in array.
	*/
	FORCEINLINE int32 GetSize() const
	{
		return m_iSize;
	}

	// Requests the removal of unused capacity.
	void Shrink();

	// Removes all element from the container.
	// invalidates any references, pointers referring to contained elements.
	// leaves the capacity() of the TArray unchanged.
	void Clear();

	// insert value before pos
	void Insert( uint32 pos , const T& value );

	// Insert a given number of uninitialized elements into the array at given
	// location.
	// 
	// Caution, InsertUninitalized() will create elements without calling the constructor
	// and this is not appropriate for element types that require a constructor to function
	// properly
	// @param Index Tells where to insert the new elements.
	// @param Count Number of elements to add.
	void InsertUninitialized( int32 index , int32 count = 1 );

	// Inserts a given number of zeroed elements into the array at given
	// location
	// 
	// Caution, InsertZeroed() will create elements without calling the constructor
	// and this is not approriate for element types that require a constructor to function
	// properly.
	// 
	// @param Index Tells where to insert the new elements.
	// @param Count Number of elements to insert.
	void InsertZeroed( int32 Index , int32 Count = 1 );

	// Inserts given elements into the array at given location.
	// 
	// @param Items Array of elements to insert.
	// @param Index Tells where to insert the new elements.
	void Insert( const TArray<T>& Items , const int32 Index );

	// Inserts a raw array of elements at a particular index in the TArray.
	// 
	// @param Ptr A Pointer to an array of elements to add.
	// @param Count The number of elements to insert from Ptr.
	// @param the index of the first element to inserted.
	void Insert( const T* Ptr , int32 Count , int32 Index );

	// 1) Removes specified elements from the container.
	// 2) Removes the elements in the range[first , last)
	// invalidates references at or after the point of the erase.
	// void Erase( uint32 pos );
	// void Erase( uint32 first , uint32 last );

	// Removes an element at given location optionally shrinking
	// the array
	//
	// @param Index location in array of the element to remove.
	void Remove( int32 Index );

	// Removes at element (or elements) at given location optionally shrinking
	// the array.
	// 
	// @param Index Location in array of the element to remove.
	// @param Count (Optional) Number of element to remove. Default is 1.
	// @param bAllowShrinkging (Optional) Tells if this call can shrink arary if suitable after remove.
	//							Default is true.
	template<typename CountType>
	void Remove( int32 Index , CountType Count = 1 , bool bAllowShrinking = true );

	// Removes as many instances of item as there are in the array.
	// maintaining order but not indices
	//
	// @param Item Item to remove from array.
	// @returns Number of removed elements
	int32 Remove( const T& Item );

	// Remove all instances that match the predicate, maintaining order but not indices
	// Optimized to work with run of matches/non-matches.
	//
	// @params Predicate Predicate class instance
	// @returns Number of removed Elements
	template<class PREDICATE_CLASS>
	int32 RemoveAll( const PREDICATE_CLASS& Predicate );

	// Removes the first occurrence of the specified item in the array.
	// maintaining order but not indices.
	//
	// @param Item the item to remove.
	// @return The number of items removed. For RemoveSingleItem , this is always either 0 or 1
	int32 RemoveSingle( const T& Item );

	// Finds element within the array.
	// 
	// @param Item Item to look for.
	// @returns Index of the found element. INDEX_NONE otherwise.
	int32 Find( const T& Item ) const;
	
	// Finds Element within the array.
	// 
	// @param Item Item to look for.
	// @Index will contain the found index.
	bool Find( const T& Item , int32& Index ) const;

	// Finds an item by key(assuming the T overloads operator == for the comparison).
	template<typename KeyType>
	inline const T* FindByKey( const KeyType& Key ) const;

	// Finds an item by key (assuming the T overloads operator == for the comparison).
	template<typename KeyType>
	T* FindByKey( const KeyType& Key );

	template<typename Predicate>
	T* FindByPredicate( Predicate Pred );

	template<typename Predicate>
	TArray<T> FilterByPredicate( Predicate Pred ) const;

	template<typename ComparisonType>
	bool Contains( const ComparisonType& Item ) const;

	template<typename KeyType>
	int32 IndexOfByKey( const KeyType& Key ) const;

	template<typename Predicate>
	int32 IndexOfByPredicate( Predicate Pred ) const;

	// Constructs a new item at the end of the array. possibly reallocating the whole array
	// to fit.
	// 
	// @param Args	The arguments to forward to the constructor of the new item.
	// @return		index to the new item.
	template<typename... ArgsType>
	int32 Emplace( ArgsType&&... Args );

	// Adds a given number of uninitialized elements into the array.
	// 
	// Caution, AddUninitialized() will create elements without calling
	// the constructor and this is not appropriate for element types that
	// require a constructor to function properly.
	// 
	// @param Count	Number of elements to add
	// @returns Number of elements in array before addition.
	int32 AddUninitialized( int32 Count = 1 );

	// Adds a new item to the end of array.
	// possibly reallocating the whole array to fit.
	//
	// @param Item The Item to add.
	// @return Index to the new Item.
	int32 Add( T&& Item );

	// Adds new items to the end of array.
	// possibly reallocating the whole array to fit.
	//
	// @param Item The Item to add.
	// @return Index to the new item.
	int32 Add( const T& Item );

	// Adds a new item to the end of the array. possibly reallocating the whole
	// array to fit. the new item will be zeroed.
	// 
	// Caution, AddZeroed() will create elements without calling the 
	// constructor and this is not appropriate for element types that require
	// a constructor to function properly.
	// 
	// @param Item Item to add.
	// @return Index to the new Item.
	int32 AddZeroed( int32 Count = 1 );

	// Adds unique element to array if it doesn't exist.
	//
	// Move semantices verison
	// @param Args Item to Add.
	// @return Index of the element in the array.
	int32 AddUnique( T&& Item );

	// Adds unique elements to array if it doesn't exist.
	// @param Args Item to Add.
	// @return Index of the element in the array.
	int32 AddUnique( const T& Item );

	// Adds unique element to array if it doesn't exist.
	//
	// @param Args Item to add.
	// @return Index of the element in the array.
	template<typename ArgsType>
	inline int32 AddUniqueImpl( ArgsType&& Args );

	// Push elements into the array.
	//
	// @param Item Item to push
	void Push( T& Item );

	// Pushes element into the array.
	//
	// Const ref version of the above.
	// @param Item Item to push.
	void Push( const T& Item );

	// Pop element from the array.
	//
	// @param bAllowShrinking If this call allows shrinking of the array during element remove.
	// @returns Popped element.
	T Pop( bool bAllowShrinking = true );

	// Empties the array. It Calls the destructors on held items if needed.
	//
	// @param Slack (Optinal) The expected usage after empty operation. Default is 0.
	void Empty( int32 Slack = 0 );

	// Resize array to given number of elements.
	// 
	// @param NewNum New Size of the array.
	// @param bAllowShrinking Tell if this function can shrinking the memory in-use if suitable.
	void Resize( int32 NewNum , bool bAllowShrinking = true );

	// Resize array to given number of elements. New elements will be zeroed.
	//
	// @param NewNum New Size of the array.
	void ResizeZeroed( int32 NewNum , bool bAllowShrinking = true );

	// Resize array to given number of elements. New elements will be uninitialized.
	// 
	// @param NewNum New Size of the array.
	void ResizeUninitialized( int32 NewNum , bool bAllowShrinking = true );

	bool CheckAddress( const T* Addr ) const;

	// Sorts the array assuming < operator is defined for the item type
	void Sort();

	template<class PREDICATE_CLASS>
	void Sort( const PREDICATE_CLASS& Predicate );

private:
	void ResizeTo( int32 NewMax );

	void RemoveAtImpl( int32 Index , int32 Count , bool bAllowShrinking );

	void ResizeShrink();

	void ResizeGrow( int32 OldNum );

	void ResizeForCopy( int32 NewMaxs , int32 PrevMax );

	// Copies data from one array into this array. Uses the fast path if the
	// data in question does not need a constructor.
	//
	// @param OtherData The source array to copy.
	// @param PrevMax	The previous allocated size.
	// @param ExtraSlack Additional amount of memory to allocate at the end of the buffer.
	//					 Counted in elements. Zero by default.
	template<typename OtherType>
	void CopyToEmpty( const OtherType* OtherData , int32 OtherNum , int32 PrevMax , int32 ExtraSlack );

private:
	T* m_pData			= nullptr;
	int32 m_iSize		= 0;
	int32 m_iCapacity	= 0;
};

#include "MemoryOps.h"
#include "TArray.inl"
#endif