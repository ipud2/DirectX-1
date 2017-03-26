#ifndef V_JOINT_H
#define V_JOINT_H

#include "Matrix4f.h"

namespace Sand
{
	class VSkeleton;

	class VJoint
	{
	public:
		VJoint();

		~VJoint();

		void AttachParent( int iParentIndex );
		
		void AttachChild( int iChildIndex );
		
		void SetName( const char* szName );

		void AttachSkeleton( VSkeleton* pSkeleton );

	protected:
		Matrix4f			m_invBindPose;				// ������֮��任
		char*				m_name;						// �ؽ�����
		unsigned int		m_iParentIndex;				// ���ڵ�����
		std::vector<int>	m_vChildList;	
		VSkeleton*			m_pSkeleton;
	};
}

#endif