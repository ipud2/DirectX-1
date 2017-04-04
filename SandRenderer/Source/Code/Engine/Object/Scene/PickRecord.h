#ifndef PickRecord_h
#define PickRecord_h

namespace Sand
{
	class Entity;

	// 记录相交的物体
	// 并且记录相交的参数
	class PickRecord
	{
	public:
		PickRecord();
		virtual ~PickRecord();

	public:
		Entity* m_pEntity;
		float m_fDistance;
	};
}

#endif