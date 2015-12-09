#include "PCH.h"
#include "ConstantBuffer.h"
#include "PipelineManager.h"
#include "Log.h"

using namespace Sand;

ConstantBuffer::ConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer )
{
	m_Buffer = pBuffer;
	m_bAutoUpdate = true;
}

ConstantBuffer::~ConstantBuffer()
{

}

ResourceType ConstantBuffer::GetType()
{
	return RT_CONSTANT_BUFFER;
}

void ConstantBuffer::AddElement( ConstantBufferElementDesc element )
{
	m_vElements.push_back( element );
}

void ConstantBuffer::EvaluateElements( PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	// 判断pParamRef的Identifier是否与当前的Identifier相同，若不同，则说明需要更新
	if( m_bAutoUpdate )		// 只有当需要自动更新时，才执行以下操作
	{
		bool doUpdate = false;	// 默认不需要更新

		for( int i = 0; i < m_vElements.size(); i++ )
		{
			if( m_vElements[i].pParamRef->GetIdentifier() != m_vElements[i].Identifier )
			{
				// 说明数据以及被更新
				doUpdate = true;
				break;
			}
		}

		if( doUpdate )
		{
			// Map Resource
			D3D11_MAPPED_SUBRESOURCE MappedResource;
			pPipelineManager->MapResource( this , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &MappedResource );

			for( int i = 0; i < m_vElements.size(); i++ )
			{
				m_vElements[i].Identifier = m_vElements[i].pParamRef->GetIdentifier();

				unsigned int Offset = m_vElements[i].Offset;

				if ( m_vElements[i].VarClass == D3D_SVC_SCALAR )
				{
					if ( m_vElements[i].VarType == D3D_SVT_FLOAT )
					{
						// ---------------float--------------
					}
					else if ( m_vElements[i].VarType == D3D_SVT_BOOL )
					{
						// ---------------bool--------------
						bool value = pParameterManager->GetBoolParameterData( m_vElements[i].pParamRef );
						bool* pBuf = ( bool* )( ( char* )MappedResource.pData + Offset );
						*pBuf = value;

					}
					else if ( m_vElements[i].VarType == D3D_SVT_INT )
					{
						// ---------------int------------------
					}
				}
				else if( m_vElements[i].VarClass == D3D_SVC_VECTOR )
				{
					if ( m_vElements[i].Columns == 4 )
					{
						// -------------float4-----------------
						Vector4f vector = pParameterManager->GetVector4fParameterData( m_vElements[i].pParamRef );
						Vector4f* pBuf = ( Vector4f* )( ( char* )MappedResource.pData + Offset );
						*pBuf = vector;
					}
					else if ( m_vElements[i].Columns == 3 )
					{
						// ----------------float2-----------------
						Vector3f vector = pParameterManager->GetVector3fParameterData( m_vElements[i].pParamRef );
						Vector3f* pBuf = ( Vector3f* )( ( char* )MappedResource.pData + Offset );
						*pBuf = vector;
					}
					else if ( m_vElements[i].Columns == 2 )
					{
						// ------------float2-----------------
						Vector2f vector = pParameterManager->GetVector2fParameterData( m_vElements[i].pParamRef );
						Vector2f* pBuf = ( Vector2f* )( ( char* )MappedResource.pData + Offset );
						*pBuf = vector;
					}
				}
				else if( m_vElements[i].VarClass == D3D_SVC_MATRIX_COLUMNS || m_vElements[i].VarClass == D3D_SVC_MATRIX_ROWS )
				{
					unsigned int count = m_vElements[i].ElementCount;

					if( count == 0 )
					{
						Matrix4f matrix = pParameterManager->GetMatrixParameterData( m_vElements[i].pParamRef );
						Matrix4f* pBuf = ( Matrix4f* )( ( char* )MappedResource.pData + Offset );
						*pBuf = matrix;
					}
					else
					{
						unsigned int size = m_vElements[i].Size;

						if( size == count * sizeof( Matrix4f ) )
						{
							Matrix4f* pMatrices = pParameterManager->GetMatrixArrayParameterData( m_vElements[i].pParamRef );
							memcpy( ( char* )MappedResource.pData + Offset , ( char* )pMatrices , size );
						}
						else
						{
							Log::Get().Write( L"MisMatch in matrix array count , update will not be performed!!" );
						}
						
					}
				}
				else if ( m_vElements[i].VarClass == D3D_SVC_STRUCT )
				{
					char* pStructure = pParameterManager->GetStructureParameterData( m_vElements[i].pParamRef );
					memcpy( ( char* )MappedResource.pData + Offset , pStructure , m_vElements[i].Size );
				}
			}

			// UnMap Resource
			pPipelineManager->UnMapResource( this , 0 );
		}

	}
}

void ConstantBuffer::EmptyElements()
{
	m_vElements.clear();
}

bool ConstantBuffer::ConstainElement( int index , const ConstantBufferElementDesc & element )
{
	// 首先判断index是否合理
	assert( index < m_vElements.size() );

	ConstantBufferElementDesc e = m_vElements[index];

	// Identifier的作用是用于比较判断参数的值是否发生了判断
	if( ( e.ElementCount == element.ElementCount ) &&
		( e.Offset == element.Offset ) &&
		( e.Size == element.Size ) &&
		( e.VarClass == element.VarClass ) &&
		( e.pParamRef = element.pParamRef ) )
	{
		return true;
	}

	return false;
}

void ConstantBuffer::SetAutoUpdate( bool bAutoUpdate )
{
	m_bAutoUpdate = bAutoUpdate;
}

bool ConstantBuffer::GetAutoUpdate()
{
	return m_bAutoUpdate;
}