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
	// �������е�Controller
	m_Controllers.Update( fTime );

	// ʹ����ת��ƽ�Ʒ������ؾֲ��ռ����
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
		// �жϸ���ͼ�Ƿ����Ⱦ
		if( Visual.ShaderEffect->Schemes[View].bRender )
		{
			// ������Ⱦ������ز���
			Visual.ShaderEffect->SetRenderParams( pParamManager , View );
			
			if ( Visual.pMaterial != nullptr )
			{
				// ��������������
				Visual.pMaterial->Update( pParamManager );
			}

			this->UpdateRenderParams( pParamManager );

			for ( int i = 0; i < Visual.IAStageExecutor->GetSubObjectCount(); i++ )
			{
				Visual.IAStageExecutor->UpdateRenderParameters( pParamManager , i );

				// ������Ⱦ״̬����shader�׶���Դ
				Visual.ShaderEffect->Schemes[View].pEffect->ConfigurePipeline( pPipelineManager , pParamManager );
				// Ӧ����Ⱦ״̬��Ӧ��shader��Դ
				pPipelineManager->ApplyPipelineResource();

				// Ӧ��InputAssembler�׶���Դ
				Visual.IAStageExecutor->Execute( pPipelineManager , pParamManager , i );
			}
		}
	}
}

void Entity::UpdateRenderParams( IParameterManager* pParameterManager )
{
	// �����������
	pParameterManager->SetWorldMatrixParameterData( &m_Transform.GetWorldMatrix() );

	// ���ı�������������������
	m_EntityParameterWriters.UpdateRenderParam( pParameterManager );
}

ParameterContainer& Entity::GetParameterWritersRef()
{
	return m_EntityParameterWriters;
}