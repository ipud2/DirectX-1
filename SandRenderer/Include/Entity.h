#ifndef Entity_h
#define Entity_h

#include "Transform.h"
#include "IController.h"

namespace Sand
{
	class Node;

	class Entity
	{
	public:
		Entity();
		~Entity();

		void AttachParent( Node* pParent );
		void DetachParent();
		Node* GetParent();

		Transform& GetTransformRef();

		std::wstring GetName();
		void SetName( std::wstring name );

	protected:
		std::wstring m_Name;

		// ���ڵ�
		Node* m_Parent;

		// ���ڿ�������任
		Transform m_Transform;
	};
}
#endif