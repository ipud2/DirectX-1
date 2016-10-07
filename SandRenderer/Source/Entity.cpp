#include "PCH.h"
#include "Entity.h"
#include "Node.h"
#include "PipelineManager.h"
#include "ParameterManager.h"

using namespace Sand;

Entity::Entity()
	:m_Parent( nullptr ) ,
	m_Name( L"" ) ,

	m_Controllers( this ) ,
	Visual()
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

ControllerPack<Entity>& Entity::GetControllersRef()
{
	return m_Controllers;
}

Renderable& Entity::GetRenderableRef()
{
	return Visual;
}

void Entity::Update( float time )
{
	UpdateLocal( time );
	UpdateWorld();

	if( Visual.ShaderEffect != nullptr )
	{
		Visual.ShaderEffect->Update( time );
	}
}

void Entity::UpdateLocal( float fTime )
{
	// 更新所有的Controller
	m_Controllers.Update( fTime );

	// 使用旋转和平移分量加载局部空间矩阵
	m_Transform.UpdateLocal();
}

void Entity::UpdateWorld()
{
	if( m_Parent )
	{
		m_Transform.UpdateWorld( m_Parent->GetTransformRef().GetWorldMatrix() );
	}
	else
	{
		m_Transform.UpdateWorld();
	}
}

void Entity::Render( PipelineManager* pPipelineManager , IParameterManager* pParamManager , VIEW_TYPE View )
{
	if( Visual.IAStageExecutor != nullptr && Visual.ShaderEffect != nullptr )
	{
		// 判断该视图是否可渲染
		if( Visual.ShaderEffect->Schemes[View].bRender )
		{
			// 设置渲染管线相关参数
			Visual.ShaderEffect->SetRenderParams( pParamManager , View );
			
			if ( Visual.pMaterial != nullptr )
			{
				// 设置物体表面材质
				Visual.pMaterial->Update( pParamManager );
			}

			this->UpdateRenderParams( pParamManager );

			for ( int i = 0; i < Visual.IAStageExecutor->GetSubObjectCount(); i++ )
			{
				Visual.IAStageExecutor->UpdateRenderParameters( pParamManager , i );

				// 配置渲染状态，各shader阶段资源
				Visual.ShaderEffect->Schemes[View].pEffect->ConfigurePipeline( pPipelineManager , pParamManager );
				// 应用渲染状态，应用shader资源
				pPipelineManager->ApplyPipelineResource();

				// 应用InputAssembler阶段资源
				Visual.IAStageExecutor->Execute( pPipelineManager , pParamManager , i );
			}
		}
	}
}

void Entity::UpdateRenderParams( IParameterManager* pParameterManager )
{
	// 设置世界矩阵
	pParameterManager->SetWorldMatrixParameterData( &m_Transform.GetWorldMatrix() );

	// 逐层的遍历参数，并进行设置
	m_EntityParameterWriters.UpdateRenderParam( pParameterManager );
}

ParameterContainer& Entity::GetParameterWritersRef()
{
	return m_EntityParameterWriters;
}