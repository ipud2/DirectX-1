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

		// 父节点
		Node* m_Parent;

		// 用于控制物体变换
		Transform m_Transform;
	};
}
#endif