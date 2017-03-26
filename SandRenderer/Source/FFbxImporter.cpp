#include "PCH.h"
#include "FFbxImporter.h"
#include "Log.h"
#include "Engine/Animation/VSkeleton.h"
#include "Engine/Animation/VJoint.h"
#include "Engine/Animation/VSkeletonManager.h"
#include "Engine/Animation/VJointManager.h"
#include "Engine/Animation/VMesh.h"
#include "fbxsdk/scene/geometry/fbxlayer.h"
#include "Engine/Animation/VScene.h"
#include "Engine/Animation/VVertex.h"
#include "SMath.h"
#include "Engine/Animation/VMaterial.h"

using namespace Sand;

FFbxImporter::FFbxImporter()
	: m_pSdkManager( nullptr )
	, m_pFbxScene( nullptr )
{
	m_pSdkManager = FbxManager::Create();
	if ( !m_pSdkManager )
	{
		Log::Get().Error( TEXT("Error : Unable to create Fbx Manager") );
	}

	FbxIOSettings* ios = FbxIOSettings::Create( m_pSdkManager , IOSROOT );
	m_pSdkManager->SetIOSettings( ios );

	m_LinkMap.clear();
}

FFbxImporter::~FFbxImporter()
{
	CleanUp();
}

void FFbxImporter::CleanUp()
{
	if ( m_pSdkManager )
	{
		m_pSdkManager->Destroy();
	}

	m_pSdkManager = nullptr;
}

void FFbxImporter::SetScene( VScene& scene )
{
	m_pScene = &scene;
}

bool FFbxImporter::Load( const char* szFilename )
{
	if ( !OpenFile( szFilename ) )	return false;

	ReadSkeleton( m_pFbxScene->GetRootNode() );

	ConvertToSkeleton();

	ReadMeshInfo();

	return true;
}

bool FFbxImporter::OpenFile( const char* Filename )
{
	int SDKMajor , SDKMinor , SDKRevision;
	int FileMajor , FileMinor , FileRevision;

	FbxManager::GetFileFormatVersion( SDKMajor , SDKMinor , SDKRevision );

	m_pFbxScene = FbxScene::Create( m_pSdkManager , "My Scene" );
	if ( !m_pFbxScene )
	{
		return false;
	}

	FbxImporter* pImporter = FbxImporter::Create( m_pSdkManager , "" );

	const bool bImporterStatus = pImporter->Initialize( Filename , -1 , m_pSdkManager->GetIOSettings() );
	pImporter->GetFileVersion( FileMajor , FileMinor , FileRevision );

	if ( !bImporterStatus )
	{
		return false;
	}

	if ( pImporter->IsFBX() )
	{
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_MATERIAL , true );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_TEXTURE , true );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_LINK , true );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_SHAPE , true );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_GOBO , true );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_ANIMATION , true );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_GLOBAL_SETTINGS , true );
	}

	bool bStatus = pImporter->Import( m_pFbxScene );
	if ( bStatus == false && pImporter->GetStatus().GetCode() == FbxStatus::ePasswordError )
	{
		std::cout << "Please Enter password : ";

		char Password[1024];
		Password[0] = '\0';

		FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
		std::cin >> Password;
		FBXSDK_CRT_SECURE_NO_WARNING_END

		FbxString lString( Password );
		m_pSdkManager->GetIOSettings()->SetStringProp( IMP_FBX_PASSWORD , lString );
		m_pSdkManager->GetIOSettings()->SetBoolProp( IMP_FBX_PASSWORD_ENABLE , true );

		bStatus = pImporter->Import( m_pFbxScene );

		if ( bStatus == false && pImporter->GetStatus().GetCode() == FbxStatus::ePasswordError )
		{
			std::cout << std::endl << "Password is wrong , import aborted." << std::endl;
		}
	}

	pImporter->Destroy();

	FbxAxisSystem axis( FbxAxisSystem::MayaYUp );
	axis.ConvertScene( m_pFbxScene );

	return bStatus;
}

