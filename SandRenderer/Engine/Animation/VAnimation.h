#ifndef V_ANIMATION_H
#define V_ANIMATION_H

#include <string>

#include "Matrix4f.h"

namespace Sand
{
	struct Joint
	{
		Matrix4f m_invBindPose;			// ������֮��任
		const char* m_name;				// �ؽ�����
		unsigned int m_iParentIndex;	// ���ڵ�����
	};

	struct Skeleton
	{
		unsigned int	m_JointCount;	// �ؽ���Ŀ
		Joint*			m_aJoint;		// �ؽ�����
	};

	struct JointPose
	{
		//Vector3f m_Trans;
		//float	m_Scale;		// ��Ϊͳһ�任
		//// Quaternion m_rot;

		Matrix4f ToParentTransform;
	};

	struct SkeletonPose
	{
		Skeleton* m_pSkeleton;			// ���� + �ؽ�����
		JointPose*	m_aLocalPose;		// ����ֲ��ؽ�����
		Matrix4f*	m_aGlobalPose;		// ���ȫ�ֹؽ�����
	};

	struct SkinnedVertex
	{
		float m_position[3];
		float m_normal[3];
		float m_u , m_v;
		int m_JointNum;
		unsigned int* m_JointIndex;
		float* m_JointWeight;			// ��ĿΪm_JointNum - 1 , ��Ϊ�ܺ�Ϊ1.0�����һ�����������
	};
}
#endif