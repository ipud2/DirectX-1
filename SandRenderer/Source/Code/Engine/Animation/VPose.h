#ifndef V_POSE_H
#define V_POSE_H

#include "Engine/Math/Matrix4f.h"

namespace Sand
{
	// 每个Pose就是Skeleton的一组关节变换矩阵

	struct JointPose
	{
		//Vector3f m_Trans;
		//float	m_Scale;		// 仅为统一变换
		// Quaternion m_rot;

		Matrix4f ToParentTransform;
	};

	class VSKeleton;

	class VPose
	{
	public:
		VPose();

	protected:
		VSKeleton*	m_pSkeleton;		// 骨骼 + 关节数量
		JointPose*	m_aLocalPose;		// 多个局部关节姿势
		Matrix4f*	m_aGlobalPose;		// 多个全局关节姿势
	};
}
#endif