void FFbxImporter::ReadMaterial( FbxNode* pNode , std::map<int , int>& vMaterialMap )
{
	int iMaterialCount = pNode->GetMaterialCount();

	std::vector<int> vMaterialList;
	for ( int iMaterialIndex = 0; iMaterialIndex < iMaterialCount; iMaterialIndex++ )
	{
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial( iMaterialIndex );
		if ( pMaterial )
		{
			vMaterialList.push_back( iMaterialIndex );
		}
	}

	for ( int iSurfaceMaterialIndex = 0 , n = ( int )vMaterialList.size(); iSurfaceMaterialIndex < n; iSurfaceMaterialIndex++ )
	{
		FbxSurfaceMaterial* pFbxMaterial = pNode->GetMaterial( vMaterialList[iSurfaceMaterialIndex] );

		if ( vMaterialMap.find( vMaterialList[iSurfaceMaterialIndex] ) == vMaterialMap.end() )
		{
			int iMaterialID = ReadSurfaceMaterial( pFbxMaterial );

			vMaterialMap[vMaterialList[iSurfaceMaterialIndex]] = iMaterialID;
		}
	}
}

int FFbxImporter::ReadSurfaceMaterial( FbxSurfaceMaterial* pFbxMaterial )
{
	VMaterial& material = m_pScene->CreateMaterial();

	if ( pFbxMaterial->GetClassId().Is( FbxSurfacePhong::ClassId ) )
	{
		FbxPropertyT<FbxDouble3> lFbxDouble3;
		
		lFbxDouble3 = ( ( FbxSurfacePhong* )pFbxMaterial )->Ambient;
		material.SetAmbient( ( float )lFbxDouble3.Get()[0] , ( float )lFbxDouble3.Get()[1] , ( float )lFbxDouble3.Get()[2] );

		lFbxDouble3 = ( ( FbxSurfacePhong* )pFbxMaterial )->Emissive;
		material.SetEmissive( ( float )lFbxDouble3.Get()[0] , ( float )lFbxDouble3.Get()[1] , ( float )lFbxDouble3.Get()[2] );

		lFbxDouble3 = ( ( FbxSurfacePhong* )pFbxMaterial )->Diffuse;
		material.SetDiffuse( ( float )lFbxDouble3.Get()[0] , ( float )lFbxDouble3.Get()[1] , ( float )lFbxDouble3.Get()[2] );
	}
	else if ( pFbxMaterial->GetClassId().Is( FbxSurfaceLambert::ClassId ) )
	{
		FbxPropertyT<FbxDouble3> lFbxDouble3;

		lFbxDouble3 = ( ( FbxSurfaceLambert* )pFbxMaterial )->Ambient;
		material.SetAmbient( ( float )lFbxDouble3.Get()[0] , ( float )lFbxDouble3.Get()[1] , ( float )lFbxDouble3.Get()[2] );

		lFbxDouble3 = ( ( FbxSurfaceLambert* )pFbxMaterial )->Emissive;
		material.SetEmissive( ( float )lFbxDouble3.Get()[0] , ( float )lFbxDouble3.Get()[1] , ( float )lFbxDouble3.Get()[2] );

		lFbxDouble3 = ( ( FbxSurfaceLambert* )pFbxMaterial )->Diffuse;
		material.SetDiffuse( ( float )lFbxDouble3.Get()[0] , ( float )lFbxDouble3.Get()[1] , ( float )lFbxDouble3.Get()[2] );
	}

	int iLayerTextureIndex;
	FBXSDK_FOR_EACH_TEXTURE( iLayerTextureIndex )
	{
		FbxProperty lProperty = pFbxMaterial->FindProperty( FbxLayerElement::sTextureChannelNames[iLayerTextureIndex] );
		if ( lProperty.IsValid() )
		{
			int iTextureCount = lProperty.GetSrcObjectCount<FbxTexture>();

			for ( int iTextureIndex = 0; iTextureIndex < iTextureCount; iTextureIndex++ )
			{
				FbxLayeredTexture* pLayeredTexture = lProperty.GetSrcObject<FbxLayeredTexture>();
				if ( pLayeredTexture )
				{
					int iNbTextureCount = pLayeredTexture->GetSrcObjectCount<FbxTexture>();
					for ( int k = 0; k < iNbTextureCount; k++ )
					{
						FbxTexture* pTexture = pLayeredTexture->GetSrcObject<FbxTexture>();
						if ( pTexture )
						{

						}
					}
				}
				else
				{
					FbxTexture* pTexture = lProperty.GetSrcObject<FbxTexture>();
					if ( pTexture )
					{
						FbxFileTexture* pFileTexture = FbxCast<FbxFileTexture>( pTexture );
						const char* szRelativeName = pFileTexture->GetRelativeFileName();
						
						switch ( FbxGeometryElement::eTextureDiffuse + iLayerTextureIndex )
						{
							case FbxGeometryElement::eTextureDiffuse:
							{
								material.SetMapName( szRelativeName , EMT_DIFFUSE );
								break;
							}

							case FbxGeometryElement::eTextureBump:
							case FbxGeometryElement::eTextureNormalMap:
							{
								material.SetMapName( szRelativeName , EMT_NORMAL );
								break;
							}

							case FbxGeometryElement::eTextureEmissive:
							{
								material.SetMapName( szRelativeName , EMT_EMISSIVE );
								break;
							}

							case FbxGeometryElement::eTextureSpecular:
							{
								material.SetMapName( szRelativeName , EMT_SPECULAR );
								break;
							}

							case FbxGeometryElement::eTextureShininess:
							{
								material.SetMapName( szRelativeName , EMT_ROUGHNESS );
								break;
							}

							default:
								break;
						}
					}
				}
			}
		}
	}

	return m_pScene->GetMaterialCount() - 1;
}

