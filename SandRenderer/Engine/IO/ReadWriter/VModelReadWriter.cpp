#include "PCH.h"
#include "VModelReadWriter.h"
#include "Engine/IO/FileInStream.h"
#include "Engine/IO/FileOutStream.h"
#include "Engine/Animation/VScene.h"
#include "Engine/Animation/VMaterial.h"
#include "Engine/Animation/VMesh.h"
#include "Vector3f.h"

#define VMODEL_MATERIAL		'VMMC'
#define VMODEL_MESH			'VMME'
#define VMODEL_POLYGON		'VMPC'

void Sand::VModelReader( const char* filename )
{
	FileInStream fin( filename );
	
	uint32 iChunkID = 0;
	while ( fin.OpenChunk( iChunkID ) )
	{
		switch ( iChunkID )
		{
			case VMODEL_MATERIAL:
			{
				int iMaterialCount = -1;
				fin.ReadInt( iMaterialCount );

				for ( int32 i = 0; i < iMaterialCount; i++ )
				{
					
				}
				break;
			}

			case VMODEL_MESH:
			{
				break;
			}

			case VMODEL_POLYGON:
			{
				break;
			}
		
			default:
				break;
		}

		fin.CloseChunk();
	}

	fin.Close();
}

void Sand::VModelWriter( const char* filename , VScene& scene )
{
	FileOutStream fout( filename );

	if ( fout.StartChunk( VMODEL_MATERIAL ) )
	{
		fout.WriteInt( scene.GetMaterialCount() );
		for ( int i = 0; i < scene.GetMaterialCount(); i++ )
		{
			VMaterial& material = scene.GetMaterial( i );

			Vector3f Ambient = material.GetAmbient();
			fout.WriteVector( Ambient );

			Vector3f Emissive = material.GetEmissive();
			fout.WriteVector( Emissive );

			Vector3f Diffuse = material.GetDiffuse();
			fout.WriteVector( Diffuse );

			for ( int i = 0; i < EMT_MAPNUM; i++ )
			{
				const char* str = material.GetMapName( EMapType( i ) );
				fout.WriteString( str );
			}
		}
		fout.EndChunk();
	}

	if ( fout.StartChunk( VMODEL_MESH ) )
	{
		int iMeshCount = scene.GetMeshCount();
		fout.WriteInt( iMeshCount );

		for ( int iMeshIndex = 0; iMeshIndex < iMeshCount; iMeshIndex++ )
		{
			VMesh* pMesh = scene.GetMesh( iMeshIndex );
			int iVertexCount		= ( int )pMesh->GetVertexList().size();
			int iTriangleCount		= ( int )pMesh->GetTriangleList().size();
			EInputMask eInputMask	= pMesh->GetInputMask();

			fout.WriteInt( iVertexCount );
			fout.WriteInt( iTriangleCount );
			fout.WriteInt( eInputMask );

			std::vector<VVertex>& vertex_list = pMesh->GetVertexList();
			for ( int iVertexIndex = 0; iVertexIndex < iVertexCount; iVertexIndex++ )
			{
				VVertex vertex = vertex_list[iVertexIndex];

				if ( eInputMask & EIM_POSITION )
				{
					Vector3f v;
					vertex.GetPosition( v[0] , v[1] , v[2] );
					fout.WriteVector( v );
				}

				if ( eInputMask & EIM_NORMAL )
				{
					Vector3f v;
					vertex.GetNormal( v[0] , v[1] , v[2] );
					fout.WriteVector( v );
				}

				if ( eInputMask & EIM_TANGENT )
				{
					Vector3f v;
					vertex.GetTangent( v[0] , v[1] , v[2] );
					fout.WriteVector( v );
				}

				if ( eInputMask & EIM_COLOR )
				{
					Vector3f v;
					vertex.GetColor( v[0] , v[1] , v[2] );
					fout.WriteVector( v );
				}
				
				if ( eInputMask & EIM_TEXCOORD0 )
				{
					Vector2f v;
					vertex.GetTexcoord( v[0] , v[1] );
					fout.WriteVector( v );
				}

				if ( eInputMask & EIM_WEIGHT )
				{
					int iWeightCount = vertex.GetWeightCount();
					fout.WriteInt( iWeightCount );

					for ( int iWeightIndex = 0; iWeightIndex < iWeightCount; iWeightIndex++ )
					{
						int32 iJointIndex = -1;
						float fWeight = 0.0f;
						vertex.GetWeight( iWeightIndex , iJointIndex , fWeight );
						fout.WriteInt( iJointIndex );
						fout.WriteFloat( fWeight );
					}
				}
			}

			std::vector<VTriangle>& triangle_list = pMesh->GetTriangleList();
			for ( int iPolygonIndex = 0; iPolygonIndex < iTriangleCount; iPolygonIndex++ )
			{
				VTriangle triangle = triangle_list[iPolygonIndex];

				fout.WriteInt( triangle.GetMatrixIndex() );
				fout.WriteInt( triangle[0] );
				fout.WriteInt( triangle[1] );
				fout.WriteInt( triangle[2] );
			}
		}
		fout.EndChunk();
	}
}