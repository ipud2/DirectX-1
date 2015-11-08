#ifndef Node_h
#define Node_h

#include "PCH.h"
#include "Transform.h"
#include "IController.h"

namespace Sand
{
	class Entity;

	class Node
	{
	public:
		Node();
		~Node();

		// attach / detach
		void AttachChild( Entity* Child );
		void AttachChild( Node* Child );
		void DetachChild( Entity* Child );
		void DetachChild( Node* Child );

		void AttachParent( Node* Parent );
		void DetachParent();
		Node* GetParent();

		// ------------Name--------------
		void SetName( const std::wstring& name );
		std::wstring GetName() const;

		// ----------����--------------------
		const std::vector<Entity*>& GetLeafsRef();
		const std::vector<Node*>& GetNodesRef();

		Transform& GetTransformRef();
		
		ControllerPack<Node>& GetControllersRef();

	protected:
		std::wstring m_Name;

		// ���е�Ҷ�ӽڵ㶼��Entity
		std::vector<Entity*> m_Leafs;
		std::vector<Node*> m_Nodes;

		// ���ڵ�
		Node* m_pParent;

		// ���Ʊ任
		Transform m_Transform;

		ControllerPack<Node> m_Controllers;
	};
}
#endif