int FFbxImporter::ReadTriangleMaterialIndex( FbxMesh* pMesh , int iPolygonIndex , int iControIndex , std::map<int , int>& vMaterialMap )
{
	for ( auto iter : vMaterialMap )
	{
		int iFbxMaterialIndex = iter.first;
		int iMaterialIndex = iter.second;

		FbxGeometryElementMaterial* pElementMaterial = pMesh->GetElementMaterial( iFbxMaterialIndex );

		switch ( pElementMaterial->GetMappingMode() )
		{
			case FbxGeometryElement::eByControlPoint:
			{
				switch ( pElementMaterial->GetReferenceMode() )
				{
					case FbxGeometryElement::eIndexToDirect:
					{
						return pElementMaterial->GetIndexArray().GetAt( iControIndex );
					}

					default:
					{
						break;
					}
				}
				break;
			}

			case FbxGeometryElement::eByPolygon:
			{
				switch ( pElementMaterial->GetReferenceMode() )
				{
					case FbxGeometryElement::eIndexToDirect:
					{
						return pElementMaterial->GetIndexArray().GetAt( iPolygonIndex );
					}

					default:
					{
						break;
					}
				}
				break;
			}

			case FbxGeometryElement::eByPolygonVertex:
			{
				switch ( pElementMaterial->GetReferenceMode() )
				{
					case FbxGeometryElement::eIndexToDirect:
					{
						// 保持三角形的三个顶点材质索引一致
						return pElementMaterial->GetIndexArray().GetAt( iPolygonIndex * 3 + 0 );
					}

					default:
					{
						break;
					}
				}
				break;
			}

			case FbxGeometryElement::eAllSame:
			{
				switch ( pElementMaterial->GetReferenceMode() )
				{
					case FbxGeometryElement::eIndexToDirect:
					{
						return pElementMaterial->GetIndexArray().GetAt( 0 );
					}

					default:
					{
						break;
					}
				}
				break;
			}

			default:
			{
				break;
			}
		}
	}

	return -1;
}

