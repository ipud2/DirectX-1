#ifndef Actor_h
#define Actor_h

#include "Node.h"
#include "Entity.h"

namespace Sand
{
	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		Node* GetRootNode() const;
		Node* GetRootNode();

	public:
		void AddElement( Entity* pElement );
		void RemoveElement( Entity* pElement );
		void AddElement( Node* pElement );
		void RemoveElement( Node* pElement );

	protected:
		Node* m_pRoot;

		std::vector<Entity*> m_vEntityElements;
		std::vector<Node*> m_vNodeElements;
	};
};
#endif