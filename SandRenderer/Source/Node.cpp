#include "PCH.h"
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
	auto it = m_Leafs.begin();

	while ( it != m_Leafs.end() )
	{
		if ( *it == Child )
		{
			( *it )->DetachParent();
			( *it ) = nullptr;
			it = m_Leafs.erase( it );
		}
		else
		{
			it++;
		}
	}

	/*for( auto& pLeaf : m_Leafs )
	{
	if( pLeaf == Child )
	{
	pLeaf->DetachParent();
	pLeaf = nullptr;
	}
	}*/
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

void Node::Render( PipelineManager* pPipelineManager , IParameterManager* pParameterManager , VIEW_TYPE ViewType )
{
	for( auto pChild : m_Leafs )
	{
		if( pChild )
		{
			// 渲染Entity
			pChild->Render( pPipelineManager , pParameterManager , ViewType );
		}
	}

	for( auto pNode : m_Nodes )
	{
		if( pNode )
		{
			// 渲染该节点下的Entity
			pNode->Render( pPipelineManager , pParameterManager , ViewType );
		}
	}
}

void Node::Update( float time )
{
	UpdateLocal( time );
	UpdateWorld();

	for( auto pChild : m_Leafs )
	{
		if( pChild )
		{
			pChild->Update( time );
		}
	}

	for( auto pChild : m_Nodes )
	{
		if( pChild )
		{
			pChild->Update( time );
		}
	}
}

void Node::UpdateLocal( float time )
{
	// 各控制器更新Node的局部位置
	m_Controllers.Update( time );

	// 使用Rotation和Translate构造新的LocalMatrix
	m_Transform.UpdateLocal();
}

void Node::UpdateWorld()
{
	if( m_pParent )
	{
		m_Transform.UpdateWorld( m_pParent->GetTransformRef().GetWorldMatrix() );
	}
	else
	{
		m_Transform.UpdateWorld();
	}
}
