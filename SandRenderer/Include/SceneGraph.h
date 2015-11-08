#ifndef SceneGraph_h
#define SceneGraph_h

#include "Entity.h"
#include "Node.h"

namespace Sand
{
	template<typename T>
	Node* GetParent( T* element )
	{
		assert( element != nullptr );

		return element->GetParent();
	}

	template<typename T>
	Node* GetRoot( T* element )
	{
		assert( element != nullptr );

		Node* pParent = GetParent( element );

		while( pParent != nullptr )
		{
			element = pParent;
			pParent = GetParent( element );
		}

		return pParent;
	}

	template<typename T>
	int GraphDepth( T* element )
	{
		// 根节点的深度为0

		Node* pParent = GetParent( element );

		if( pParent == nullptr )
		{
			return 0;
		}
		else
		{
			return GraphDepth( pParent ) + 1;
		}
	}

	void GetAllEntities( Node* node , std::vector<Entity*>& set );
}

#endif