bool FFbxImporter::ReadVertices( FbxMesh* pMesh , std::vector<VVertex>& vVertexList , std::vector<VTriangle>& vTriangleList , EInputMask eInputMask , std::map<int , int>& vMaterialMap )
{
	VVertex vertex( eInputMask );

	int iPolygonCount			= pMesh->GetPolygonCount();
	FbxVector4* pControlPoints	= pMesh->GetControlPoints();

	int32 iVertexNum = pMesh->GetControlPointsCount();

	m_vVertexOffset.push_back( ( int )m_vBaseShape.size() );

	for ( int i = 0; i < iVertexNum; i++ )
	{
		FbxVector4 ControlPointPos = pControlPoints[i];

		vertex.SetPosition( ( float )ControlPointPos[0] , ( float )ControlPointPos[1] , ( float )ControlPointPos[2] );

		vVertexList.push_back( vertex );

		m_vBaseShape.push_back( Vector3f( ( float )ControlPointPos[0] , ( float )ControlPointPos[1] , ( float )ControlPointPos[2] ) );
	}

	for ( int iPolygonIndex = 0; iPolygonIndex < iPolygonCount; iPolygonIndex++ )
	{
		vTriangleList.push_back( VTriangle() );
		VTriangle& triangle = vTriangleList.back();
		for ( int iVertexIndex = 0; iVertexIndex < 3; iVertexIndex++ )
		{
			int iControlPointIndex = pMesh->GetPolygonVertex( iPolygonIndex , iVertexIndex );

			triangle[iVertexIndex] = iControlPointIndex;
			triangle.SetMaterialIndex( ReadTriangleMaterialIndex( pMesh , iPolygonIndex , iControlPointIndex , vMaterialMap ) );
		}
	}

	return true;
}

bool FFbxImporter::ReadNormals( FbxMesh* pMesh , std::vector<VVertex>& vVertexList )
{
	int iPolygonCount = pMesh->GetPolygonCount();

	FbxGeometryElementNormal* pElementNormal = pMesh->GetElementNormal( 0 );

	for ( int iPolygonIndex = 0; iPolygonIndex < iPolygonCount; iPolygonIndex++ )
	{
		for ( int iVertexIndex = 0; iVertexIndex < 3; iVertexIndex++ )
		{
			FbxVector4 normal;
			bool bSuccess = pMesh->GetPolygonVertexNormal( iPolygonIndex , iVertexIndex , normal );

			int iControlPointIndex = pMesh->GetPolygonVertex( iPolygonIndex , iVertexIndex );

			vVertexList[iControlPointIndex].SetNormal( ( float )normal[0] , ( float )normal[1] , ( float )normal[2] );
		}
	}

	return true;
}

bool FFbxImporter::ReadTangents( FbxMesh* pMesh , std::vector<VVertex>& vVertexList )
{
	FbxGeometryElementTangent* pElementTangent = pMesh->GetElementTangent( 0 );

	FbxVector4 tangent;

	for ( int iPolygonIndex = 0; iPolygonIndex < pMesh->GetPolygonCount(); iPolygonIndex++ )
	{
		for ( int iVertexIndex = 0; iVertexIndex < 3; iVertexIndex++ )
		{
			switch ( pElementTangent->GetMappingMode() )
			{
				case FbxGeometryElement::eByPolygonVertex:
				{
					switch ( pElementTangent->GetReferenceMode() )
					{
						case FbxGeometryElement::eDirect:
						{
							tangent = pElementTangent->GetDirectArray().GetAt( iPolygonIndex * 3 + iVertexIndex );
							break;
						}

						case FbxGeometryElement::eIndexToDirect:
						{
							int id = pElementTangent->GetIndexArray().GetAt( iPolygonIndex );
							tangent = pElementTangent->GetDirectArray().GetAt( id );
							break;
						}

						default:
							break;
					}
					break;
				}

				case FbxGeometryElement::eAllSame:
				{
					switch ( pElementTangent->GetReferenceMode() )
					{
						case FbxGeometryElement::eDirect:
						{
							tangent = pElementTangent->GetDirectArray().GetAt( 0 );
							break;
						}

						case FbxGeometryElement::eIndexToDirect:
						{
							int id = pElementTangent->GetIndexArray().GetAt( 0 );
							tangent = pElementTangent->GetDirectArray().GetAt( id );
							break;
						}

						default:
							break;
					}
					break;
				}
			}

			int iControlPointIndex = pMesh->GetPolygonVertex( iPolygonIndex , iVertexIndex );

			vVertexList[iControlPointIndex].SetTangent( ( float )tangent[0] , ( float )tangent[1] , ( float )tangent[2] );
		}
	}

	return true;
}

