#include "Engine/PCH.h"
#include "VJoint.h"

#define _CRT_SECURE_NO_WARNINGS

Sand::VJoint::VJoint()
{
	m_invBindPose.MakeIdentity();
	m_iParentIndex = -1;

	m_name = new char[1024];
	m_name[0] = '\0';
}

void Sand::VJoint::AttachParent( int iParentIndex )
{
	m_iParentIndex = iParentIndex;
}

void Sand::VJoint::AttachChild( int iChildIndex )
{
	bool bAttach = true;

	for ( auto iter = m_vChildList.begin(); iter != m_vChildList.end(); iter++ )
	{
		if ( *iter == iChildIndex )
		{
			bAttach = false;
			break;
		}
	}

	if ( bAttach )	m_vChildList.push_back( iChildIndex );
}

void Sand::VJoint::SetName( const char* szName )
{
	memset( m_name , 0 , 1024 );
	strcpy_s( m_name , 1024 , szName );
}

Sand::VJoint::~VJoint()
{
	delete[] m_name;
}

void Sand::VJoint::AttachSkeleton( VSkeleton* pSkeleton )
{
	assert( pSkeleton != nullptr );
	m_pSkeleton = pSkeleton;
}