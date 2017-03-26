#include "PCH.h"
#include "Scene.h"
#include "Log.h"
#include "SceneGraph.h"

using namespace Sand;

Scene::Scene()
{
	// 创建场景根节点
	m_pRootNode = new Node();
}

Scene::~Scene()
{
	for( auto pActor : m_vActors )
	{
		SAFE_DELETE( pActor );
	}
}

Node* Scene::GetRootNode()
{
	return m_pRootNode;
}

void Scene::AddCamera( BaseCamera* camera )
{
	m_vCameras.push_back( camera );
	camera->SetScene( this );
	AddActor( camera );
}

BaseCamera* Scene::GetCamera( unsigned int index )
{
	assert( index < m_vCameras.size() );

	return m_vCameras[index];
}

unsigned int Scene::GetCameraCount()
{
	return ( unsigned int )m_vCameras.size();
}

void Scene::AddLight( Light* pLight )
{
	m_vLights.push_back( pLight );

	AddActor( pLight );
}

Light* Scene::GetLight( unsigned int index )
{
	assert( index < m_vLights.size() );

	return ( m_vLights[index] );
}

unsigned int Scene::GetLightCount()
{
	return ( unsigned int )m_vLights.size();
}

void Scene::AddActor( Actor* pActor )
{
	// attach node
	m_pRootNode->AttachChild( pActor->GetRootNode() );
	m_vActors.push_back( pActor );
}

void Scene::RemoveActor( Actor* pActor )
{
	auto it = m_vActors.begin();

	while( it != m_vActors.end() )
	{
		if( *it == pActor )
		{
			it = m_vActors.erase( it );
		}
		else
		{
			it++;
		}
	}

	// 解除与parent的联系
	Node* pParent = static_cast< Node* >( pActor->GetRootNode()->GetParent() );
	if( pParent )
	{
		pParent->DetachChild( pActor->GetRootNode() );
	}
}

void Scene::Update( float time )
{
	m_pRootNode->Update( time );
}

void Scene::Render( Renderer* pRenderer )
{
	for( auto pCamera : m_vCameras )
	{
		// 每次以一种新的ViewType渲染场景时
		// 都初始化渲染参数
		SceneParameterWriters.InitRenderParams();
		pCamera->RenderFrame( pRenderer );
	}
}