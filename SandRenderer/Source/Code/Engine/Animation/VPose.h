#ifndef V_POSE_H
#define V_POSE_H

#include "Engine/Math/Matrix4f.h"

namespace Sand
{
	// ÿ��Pose����Skeleton��һ��ؽڱ任����

	struct JointPose
	{
		//Vector3f m_Trans;
		//float	m_Scale;		// ��Ϊͳһ�任
		// Quaternion m_rot;

		Matrix4f ToParentTransform;
	};

	class VSKeleton;

	class VPose
	{
	public:
		VPose();

	protected:
		VSKeleton*	m_pSkeleton;		// ���� + �ؽ�����
		JointPose*	m_aLocalPose;		// ����ֲ��ؽ�����
		Matrix4f*	m_aGlobalPose;		// ���ȫ�ֹؽ�����
	};
}
#endif