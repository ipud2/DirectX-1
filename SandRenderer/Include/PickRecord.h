#ifndef PickRecord_h
#define PickRecord_h

namespace Sand
{
	class Entity;

	// ��¼�ཻ������
	// ���Ҽ�¼�ཻ�Ĳ���
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