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

		// ----------引用--------------------
		const std::vector<Entity*>& GetLeafsRef();
		const std::vector<Node*>& GetNodesRef();

		Transform& GetTransformRef();
		
		ControllerPack<Node>& GetControllersRef();

	protected:
		std::wstring m_Name;

		// 所有的叶子节点都是Entity
		std::vector<Entity*> m_Leafs;
		std::vector<Node*> m_Nodes;

		// 父节点
		Node* m_pParent;

		// 控制变换
		Transform m_Transform;

		ControllerPack<Node> m_Controllers;
	};
}
#endif