#include "PCH.h"
#include "Geometry.h"
#include "BufferConfig.h"
#include "Renderer.h"
#include "PipelineManager.h"

using namespace Sand;

Geometry::Geometry()
{
	m_PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_iVertexStructureSize = 0;
	m_iVertexCount = 0;
}

Geometry::~Geometry()
{

}

void Geometry::Execute( PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	// 清除设置
	pPipelineManager->GetInputAssemblerStageRef().ClearDesiredState();

	// -----------------------------------------Input Layout-----------------------------------------------
	int layout = GetInputLayout( pPipelineManager->ShaderStages[ST_VERTEX_SHADER]->DesiredState.ShaderProgramID.GetState() );
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.InputLayout.SetState( layout );
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.PrimitiveTopology.SetState( m_PrimitiveTopology );
	
	// ---------------------------------------Vertex Buffer----------------------------------------------
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.VertexBuffers.SetState( 0 , m_VertexBuffer->GetResourceID() );
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.VertexBufferStrides.SetState( 0 , m_iVertexStructureSize );
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.VertexBufferOffsets.SetState( 0 , 0 );

	// --------------------------------------Index Buffer-----------------------------------------------
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.IndexBuffers.SetState( m_IndexBuffer->GetResourceID() );
	pPipelineManager->GetInputAssemblerStageRef().DesiredState.IndexBufferFormat.SetState( DXGI_FORMAT_R32_UINT );

	pPipelineManager->ApplyInputResource();

	pPipelineManager->DrawIndexed( GetIndexCount() , 0 , 0 );
}

void Geometry::AddFace( int index_1 , int index_2 , int index_3 )
{
	m_vIndices.push_back( index_1 );
	m_vIndices.push_back( index_2 );
	m_vIndices.push_back( index_3 );
}

void Geometry::AddElement( VertexElement* pElement )
{
	// 先判断该类元素是否已经存在
	int index = -1;
	for( unsigned int i = 0; i < m_vElements.size(); i++ )
	{
		if( m_vElements[i]->m_SemanticName == pElement->m_SemanticName )
		{
			index = i;
		}
	}

	if( index == -1 )
	{
		// 说明目前不存在该字段
		m_vElements.push_back( pElement );
	}
	else
	{
		delete m_vElements[index];		// 释放原来的元素
		m_vElements[index] = pElement;	// 设置新元素
	}
}

void Geometry::LoadToBuffer()
{
	// --------------创建Vertex Buffer 和 Index Buffer的ResourceProxy对象--------------------

	// 计算顶点列表中顶点数目
	CalculateVertexCount();

	// 计算顶点结构大小
	CalculateVertexStructureSize();

	if( m_iVertexStructureSize > 0 )
	{
		// 计算保存所有顶点数据所需的字节大小
		unsigned int length = m_iVertexStructureSize * m_iVertexCount;

		// 创建数组用于保存所有顶点数据
		char* pData = new char[length];

		for( int i = 0; i < m_iVertexCount; i++ )
		{
			int offset = 0;
			for( int j = 0; j < m_vElements.size(); j++ )
			{
				// 将顶点各属性数据逐个拷贝
				memcpy( pData + i * m_iVertexStructureSize + offset , m_vElements[j]->GetDataPtr( i ) , m_vElements[j]->GetElementSizeInBytes() );
				offset += m_vElements[j]->GetElementSizeInBytes();
			}
		}

		// -------------------------------创建顶点缓存----------------------------------

		D3D11_SUBRESOURCE_DATA VertexInitData;
		VertexInitData.pSysMem = reinterpret_cast< void* >( pData );
		VertexInitData.SysMemPitch = 0;
		VertexInitData.SysMemSlicePitch = 0;

		// 创建顶点缓存描述
		BufferConfig VertexBufferConfig;
		VertexBufferConfig.SetDefaultVertexBuffer( length , false );

		// 创建Vertex Buffer
		m_VertexBuffer = Renderer::Get()->CreateVertexBuffer( &VertexBufferConfig , &VertexInitData );

		delete[] pData;

		// -----------------------------创建索引缓存-----------------------------------
		D3D11_SUBRESOURCE_DATA IndexInitData;
		IndexInitData.pSysMem = reinterpret_cast< void* >( &m_vIndices[0] );
		IndexInitData.SysMemPitch = 0;
		IndexInitData.SysMemSlicePitch = 0;

		BufferConfig IndexBufferConfig;
		IndexBufferConfig.SetDefaultIndexBuffer( m_vIndices.size() * sizeof( unsigned int ) , false );

		// 创建Index Buffer
		m_IndexBuffer = Renderer::Get()->CreateIndexBuffer( &IndexBufferConfig , &IndexInitData );
	}
}

int Geometry::CalculateVertexCount()
{
	// 计算顶点列表中顶点数目

	if( m_vElements.size() != 0 )
	{
		m_iVertexCount = m_vElements[0]->GetCount();
	}
	else
	{
		m_iVertexCount = 0;
	}

	return m_iVertexCount;
}