bool FFbxImporter::ReadUVs( FbxMesh* pMesh , std::vector<VVertex>& vVertexList )
{
	FbxGeometryElementUV* pElementUV = pMesh->GetElementUV( 0 );

	int iPolygonCount = pMesh->GetPolygonCount();

	for ( int iPolygonIndex = 0; iPolygonIndex < iPolygonCount; iPolygonIndex++ )
	{
		for ( int iVertexIndex = 0; iVertexIndex < 3; iVertexIndex++ )
		{
			int iControlPointIndex = pMesh->GetPolygonVertex( iPolygonIndex , iVertexIndex );

			FbxVector2 uv;
			bool bUnMapped = false;
			pMesh->GetPolygonVertexUV( iPolygonIndex , iVertexIndex , pElementUV->GetName() , uv , bUnMapped );

			if ( !bUnMapped )
			{
				vVertexList[iControlPointIndex].SetTexcoord( 0 , ( float )uv[0] , ( float )uv[1] );
			}
		}
	}
	
	return true;
}

void FFbxImporter::ReadInputMask( FbxMesh* pMesh , EInputMask& InputMask )
{
	InputMask = EInputMask( EIM_POSITION | InputMask );

	int iElementNormalCount = pMesh->GetElementNormalCount();
	InputMask = iElementNormalCount > 0 ? EInputMask( EIM_NORMAL | InputMask ) : InputMask;

	int iElementTangentCount = pMesh->GetElementTangentCount();
	InputMask = iElementTangentCount > 0 ? EInputMask( EIM_TANGENT | InputMask ) : InputMask;

	int iElementUVCount = pMesh->GetElementUVCount();
	InputMask = iElementUVCount > 0 ? EInputMask( EIM_TEXCOORD0 | InputMask ) : InputMask;

	int iSkinCount = pMesh->GetDeformerCount( FbxDeformer::eSkin );
	if ( iSkinCount )	InputMask = EInputMask( EIM_WEIGHT | InputMask );
}

