#ifndef V_ANIMATION_H
#define V_ANIMATION_H

#include <string>

#include "Matrix4f.h"

namespace Sand
{
	struct Joint
	{
		Matrix4f m_invBindPose;			// 绑定姿势之逆变换
		const char* m_name;				// 关节名称
		unsigned int m_iParentIndex;	// 父节点索引
	};

	struct Skeleton
	{
		unsigned int	m_JointCount;	// 关节数目
		Joint*			m_aJoint;		// 关节数组
	};

	struct JointPose
	{
		//Vector3f m_Trans;
		//float	m_Scale;		// 仅为统一变换
		//// Quaternion m_rot;

		Matrix4f ToParentTransform;
	};

	struct SkeletonPose
	{
		Skeleton* m_pSkeleton;			// 骨骼 + 关节数量
		JointPose*	m_aLocalPose;		// 多个局部关节姿势
		Matrix4f*	m_aGlobalPose;		// 多个全局关节姿势
	};

	struct SkinnedVertex
	{
		float m_position[3];
		float m_normal[3];
		float m_u , m_v;
		int m_JointNum;
		unsigned int* m_JointIndex;
		float* m_JointWeight;			// 数目为m_JointNum - 1 , 因为总和为1.0，最后一个可以算出来
	};
}
#endif