#include <Engine/PCH.h>
#include "SceneGraph.h"

using namespace Sand;

void Sand::GetAllEntities( Node* node , std::vector<Entity*>& set )
{
	// ������������
	set.reserve( set.size() + node->GetLeafsRef().size() );
	set.insert( set.end() , node->GetLeafsRef().begin() , node->GetLeafsRef().end() );

	for( auto pNode : node->GetNodesRef() )
	{
		GetAllEntities( pNode , set );
	}
}