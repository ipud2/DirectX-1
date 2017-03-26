#include "PCH.h"
#include "FFbxMesh.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "InputAssemblerLayer.h"

bool LoadPosition( FbxMesh* pMesh , FbxVector4* pControlPoints , int iPolygonCount , std::vector<Sand::Vector3f>& PosList )
{
	for ( int i = 0; i < iPolygonCount; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			int iControlPointIndex = pMesh->GetPolygonVertex( i , j );

			FbxVector4 pos = pControlPoints[iControlPointIndex];

			PosList.push_back( Sand::Vector3f( ( float )pos[0] , ( float )pos[1] , ( float )pos[2] ) );
		}
	}

	return true;
}

bool LoadNormal( FbxMesh* pMesh , FbxVector4* pControlPoints , int iPolygonCount , std::vector<Sand::Vector3f>& NormalList )
{
	bool bResult = true;

	// 只使用第一套Normal
	FbxGeometryElementNormal* pNormal = pMesh->GetElementNormal( 0 );

	for ( int i = 0 , vertex_id = 0; i < iPolygonCount; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			if ( pNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex )
			{
				switch ( pNormal->GetReferenceMode() )
				{
					case FbxGeometryElement::eDirect:
					{
						FbxVector4 normal = pNormal->GetDirectArray().GetAt( vertex_id );

						NormalList.push_back( Sand::Vector3f( ( float )normal[0] , ( float )normal[1] , ( float )normal[2] ) );

						break;
					}

					case FbxGeometryElement::eIndexToDirect:
					{
						int id = pNormal->GetIndexArray().GetAt( vertex_id );
						FbxVector4 normal = pNormal->GetDirectArray().GetAt( id );

						NormalList.push_back( Sand::Vector3f( ( float )normal[0] , ( float )normal[1] , ( float )normal[2] ) );

						break;
					}

					default:
						return false;
				}
			}
			else
			{
				return false;
			}

			vertex_id++;
		}
	}

	return bResult;
}

bool LoadTangent( FbxMesh* pMesh , FbxVector4* pControlPoints , int iPolygonCount , std::vector<Sand::Vector3f>& TangentList )
{
	bool bResult = true;

	if ( pMesh->GetElementTangentCount() < 1 )	return false;

	// 只使用第一套Tangent
	FbxGeometryElementTangent* pTangent = pMesh->GetElementTangent( 0 );

	for ( int i = 0 , vertex_id = 0; i < iPolygonCount; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			if ( pTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex )
			{
				switch ( pTangent->GetReferenceMode() )
				{
					case FbxGeometryElement::eDirect:
					{
						FbxVector4 tangent = pTangent->GetDirectArray().GetAt( vertex_id );

						TangentList.push_back( Sand::Vector3f( ( float )tangent[0] , ( float )tangent[1] , ( float )tangent[2] ) );

						break;
					}

					case FbxGeometryElement::eIndexToDirect:
					{
						int id = pTangent->GetIndexArray().GetAt( vertex_id );
						FbxVector4 tangent = pTangent->GetDirectArray().GetAt( id );

						TangentList.push_back( Sand::Vector3f( ( float )tangent[0] , ( float )tangent[1] , ( float )tangent[2]) );

						break;
					}

					default:
						return false;
				}
			}
			else
			{
				return false;
			}

			vertex_id++;
		}
	}

	return bResult;
}

bool LoadUV( FbxMesh* pMesh , FbxVector4* pControlPoints , int iPolygonCount , std::vector<Sand::Vector2f>& UVList )
{
	bool bResult = true;

	if ( pMesh->GetElementUVCount() < 1 )	return false;

	// 只使用第一套UV
	FbxGeometryElementUV* pUV = pMesh->GetElementUV( 0 );

	for ( int i = 0 , vertex_id = 0; i < iPolygonCount; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			if ( pUV->GetMappingMode() == FbxGeometryElement::eByPolygonVertex )
			{
				switch ( pUV->GetReferenceMode() )
				{
					case FbxGeometryElement::eDirect:
					{
						FbxVector4 uv = pUV->GetDirectArray().GetAt( vertex_id );

						UVList.push_back( Sand::Vector2f( ( float )uv[0] , ( float )uv[1] ) );

						break;
					}

					case FbxGeometryElement::eIndexToDirect:
					{
						int id = pUV->GetIndexArray().GetAt( vertex_id );
						FbxVector4 uv = pUV->GetDirectArray().GetAt( id );

						UVList.push_back( Sand::Vector2f( ( float )uv[0] , ( float )uv[1] ) );

						break;
					}

					default:
						return false;
				}
			}
			else
			{
				return false;
			}

			vertex_id++;
		}
	}

	return bResult;
}