void FFbxImporter::ReadMeshInfo()
{
	std::vector<FbxNode*> MeshNodeArray;

	FbxNode* pRootNode = m_pFbxScene->GetRootNode();

	for ( int i = 0; i < pRootNode->GetChildCount(); i++ )
	{
		RecursiveReadMeshNode( pRootNode->GetChild( i ) , MeshNodeArray );
	}

	// Triangluate
	std::vector<FbxMesh*> TriMeshList;
	for ( auto& iter = MeshNodeArray.begin(); iter != MeshNodeArray.end(); iter++ )
	{
		FbxMesh* pTriMesh = ( FbxMesh* )( *iter )->GetNodeAttribute();
		if ( Triangluate( pTriMesh ) )
		{
			TriMeshList.push_back( pTriMesh );
		}
	}

	for ( auto& iter = TriMeshList.begin(); iter != TriMeshList.end(); iter++ )
	{
		EInputMask eInputMask = EIM_NONE;
		ReadInputMask( *iter , eInputMask );

		int iMeshIndex = m_pScene->CreateMesh( eInputMask );
		VMesh* pMesh = m_pScene->GetMesh( iMeshIndex );
		if ( pMesh )
		{
			std::vector<VVertex>& vertex_list = pMesh->GetVertexList();
			std::vector<VTriangle>& triangle_list = pMesh->GetTriangleList();

			FbxNode* pMeshNode				= ( *iter )->GetNode();
			FbxAMatrix GeometricTransform	= FbxAMatrix( pMeshNode->GetGeometricTranslation( FbxNode::eSourcePivot ) , pMeshNode->GetGeometricRotation( FbxNode::eSourcePivot ) , pMeshNode->GetGeometricScaling( FbxNode::eSourcePivot ) );
			FbxAMatrix& GlobalTransform		= pMeshNode->EvaluateGlobalTransform();
			Matrix4f GeometricTranRowMajor	= converter.ConvertMatrix( GeometricTransform );
			Matrix4f GlobalTranRowMajor		= converter.ConvertMatrix( GlobalTransform );
			pMesh->SetTransform( GeometricTranRowMajor * GlobalTranRowMajor );
			pMesh->SetName( pMeshNode->GetName() );
			m_vLocalTransform.push_back( pMesh->GetTransform() );

			std::map<int , int> vMaterialMap;
			ReadMaterial( pMeshNode , vMaterialMap );

			// Read Vertices
			if ( eInputMask & EIM_POSITION )
			{
				int iVertexNum = 0;
				ReadVertices( *iter , vertex_list , triangle_list , eInputMask , vMaterialMap );
			}

			// Read Normal
			if ( eInputMask & EIM_NORMAL )
			{
				ReadNormals( *iter , vertex_list );
			}

			// Read Tangent
			if ( eInputMask & EIM_TANGENT )
			{
				ReadTangents( *iter , vertex_list );
			}

			// Read Texcoord
			if ( eInputMask & EIM_TEXCOORD0 )
			{
				ReadUVs( *iter , vertex_list );
			}
		}
	}

	for( int i = 0; i < ( int )TriMeshList.size(); i++ )
	{
		FbxMesh* pFbxMesh = TriMeshList[i];

		int iSkinCount = pFbxMesh->GetDeformerCount( FbxDeformer::eSkin );

		for ( int iSkinIndex = 0; iSkinIndex < iSkinCount; iSkinIndex++ )
		{
			FbxSkin* pSkin = ( FbxSkin* )pFbxMesh->GetDeformer( iSkinIndex , FbxDeformer::eSkin );

			int iClusterCount = pSkin->GetClusterCount();
			for ( int iClusterIndex = 0; iClusterIndex < iClusterCount; iClusterIndex++ )
			{
				FbxCluster* pCluster = pSkin->GetCluster( iClusterIndex );

				int iBoneIndex = FindBoneIndex( pCluster->GetLink() );

				int*	pClusterControlPointIndices	= pCluster->GetControlPointIndices();
				double* pClusterWeights				= pCluster->GetControlPointWeights();
				int		iClusterControlPointCount	= pCluster->GetControlPointIndicesCount();

				for ( int iClusterControlPointIndex = 0; iClusterControlPointIndex < iClusterControlPointCount; iClusterControlPointIndex++ )
				{
					int		iControlPointIndex	= pClusterControlPointIndices[iClusterControlPointIndex];
					float	Weight				= ( float )pClusterWeights[iClusterControlPointIndex];

					std::vector<VVertex>& vertex_list = m_pScene->GetMesh( i )->GetVertexList();
					if ( iBoneIndex != -1 )
					{
						vertex_list[iControlPointIndex].AddWeight( iBoneIndex , Weight );
					}
				}
			}

		}
	}

	ReadMorph( TriMeshList );
}

