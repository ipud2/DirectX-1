#ifndef Node_h
#define Node_h

#include "PCH.h"
#include "Transform.h"
#include "IController.h"
#include "SceneRenderTask.h"

namespace Sand
{
	class Entity;

	class Node
	{
	public:
		Node();
		~Node();
		
		/*
			Recursive Rendering
		*/
		void Render( PipelineManager* pPipelineManager , IParameterManager* pParameterManager , VIEW_TYPE ViewType );

		/*
			�Զ����±���������Local , World Matrix
		*/
		void Update( float time );

	protected:
		void UpdateLocal( float time );
		void UpdateWorld();


		// ---------------Attach or Detach Node------------------
	public:
		void AttachChild( Entity* Child );
		void AttachChild( Node* Child );
		void DetachChild( Entity* Child );
		void DetachChild( Node* Child );

		void AttachParent( Node* Parent );
		void DetachParent();
		Node* GetParent();

		// -------------------Name--------------------------
	public:
		void SetName( const std::wstring& name );
		std::wstring GetName() const;

		// Get Class Data Member Object Reference
	public:
		const std::vector<Entity*>& GetLeafsRef();
		const std::vector<Node*>& GetNodesRef();

		Transform& GetTransformRef();
		
		ControllerPack<Node>& GetControllersRef();

	protected:
		std::wstring m_Name;

		Node* m_pParent;

		// ���е�Ҷ�ӽڵ㶼��Entity
		std::vector<Entity*> m_Leafs;
		std::vector<Node*> m_Nodes;

		// ���Ʊ任
		Transform m_Transform;

		ControllerPack<Node> m_Controllers;
	};
};
#endif