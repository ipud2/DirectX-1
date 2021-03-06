#include <Engine/PCH.h>
#include "Engine/Object/Actor/Actor.h"

using namespace Sand;

Actor::Actor()
{
	m_pRoot = new Node;

	AddElement( m_pRoot );
}

Actor::~Actor()
{
	for( auto pEntity : m_vEntityElements )
	{
		SAFE_DELETE( pEntity );
	}

	for( auto pNode : m_vNodeElements )
	{
		SAFE_DELETE( pNode );
	}
}

Node* Actor::GetRootNode() const
{
	return m_pRoot;
}

Node* Actor::GetRootNode()
{
	return m_pRoot;
}

void Actor::AddElement( Node* pElement )
{
	m_vNodeElements.push_back( pElement );
}

void Actor::AddElement( Entity* pElement )
{
	m_vEntityElements.push_back( pElement );
}

void Actor::RemoveElement( Node* pElement )
{
	auto it = m_vNodeElements.begin();

	while( it != m_vNodeElements.end() )
	{
		if( *it == pElement )
		{
			it = m_vNodeElements.erase( it );
		}
		else
		{
			it++;
		}
	}
}

void Actor::RemoveElement( Entity* pElement )
{
	auto it = m_vEntityElements.begin();

	while( it != m_vEntityElements.end() )
	{
		if( *it == pElement )
		{
			it = m_vEntityElements.erase( it );
		}
		else
		{
			it++;
		}
	}
}