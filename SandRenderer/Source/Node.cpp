#include "Node.h"
#include "Entity.h"

using namespace Sand;

Node::Node()
	:m_pParent( nullptr ) ,
	m_Controllers( this )
{

}

Node::~Node()
{

}

void Node::AttachChild( Node* Child )
{
	// 若节点中有空节点，则代替
	for( auto pChild : m_Nodes )
	{
		if( pChild == nullptr )
		{
			pChild = Child;
			Child->AttachParent( this );
		}
	}

	// 压入容器
	m_Nodes.push_back( Child );
	Child->AttachParent( this );
}

void Node::AttachChild( Entity* Child )
{
	// 若叶子中有空节点，则代替
	for( auto pLeaf : m_Leafs )
	{
		if( pLeaf == nullptr )
		{
			pLeaf = Child;
			Child->AttachParent( this );
		}
	}

	m_Leafs.push_back( Child );
	Child->AttachParent( this );
}

void Node::DetachChild( Entity* Child )
{
	for( auto pLeaf : m_Leafs )
	{
		if( pLeaf == Child )
		{
			pLeaf->DetachParent();
			pLeaf = nullptr;
		}
	}
}

void Node::DetachChild( Node* Child )
{
	for( auto pNode : m_Nodes )
	{
		if( pNode == Child )
		{
			pNode->DetachParent();
			pNode = nullptr;
		}
	}
}

void Node::AttachParent( Node* Parent )
{
	m_pParent = Parent;
}

void Node::DetachParent()
{
	m_pParent = nullptr;
}

Node* Node::GetParent()
{
	return m_pParent;
}

void Node::SetName( const std::wstring& name )
{
	m_Name = name;
}

std::wstring Node::GetName() const
{
	return m_Name;
}

const std::vector<Node*>& Node::GetNodesRef()
{
	return m_Nodes;
}

const std::vector<Entity*>& Node::GetLeafsRef()
{
	return m_Leafs;
}

Transform& Node::GetTransformRef()
{
	return m_Transform;
}

ControllerPack<Node>& Node::GetControllersRef()
{
	return m_Controllers;
}