int Geometry::CalculateVertexStructureSize()
{
	// 计算顶点结构大小

	m_iVertexStructureSize = 0;

	for( auto pVertexElement : m_vElements )
	{
		m_iVertexStructureSize += pVertexElement->GetElementSizeInBytes();
	}

	return m_iVertexStructureSize;
}

void Geometry::GenerateInputLayout( int ShaderID )
{
	int ElementCount = m_vElements.size();

	if( ElementCount == 0 )
	{
		// 这种情况我们认为顶点数据是由shader自动生成的。

		std::vector<D3D11_INPUT_ELEMENT_DESC> Elements;

		Renderer* pRenderer = Renderer::Get();

		if( m_InputLayouts[ShaderID] == nullptr )
		{
			InputLayoutKey* pKey = new InputLayoutKey;
			pKey->ShaderID = ShaderID;
			pKey->InputLayoutID = pRenderer->CreateInputLayout( Elements , ShaderID );
			m_InputLayouts[ShaderID] = pKey;
		}
	}
	else
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> Elements;

		for( unsigned int i = 0; i < m_vElements.size(); i++ )
		{
			D3D11_INPUT_ELEMENT_DESC Desc;
			Desc.SemanticName = m_vElements[i]->m_SemanticName.c_str();
			Desc.SemanticIndex = m_vElements[i]->m_uiSemanticIndex;
			Desc.Format = m_vElements[i]->m_Format;
			Desc.InputSlot = m_vElements[i]->m_uiInputSlot;
			Desc.AlignedByteOffset = m_vElements[i]->m_uiAlignedByteOffset;
			Desc.InputSlotClass = m_vElements[i]->m_InputSlotClass;
			Desc.InstanceDataStepRate = m_vElements[i]->m_uiInstanceDataStepRate;

			Elements.push_back( Desc );
		}

		Renderer* pRenderer = Renderer::Get();

		if( m_InputLayouts[ShaderID] == 0 )
		{
			InputLayoutKey* pKey = new InputLayoutKey;
			pKey->ShaderID = ShaderID;
			pKey->InputLayoutID = pRenderer->CreateInputLayout( Elements , ShaderID );
			m_InputLayouts[ShaderID] = pKey;
		}
	}
}

int Geometry::GetPrimitiveCount()
{
	UINT count = 0;
	UINT indices = m_vIndices.size();

	switch( m_PrimitiveTopology )
	{
		case D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED:
			break;
		case D3D11_PRIMITIVE_TOPOLOGY_POINTLIST:
			count = indices; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINELIST:
			count = indices / 2; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
			count = indices - 1; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
			count = indices / 3; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
			count = indices - 2; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
			count = indices / 4; break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
			count = indices - 3; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
			count = indices / 6; break;
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
			count = ( indices - 3 ) / 2; break;
		case D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST:
			count = indices; break;
		case D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST:
			count = indices / 2; break;
		case D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST:
			count = indices / 3; break;
		case D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST:
			count = indices / 4; break;
		case D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST:
			count = indices / 5; break;
		case D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST:
			count = indices / 6; break;
		case D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST:
			count = indices / 7; break;
		case D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST:
			count = indices / 8; break;
		case D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST:
			count = indices / 9; break;
		case D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST:
			count = indices / 10; break;
		case D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST:
			count = indices / 11; break;
		case D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST:
			count = indices / 12; break;
		case D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST:
			count = indices / 13; break;
		case D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST:
			count = indices / 14; break;
		case D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST:
			count = indices / 15; break;
		case D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST:
			count = indices / 16; break;
		case D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST:
			count = indices / 17; break;
		case D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST:
			count = indices / 18; break;
		case D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST:
			count = indices / 19; break;
		case D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST:
			count = indices / 20; break;
		case D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST:
			count = indices / 21; break;
		case D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST:
			count = indices / 22; break;
		case D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST:
			count = indices / 23; break;
		case D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST:
			count = indices / 24; break;
		case D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST:
			count = indices / 25; break;
		case D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST:
			count = indices / 26; break;
		case D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST:
			count = indices / 27; break;
		case D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST:
			count = indices / 28; break;
		case D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST:
			count = indices / 29; break;
		case D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST:
			count = indices / 30; break;
		case D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST:
			count = indices / 31; break;
		case D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST:
			count = indices / 32; break;
	}

	return( count );
}

UINT Geometry::GetIndexCount()
{
	return m_vIndices.size();
}

void Geometry::SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology )
{
	m_PrimitiveTopology = PrimitiveTopology;
}

D3D11_PRIMITIVE_TOPOLOGY Geometry::GetPrimitiveTopology()
{
	return m_PrimitiveTopology;
}
