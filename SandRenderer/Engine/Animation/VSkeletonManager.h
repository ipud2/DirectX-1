#ifndef V_SKELETON_MANAGER_H
#define V_SKELETON_MANAGER_H

namespace Sand
{
	class VSkeleton;

	class VSkeletonManager
	{
	public:
		static VSkeletonManager& GetInstance();

		int CreateSkeleton();

		VSkeleton* GetSkeleton( int index );

	protected:
		VSkeletonManager();
		VSkeletonManager( const VSkeletonManager& );

	private:
		std::vector<VSkeleton*> m_vSkeleton;
	};
}
#endif