void FFbxImporter::ReadMorph( std::vector<FbxMesh*>& TriMeshList )
{
	bool bHasMorph = false;
	int iMeshNum = ( int )TriMeshList.size();
	for ( int iMeshIndex = 0; iMeshIndex < iMeshNum; iMeshIndex++ )
	{
		FbxMesh* pMesh = TriMeshList[iMeshIndex];
		if ( pMesh )
		{
			bHasMorph = pMesh->GetDeformerCount( FbxDeformer::eBlendShape ) > 0;
			if ( bHasMorph )
			{
				break;
			}
		}
	}

	if ( bHasMorph )
	{
		int iMeshIndex = 0;
		for ( auto pTriMesh : TriMeshList )
		{
			int iBlendShapeCount = pTriMesh->GetDeformerCount( FbxDeformer::eBlendShape );

			for ( int iBlendShapeIndex = 0; iBlendShapeIndex < iBlendShapeCount; iBlendShapeIndex++ )
			{
				FbxBlendShape* pBlendShape = ( FbxBlendShape* )pTriMesh->GetDeformer( iBlendShapeIndex , FbxDeformer::eBlendShape );
				int iBlendShapeChannelCount = pBlendShape->GetBlendShapeChannelCount();
				std::string BlendShapeName = pBlendShape->GetName();

				const bool bMightBeBadMAXFile = ( strcmp( BlendShapeName.c_str() , "Morpher" ) == 0 );

				for ( int32 iBlendShapeChannelIndex = 0; iBlendShapeChannelIndex < iBlendShapeChannelCount; iBlendShapeChannelIndex++ )
				{
					FbxBlendShapeChannel* pBlendShapeChannel = pBlendShape->GetBlendShapeChannel( iBlendShapeChannelIndex );

					if ( pBlendShapeChannel )
					{
						int32 iTargetShapeCount = pBlendShapeChannel->GetTargetShapeCount();

						std::string ChannelName = pBlendShapeChannel->GetName();
						
						if ( strstr( ChannelName.c_str() , BlendShapeName.c_str() ) == ChannelName.c_str() )
						{
							ChannelName = ChannelName.substr( BlendShapeName.size() + 1 , ChannelName.size() - BlendShapeName.size() - 1 );
						}

						for ( int32 iTargetShapeIndex = 0; iTargetShapeIndex < iTargetShapeCount; iTargetShapeIndex++ )
						{
							FbxShape* pTargetShape = pBlendShapeChannel->GetTargetShape( iTargetShapeIndex );

							std::string TargetShapeName;
							if ( iTargetShapeIndex > 1 )
							{
								TargetShapeName = pTargetShape->GetName();
							}
							else
							{
								if ( bMightBeBadMAXFile )
								{
									TargetShapeName = pTargetShape->GetName();
								}
								else
								{
									TargetShapeName = ChannelName;
								}
							}

							if ( m_vMorph.find( TargetShapeName ) == m_vMorph.end() )
							{
								MorphInfo& morph_info = m_vMorph[TargetShapeName];

								FbxVector4* pControlPoints = pTargetShape->GetControlPoints();
								int iControlPointCount = pTargetShape->GetControlPointIndicesCount();
								int* pControlPointIndices = pTargetShape->GetControlPointIndices();

								for ( int iControlPointIndex = 0; iControlPointIndex < iControlPointCount; iControlPointIndex++ )
								{
									if ( !IsZero( Vector3f( ( float )pControlPoints[iControlPointIndex][0] , ( float )pControlPoints[iControlPointIndex][1] , ( float )pControlPoints[iControlPointIndex][2] ) ) )
									{
										FbxVector4 ControlPoint = pControlPoints[iControlPointIndex];
										Vector4f p = Multipy( Vector3f( ( float )ControlPoint[0] , ( float )ControlPoint[1] , ( float )ControlPoint[2] ) , m_vLocalTransform[iMeshIndex] );
										int iVertexIndexOffset = m_vVertexOffset[iMeshIndex] + pControlPointIndices[iControlPointIndex];
										morph_info.MorphVertex.push_back( iVertexIndexOffset );
										morph_info.VertexDelta.push_back( Vector3f( p[0] , p[1] , p[2] ) - m_vBaseShape[iVertexIndexOffset] );
									}
								}
							}
						}
					}
				}
			}

			iMeshIndex++;
		}
	}
}

void FFbxImporter::RecursiveReadMeshNode( FbxNode* pNode , std::vector<FbxNode*>& mesh_list )
{
	if ( pNode->GetNodeAttribute() && pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh )
	{
		mesh_list.push_back( pNode );
	}

	for ( int i = 0; i < pNode->GetChildCount(); i++ )
	{
		RecursiveReadMeshNode( pNode->GetChild( i ) , mesh_list );
	}
}

void FFbxImporter::ReadSkeleton( FbxNode* pNode )
{
	if ( pNode && pNode->GetNodeAttribute() )
	{
		if ( pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton )
		{
			m_vSkeletonNode.push_back( pNode );
		}
	}

	for ( int i = 0; i < pNode->GetChildCount(); i++ )
	{
		FbxNode* pChildNode = pNode->GetChild( i );

		ReadSkeleton( pChildNode );
	}
}

