#include "Engine/PCH.h"
#include "VSkeleton.h"
#include "VJoint.h"
#include "VJointManager.h"

Sand::VSkeleton::VSkeleton()
{
	m_iRootJointIndex = -1;
}

int Sand::VSkeleton::GetRootJoint()
{
	return m_iRootJointIndex;
}