#include "PCH.h"
#include "FbxImporterProcesser.h"
#include "VScene.h"
#include "VMesh.h"
#include "VVertex.h"
#include "Geometry.h"
#include "SMath.h"

using namespace Sand;

void FbxImporterProcesser::Process( VScene& scene )
{
	int iNumMesh = scene.GetMeshCount();

	int iTotalVertexCount = 0;
	for ( int i = 0; i < iNumMesh; i++ )
	{
		VMesh* mesh = scene.GetMesh( i );
		iTotalVertexCount += ( int )mesh->GetVertexList().size();
	}

	EInputMask inputMask = scene.GetMesh( 0 )->GetInputMask();

	// fill vertex buffer and index buffer
	// first create geometry object

	VertexElement* PosVertexElement = new VertexElement( 3 , iTotalVertexCount );
	PosVertexElement->m_SemanticName = VertexElement::PositionSemantic;
	PosVertexElement->m_uiSemanticIndex = 0;
	PosVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	PosVertexElement->m_uiInputSlot = 0;
	PosVertexElement->m_uiAlignedByteOffset = 0;
	PosVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	PosVertexElement->m_uiInstanceDataStepRate = 0;

	if ( inputMask & EIM_POSITION )
	{
		Vector3f* Pos = ( Vector3f* )( ( *PosVertexElement )[0] );

		for ( int iMeshIndex = 0 , iVertexOffset = 0; iMeshIndex < iNumMesh; iMeshIndex++ )
		{
			VMesh* pMesh						= scene.GetMesh( iMeshIndex );
			std::vector<VVertex>& vertex_list	= pMesh->GetVertexList();
			int iVertexCount					= ( int )vertex_list.size();
			Matrix4f& LocalMatrix				= pMesh->GetTransform();

			for ( int iVertexIndex = 0; iVertexIndex < iVertexCount; iVertexIndex++ )
			{
				vertex_list[iVertexIndex].GetPosition( Pos[iVertexOffset + iVertexIndex].x , Pos[iVertexOffset + iVertexIndex].y , Pos[iVertexOffset + iVertexIndex].z );
				Vector4f v( Pos[iVertexOffset + iVertexIndex].x , Pos[iVertexOffset + iVertexIndex].y , Pos[iVertexOffset + iVertexIndex].z , 1.0f );
				v = LocalMatrix * v;
				Pos[iVertexOffset + iVertexIndex].x = v[0];	Pos[iVertexOffset + iVertexIndex].y = v[1];	Pos[iVertexOffset + iVertexIndex].z = v[2];
			}

			iVertexOffset += iVertexCount;
		}
		m_pGeometry->AddElement( PosVertexElement );
	}

	VertexElement* NormalVertexElement = new VertexElement( 3 , iTotalVertexCount );
	NormalVertexElement->m_SemanticName = VertexElement::NormalSemantic;
	NormalVertexElement->m_uiSemanticIndex = 0;
	NormalVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	NormalVertexElement->m_uiInputSlot = 0;
	NormalVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	NormalVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	NormalVertexElement->m_uiInstanceDataStepRate = 0;

	if ( inputMask & EIM_NORMAL )
	{
		Vector3f* Nor = ( Vector3f* )( ( *NormalVertexElement )[0] );

		for ( int iMeshIndex = 0 , iVertexOffset = 0; iMeshIndex < iNumMesh; iMeshIndex++ )
		{
			VMesh* pMesh						= scene.GetMesh( iMeshIndex );
			std::vector<VVertex>& vertex_list	= pMesh->GetVertexList();
			int iVertexCount					= ( int )vertex_list.size();

			for ( int iVertexIndex = 0; iVertexIndex < iVertexCount; iVertexIndex++ )
			{
				vertex_list[iVertexIndex].GetNormal( Nor[iVertexOffset + iVertexIndex].x , Nor[iVertexOffset + iVertexIndex].y , Nor[iVertexOffset + iVertexIndex].z );
				Nor[iVertexOffset + iVertexIndex] = MultipyNormal( Nor[iVertexOffset + iVertexIndex] , pMesh->GetTransform() );
			}

			iVertexOffset += iVertexCount;
		}
		m_pGeometry->AddElement( NormalVertexElement );
	}

	VertexElement* TexcoordVertexElement = new VertexElement( 2 , iTotalVertexCount );
	TexcoordVertexElement->m_SemanticName = VertexElement::TexCoordSemantic;
	TexcoordVertexElement->m_uiSemanticIndex = 0;
	TexcoordVertexElement->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	TexcoordVertexElement->m_uiInputSlot = 0;
	TexcoordVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	TexcoordVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	TexcoordVertexElement->m_uiInputSlot = 0;

	if ( inputMask & EIM_TEXCOORD0 )
	{
		Vector2f* Texcoprd = ( Vector2f* )( ( *TexcoordVertexElement )[0] );

		for ( int iMeshIndex = 0 , iVertexOffset = 0; iMeshIndex < iNumMesh; iMeshIndex++ )
		{
			VMesh* pMesh						= scene.GetMesh( iMeshIndex );
			std::vector<VVertex>& vertex_list	= pMesh->GetVertexList();
			int iVertexCount					= ( int )vertex_list.size();

			for ( int iVertexIndex = 0; iVertexIndex < iVertexCount; iVertexIndex++ )
			{
				vertex_list[iVertexIndex].GetTexcoord( Texcoprd[iVertexOffset + iVertexIndex].x , Texcoprd[iVertexOffset + iVertexIndex].y );
			}

			iVertexOffset += iVertexCount;
		}
		m_pGeometry->AddElement( TexcoordVertexElement );
	}

	VertexElement* TanVertexElement = new VertexElement( 3 , iTotalVertexCount );
	TanVertexElement->m_SemanticName = VertexElement::TangentSemantic;
	TanVertexElement->m_uiSemanticIndex = 0;
	TanVertexElement->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	TanVertexElement->m_uiInputSlot = 0;
	TanVertexElement->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	TanVertexElement->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	TanVertexElement->m_uiInputSlot = 0;

	if ( inputMask & EIM_TANGENT )
	{
		Vector3f* Tan = ( Vector3f* )( ( *TanVertexElement )[0] );
		for ( int iMeshIndex = 0 , iVertexOffset = 0; iMeshIndex < iNumMesh; iMeshIndex++ )
		{
			VMesh* pMesh						= scene.GetMesh( iMeshIndex );
			std::vector<VVertex>& vertex_list	= pMesh->GetVertexList();
			int iVertexCount					= ( int )vertex_list.size();

			for ( int iVertexIndex = 0; iVertexIndex < iVertexCount; iVertexIndex++ )
			{
				vertex_list[iVertexIndex].GetTangent( Tan[iVertexOffset + iVertexIndex].x , Tan[iVertexOffset + iVertexIndex].y , Tan[iVertexOffset + iVertexIndex].z );
			}

			iVertexOffset += iVertexCount;
		}
		m_pGeometry->AddElement( TanVertexElement );
	}

	for ( int iMeshIndex = 0 , iVertexOffset = 0 , iTriIndexOffset = 0; iMeshIndex < iNumMesh; iMeshIndex++ )
	{
		VMesh* pMesh						= scene.GetMesh( iMeshIndex );
		std::vector<VTriangle>& tri_list	= pMesh->GetTriangleList();
		int iVertexCount					= pMesh->GetVertexList().size();
		int iTriCount						= ( int )tri_list.size();

		for ( int iTriIndex = 0; iTriIndex < iTriCount; iTriIndex++ )
		{
			m_pGeometry->AddFace( tri_list[iTriIndex][0] , tri_list[iTriIndex][1] , tri_list[iTriIndex][2] );
		}

		m_pGeometry->AddGroupInfo( iTriIndexOffset , iTriCount * 3 , iVertexOffset );

		iVertexOffset += iVertexCount;

		iTriIndexOffset += iTriCount * 3;
	}
}

void FbxImporterProcesser::SetGeometry( Geometry* pGeometry )
{
	m_pGeometry = pGeometry;
}

Geometry* FbxImporterProcesser::GetGeometry()
{
	return m_pGeometry;
}