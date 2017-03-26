#pragma once

#include "PCH.h"

FORCEINLINE int32 DefaultCalculateSlackShrink( int32 NumElements , int32 NumAllocatedElements , SIZE_T BytesPerElement )
{
	int32 RetVal = 0;

	const uint32 CurrentSlackElements = NumAllocatedElements - NumElements;
	const SIZE_T CurrentSlackBytes = ( NumAllocatedElements - NumElements ) * BytesPerElement;
	const bool bTooManySlackBytes = CurrentSlackBytes >= 16384;
	const bool bTooManySlackElement = 3 * NumElements < 2 * NumAllocatedElements;

	if( ( bTooManySlackBytes || bTooManySlackElement ) && ( CurrentSlackElements > 64 || !NumElements ) )
	{
		RetVal = NumElements;
	}
	else
	{
		RetVal = NumAllocatedElements;
	}

	return RetVal;
}

FORCEINLINE int32 DefaultCalculateSlackGrow( int32 NumElements , int32 NumAllocatedElements , SIZE_T BytesPerElement )
{
	int32 RetVal = 0;

	SIZE_T Grow = 4;	// this is the amount for the first alloc
	if( NumAllocatedElements || SIZE_T( NumElements ) > Grow )
	{
		// Allocate slack for the array proportional to its size
		Grow = SIZE_T( NumElements ) + 3 * SIZE_T( NumElements ) / 8 + 16;
	}
	
	RetVal = (int)Grow;

	// NumElements and MaxElements are stored in 32-bit signed integers so we must be careful not to overflow here.
	if( NumElements > RetVal )
	{
		RetVal = Max_int32;
	}

	return RetVal;
}

FORCEINLINE int32 DefaultCalculateSlackReserve( int32 NumElements , SIZE_T BytesPerElement )
{
	int32 RetValue = NumElements;

	return RetValue;
}