int FFbxImporter::FindBoneIndex( FbxNode* pBoneNode )
{ 
	if ( m_LinkMap.find( pBoneNode ) != m_LinkMap.end() )
	{
		return m_LinkMap[pBoneNode];
	}

	return -1;
}

FbxNode* FFbxImporter::GetRootSkeleton( FbxNode* pNode )
{
	if ( pNode->GetParent() && pNode->GetParent()->GetNodeAttribute() && pNode->GetParent()->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton )
	{
		return GetRootSkeleton( pNode->GetParent() );
	}

	return pNode;
}

void FFbxImporter::ConvertToSkeleton()
{
	// Get Skeleton Root Node Array , Each Skeleton Root Node means Exist One Character
	for ( auto iter = m_vSkeletonNode.begin(); iter != m_vSkeletonNode.end(); iter++ )
	{
		FbxNode* pRootSkeleton = GetRootSkeleton( *iter );

		if ( pRootSkeleton )
		{
			bool bNew = true;
			for ( auto iter_skeleton_root_node = m_vSkeletonRootNode.begin(); iter_skeleton_root_node != m_vSkeletonRootNode.end(); iter_skeleton_root_node++ )
			{
				if ( *iter_skeleton_root_node == pRootSkeleton )
				{
					bNew = false;
					break;
				}
			}

			if ( bNew )
			{
				m_vSkeletonRootNode.push_back( pRootSkeleton );
			}
		}
	}

	// create VSkeleton Through m_vSkeletonRootNode Array
	for ( auto iter = m_vSkeletonRootNode.begin(); iter != m_vSkeletonRootNode.end(); iter++ )
	{
		int SkeletonIndex = VSkeletonManager::GetInstance().CreateSkeleton();

		// Skeleton Root Node , No Parent Node
		RecursiveCreateJoint( VSkeletonManager::GetInstance().GetSkeleton( SkeletonIndex ) , *iter );
	}
}

void FFbxImporter::RecursiveCreateJoint( VSkeleton* pSkeleton , FbxNode* pNode , int iParentIndex/* = -1*/ )
{
	if ( !pNode )	return;

	int iJointIndex = VJointManager::GetInstance().CreateJoint();
	m_LinkMap[pNode] = iJointIndex;

	VJointManager::GetInstance().GetJoint( iJointIndex )->AttachParent( iParentIndex );
	if ( iParentIndex != -1 )
	{
		VJointManager::GetInstance().GetJoint( iParentIndex )->AttachChild( iJointIndex );
	}

	for ( int i = 0; i < pNode->GetChildCount(); i++ )
	{
		RecursiveCreateJoint( pSkeleton , pNode->GetChild( i ) , iJointIndex );
	}
}

void FFbxImporter::ReadAnimation( FbxScene* pScene )
{
	/*int iAnimStackCount = pScene->GetSrcObjectCount<FbxAnimStack>();
	for ( int iAnimStackIndex = 0; iAnimStackIndex < iAnimStackCount; iAnimStackIndex++ )
	{
		FbxAnimStack* CurAnimStack = pScene->GetSrcObject<FbxAnimStack>( iAnimStackIndex );

		FbxTimeSpan AnimTimeSpan = CurAnimStack->GetLocalTimeSpan();
	}*/
}

bool FFbxImporter::Triangluate( FbxMesh*& pMesh )
{
	if ( !pMesh )	return false;

	if ( pMesh->IsTriangleMesh() )	return true;

	FbxGeometryConverter converter( m_pSdkManager );
	FbxNodeAttribute* pNodeAttribute = converter.Triangulate( pMesh , true );

	if ( pNodeAttribute )
	{
		pMesh = ( FbxMesh* )pNodeAttribute->GetNode()->GetNodeAttribute();
	}

	if ( !pMesh->IsTriangleMesh() )	return false;

	return true;
}