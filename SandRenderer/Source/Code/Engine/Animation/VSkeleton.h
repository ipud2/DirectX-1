#ifndef VSKELETON_H
#define VSKELETON_H

#include <vector>

namespace Sand
{
	class VJoint;

	class VSkeleton
	{
	public:
		VSkeleton();

		~VSkeleton();

		int GetRootJoint();

	protected:
		int m_iRootJointIndex;
	};
}
#endif