#include "Engine/PCH.h"
#include "VSkeletonManager.h"
#include "VSkeleton.h"

using namespace Sand;

VSkeletonManager& VSkeletonManager::GetInstance()
{
	static VSkeletonManager SkeletonInstance;

	return SkeletonInstance;
}


VSkeletonManager::VSkeletonManager()
{
	m_vSkeleton.clear();
}

int VSkeletonManager::CreateSkeleton()
{
	VSkeleton* pSkeleton = new VSkeleton;

	m_vSkeleton.push_back( pSkeleton );

	return ( int )m_vSkeleton.size() - 1;
}

VSkeleton* VSkeletonManager::GetSkeleton( int index )
{
	if( index >= 0 && index < ( int )m_vSkeleton.size() )
	{
		return m_vSkeleton[index];
	}

	return nullptr;
}