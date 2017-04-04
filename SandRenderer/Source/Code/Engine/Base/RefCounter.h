#ifndef REF_COUNTER_H
#define REF_COUNTER_H

#include <Engine/PCH.h>

class IRefCountedObject
{
public:
	virtual uint32 AddRef()	const = 0;
	virtual uint32 Release() const = 0;
	virtual uint32 GetRefCount() const = 0;
};

class RefCountedObject
{
public:
	RefCountedObject()
	{
		NumRefs = 0;
	}

	virtual ~RefCountedObject() {}

	uint32 AddRef() const {}
	{
		return uint32( ++NumRefs );
	}

	uint32 Release() const
	{
		uint32 Refs = uint32( --NumRefs );
		if ( Refs == 0 )
		{
			delete this;
		}

		return Refs;
	}

	uint32 GetRefCount() const
	{
		return uint32( NumRefs );
	}

private:
	mutable int32 NumRefs;
};

template<typename ReferencedType>
class TRefCountPtr
{
	typedef ReferencedType* ReferenceType;
public:
	FORCEINLINE TRefCountPtr()
		: Reference( nullptr )
	{

	}

	TRefCountPtr( ReferencedType* InReference , bool bAddRef = true )
	{
		Reference = InReference;
		if ( Reference && bAddRef )
		{
			Reference->AddRef();
		}
	}

	TRefCountPtr( const TRefCountPtr& Copy )
	{
		Reference = Copy.Reference;
		if ( Reference )
		{
			Reference->AddRef();
		}
	}

	FORCEINLINE TRefCountPtr( TRefCountPtr&& Copy )
	{
		Reference = Copy.Reference;
		Copy.Reference = nullptr;
	}

	~TRefCountPtr()
	{
		if ( Reference )
		{
			Reference->Release();
		}
	}

	TRefCountPtr& operator= ( ReferenceType* InReference )
	{
		ReferenceType* oldReference = Reference;
		Reference = InReference;

		if ( Reference )
		{
			Reference->AddRef();
		}

		if ( oldReference )
		{
			oldReference->Release();
		}

		return *this;
	}

	FORCEINLINE TRefCountPtr& operator=( const TRefCountPtr& InPtr )
	{
		return *this = InPtr.Reference;
	}

	TRefCountPtr& operator = ( TRefCountPtr&& InPtr )
	{
		if (this != &InPtr )
		{
			ReferenceType* oldReference = Reference;
			Reference = InPtr.Reference;
			InPtr.Reference = nullptr;

			if ( oldReference )
			{
				oldReference->Release();
			}
		}

		return *this;
	}

	FORCEINLINE ReferencedType* operator->( ) const
	{
		return Reference;
	}

	FORCEINLINE operator ReferenceType() const
	{
		return Reference;
	}

	FORCEINLINE ReferencedType** GetInitReference()
	{
		*this = nullptr;
		return &Reference;
	}

	FORCEINLINE ReferencedType* GetReference() const
	{
		return Reference;
	}

	FORCEINLINE friend bool IsValidRef( const TRefCountPtr& InReference )
	{
		return InReference.Reference != nullptr;
	}

	FORCEINLINE bool IsValid() const
	{
		return Reference != nullptr;
	}

	FORCEINLINE void SafeRelease()
	{
		*this = nullptr;
	}

	uint32 GetRefCount()
	{
		uint32 Result = 0;
		if ( Reference )
		{
			Result = Reference->GetRefCount();
			assert( Result > 0 );
		}

		return Result;
	}

	FORCEINLINE void Swap( TRefCountPtr& InPtr )
	{
		ReferencedType* oldReference = Reference;
		Reference = InPtr.Reference;
		InPtr.Reference = oldReference;
	}

private:
	ReferencedType* Reference;
};
#endif