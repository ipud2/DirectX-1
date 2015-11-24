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
	// �ж�pParamRef��Identifier�Ƿ��뵱ǰ��Identifier��ͬ������ͬ����˵����Ҫ����
	if( m_bAutoUpdate )		// ֻ�е���Ҫ�Զ�����ʱ����ִ�����²���
	{
		bool doUpdate = false;	// Ĭ�ϲ���Ҫ����

		for( int i = 0; i < m_vElements.size(); i++ )
		{
			if( m_vElements[i].pParamRef->GetIdentifier() != m_vElements[i].Identifier )
			{
				// ˵�������Լ�������
				doUpdate = true;
				break;
			}
		}

		if( doUpdate )
		{
			// Map Resource
			/*D3D11_MAPPED_SUBRESOURCE MappedResource;
			pPipelineManager->MapResource( this , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &MappedResource );*/

			D3D11_MAPPED_SUBRESOURCE MappedResource = pPipelineManager->MapResource( this , 0 , D3D11_MAP_WRITE_DISCARD , 0 );

			for( int i = 0; i < m_vElements.size(); i++ )
			{
				m_vElements[i].Identifier = m_vElements[i].pParamRef->GetIdentifier();

				unsigned int Offset = m_vElements[i].Offset;

				if( m_vElements[i].VarClass == D3D_SVC_VECTOR )
				{
					// ��Ԫ��Ϊ����
					Vector4f vector = pParameterManager->GetVectorParameterData( m_vElements[i].pParamRef );
					Vector4f* pBuf = ( Vector4f* )( ( char* )MappedResource.pData + Offset );
					*pBuf = vector;
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
				else
				{
					// �������Ͳ��账��
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
	// �����ж�index�Ƿ����
	assert( index < m_vElements.size() );

	ConstantBufferElementDesc e = m_vElements[index];

	// Identifier�����������ڱȽ��жϲ�����ֵ�Ƿ������ж�
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