Sand::GeometryPtr Sand::ParseMesh( FbxNode* pNode , uint32_t& vertex_layer )
{
	FbxMesh* pMesh = ( FbxMesh* )pNode->GetNodeAttribute();

	FbxVector4* pControlPoints = pMesh->GetControlPoints();
	int iPolygonCount = pMesh->GetPolygonCount();

	std::vector<Vector3f> PosList;
	LoadPosition( pMesh , pControlPoints , iPolygonCount , PosList );
	vertex_layer |= ePos;

	std::vector<Vector3f> NormalList;
	bool bHasNormal = LoadNormal( pMesh , pControlPoints , iPolygonCount , NormalList );
	vertex_layer |= ( bHasNormal ? eNormal : eNull );

	std::vector<Vector3f> TangentList;
	bool bHasTangent = LoadTangent( pMesh , pControlPoints , iPolygonCount , TangentList );
	vertex_layer |= ( bHasTangent ? eTangent : eNull );

	std::vector<Vector2f> UVList;
	bool bHasUV = LoadUV( pMesh , pControlPoints , iPolygonCount , UVList );
	vertex_layer |= ( bHasUV ? eTex0 : eNull );

	GeometryPtr pGeometry = GeometryPtr( new Geometry );

	int iNumVertices = iPolygonCount * 3;

	if ( vertex_layer & ePos )
	{
		if ( PosList.size() != iNumVertices )	return nullptr;

		VertexElement* pPosition = new VertexElement( 3 , iNumVertices );
		pPosition->m_SemanticName = "POSITION";
		pPosition->m_uiSemanticIndex = 0;
		pPosition->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pPosition->m_uiInputSlot = 0;
		pPosition->m_uiAlignedByteOffset = 0;
		pPosition->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pPosition->m_uiInstanceDataStepRate = 0;

		Vector3f* pVertex = pPosition->Get3fTupleDataPtr( 0 );
		for ( int i = 0; i < iNumVertices; i++ ) { pVertex[i] = PosList[i]; }

		pGeometry->AddElement( pPosition );
	}
	
	if ( vertex_layer & eNormal )
	{
		if ( NormalList.size() != iNumVertices )	return nullptr;

		VertexElement* pNormals = new VertexElement( 3 , iNumVertices );
		pNormals->m_SemanticName = "NORMAL";
		pNormals->m_uiSemanticIndex = 0;
		pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pNormals->m_uiInputSlot = 0;
		pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pNormals->m_uiInstanceDataStepRate = 0;

		Vector3f* pNormal = pNormals->Get3fTupleDataPtr( 0 );
		for ( int i = 0; i < iNumVertices; i++ ) { pNormal[i] = NormalList[i]; }

		pGeometry->AddElement( pNormals );
	}

	if ( vertex_layer & eTangent )
	{
		if ( TangentList.size() != iNumVertices )	return nullptr;

		VertexElement* pTangents = new VertexElement( 3 , iNumVertices );
		pTangents->m_SemanticName = "TANGENT";
		pTangents->m_uiSemanticIndex = 0;
		pTangents->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pTangents->m_uiInputSlot = 0;
		pTangents->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		pTangents->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pTangents->m_uiInstanceDataStepRate = 0;

		Vector3f* pTangent = pTangents->Get3fTupleDataPtr( 0 );
		for ( int i = 0; i < iNumVertices; i++ ) { pTangent[i] = TangentList[i]; }

		pGeometry->AddElement( pTangents );
	}

	if ( vertex_layer & eTex0 )
	{
		if ( UVList.size() != iNumVertices )	return nullptr;

		VertexElement* pTexCoords = new VertexElement( 2 , iNumVertices );
		pTexCoords->m_SemanticName = "TEXCOORD";
		pTexCoords->m_uiSemanticIndex = 0;
		pTexCoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
		pTexCoords->m_uiInputSlot = 0;
		pTexCoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		pTexCoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pTexCoords->m_uiInstanceDataStepRate = 0;

		Vector2f* pTex = pTexCoords->Get2fTupleDataPtr( 0 );
		for ( int i = 0; i < iNumVertices; i++ ) { pTex[i] = UVList[i]; }

		pGeometry->AddElement( pTexCoords );
	}

	for ( int i = 0; i < iNumVertices; i += 3 )
	{
		pGeometry->AddFace( i , i + 1 , i + 2 );
	}

	pGeometry->AddGroupInfo( 0 , iNumVertices );

	return pGeometry;
}