#ifndef V_JOINT_MANAGER_H
#define V_JOINT_MANAGER_H

#include <vector>

namespace Sand
{
	class VJoint;

	class VJointManager
	{
	public:
		static VJointManager& GetInstance();

		int CreateJoint();

		VJoint* GetJoint( int index );

		int FindJoint( VJoint* pJoint );

	protected:
		VJointManager();
		VJointManager( const VJointManager& );

	protected:
		std::vector<VJoint*> m_vJoint;
	};
}
#endif