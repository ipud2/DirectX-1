#include "Entity.h"

using namespace Sand;

Entity::Entity()
{
	m_Parent = nullptr;
}

Entity::~Entity()
{

}

void Entity::AttachParent( Node* pParent )
{
	m_Parent = pParent;
}

void Entity::DetachParent()
{
	m_Parent = nullptr;
}

Node* Entity::GetParent()
{
	return m_Parent;
}

std::wstring Entity::GetName()
{
	return m_Name;
}

void Entity::SetName( std::wstring name )
{
	m_Name = name;
}

Transform& Entity::GetTransformRef()
{
	return m_Transform;
}