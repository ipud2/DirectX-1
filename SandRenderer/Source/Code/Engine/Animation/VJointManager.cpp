#include "Engine/PCH.h"
#include "VJointManager.h"
#include "VJoint.h"

using namespace Sand;

VJointManager& VJointManager::GetInstance()
{
	static VJointManager JointManager;
	return JointManager;
}

VJointManager::VJointManager()
{
	m_vJoint.clear();
}

int VJointManager::CreateJoint()
{
	VJoint* pJoint = new VJoint;

	m_vJoint.push_back( pJoint );

	return ( int )m_vJoint.size() - 1;
}

VJoint* VJointManager::GetJoint( int index )
{
	if ( index >= 0 && index < ( int )m_vJoint.size() )
	{
		return m_vJoint[index];
	}

	return nullptr;
}

int VJointManager::FindJoint( VJoint* pJoint )
{
	int index = -1;

	for ( auto iter = m_vJoint.begin(); iter != m_vJoint.end(); iter++ )
	{
		if ( *iter == pJoint )
		{
			index = ( int )( iter - m_vJoint.begin() );
			break;
		}
	}

	return index;
}