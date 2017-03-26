#pragma once

#include "STypeTraits.h"
#include "IsTriviallyCopyAssignable.h"
#include "AreTypesEqual.h"
#include "IsTriviallyDestructible.h"

namespace MemoryOps_Private
{
	template<typename DestinationElementType , typename SourceElementType>
	struct TCanBitwiseRelocate
	{
		// 1 : type are equal
		// 2 : can bit wise construct and has trivially destruct.
		enum
		{
			Value = TOr<
						TAreTypesEqual<DestinationElementType , SourceElementType> , 
						TAnd<	
							TIsBitwiseConstructible<DestinationElementType , SourceElementType> , 
							TIsTriviallyDestructible<SourceElementType>
							>
						>::Value
		};
	};
}
template<typename DestinationElementType , typename SourceElementType>
FORCEINLINE typename TEnableIf<!MemoryOps_Private::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value>::Type RelocateConstructItems( void* Dest , const SourceElementType* Source , int32 Count )
{
	while( Count )
	{
		new ( Dest ) DestinationElementType( *Source );
		++( DestinationElementType*& )Dest;
		( Source++ )->SourceElementType::~SourceElementType();
		--Count;
	}
}

template<typename DestinationElementType , typename SourceElementType>
FORCEINLINE typename TEnableIf<MemoryOps_Private::TCanBitwiseRelocate<DestinationElementType , SourceElementType>::Value>::Type RelocateConstructItems(void* Dest, const SourceElementType* Source, int32 Count)
{
	SMemory::Memmove(Dest, Source, sizeof(SourceElementType) * Count);
}

template<typename DestinationElementType , typename SourceElementType>
FORCEINLINE void ConstructItems( void* Dest , const SourceElementType* Source , int32 Count )
{
	while( Count )
	{
		new ( Dest ) DestinationElementType( *Source );
		++( DestinationElementType* &)Dest;
		++Source;
		--Count;
	}
}

template<typename ElementType>
void DestructItems( ElementType* Element , int32 Count )
{
	while( Count )
	{
		Element->ElementType::~ElementType();
		++Element;
		--Count;
	}
}

template<typename ElementType>
typename TEnableIf<!TIsZeroConstructType<ElementType>::Value>::Type DefaultConstructItems( void* Address , int32 Count )
{
	ElementType* Element = ( ElementType* )Address;

	while( Count )
	{
		new ( Element )ElementType;
		++Element;
		--Count;
	}
}

template<typename ElementType>
typename TEnableIf<TIsZeroConstructType<ElementType>::Value>::Type DefaultConstructItems( void* Address , int32 Count )
{
	std::memset( Address , 0 , sizeof( ElementType ) * Count );
}

template<typename ElementType>
typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value>::Type CopyAssignItems( ElementType* Dest , const ElementType* Soure , int32 Count )
{
	while( Count )
	{
		*Dest = *Source;
		++Dest;
		++Soure;
		--Count;
	}
}

template<typename ElementType>
typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value>::Type CopyAssignItems( ElementType* Dest , const ElementType* Soure , int32 Count )
{
	SMemory::Memcpy( Dest , Soure , sizeof( ElementType ) * Count );
}