#ifndef FFBX_IMPORTER_H
#define FFBX_IMPORTER_H

#include <fbxsdk.h>
#include <fbxsdk/fileio/fbximporter.h>
#include "fbxsdk/scene/geometry/fbxmesh.h"
#include "Engine/Animation/FFbxDataConverter.h"
#include "Engine/Animation/VVertex.h"
#include "FbxInfoHeader.h"

namespace Sand
{
	class VSkeleton;
	class VScene;
	class VMaterial;
	class VTriangle;

	class FFbxImporter
	{
	public:
		FFbxImporter();
		~FFbxImporter();

	public:
		void SetScene( VScene& scene );

		bool Load( const char* szFilename );

		bool OpenFile( const char* Filename );

		void ReadSkeleton( FbxNode* pNode );

		void ReadMeshInfo();

		void ReadMaterial( FbxNode* pMeshNode , std::map<int , int>& vMaterialMap );

		void ReadAnimation( FbxScene* pScene );

		void CleanUp();

	protected:
		void RecursiveReadMeshNode( FbxNode* pNode , std::vector<FbxNode*>& mesh_list );
		
		void ReadInputMask( FbxMesh* pMesh , EInputMask& InputMask );
		bool ReadVertices( FbxMesh* pMesh , std::vector<VVertex>& vVertexList , std::vector<VTriangle>& TriangleList , EInputMask eInputMask , std::map<int , int>& vMaterialMap );
		bool ReadNormals( FbxMesh* pMesh , std::vector<VVertex>& vVertexList );
		bool ReadTangents( FbxMesh* pMesh , std::vector<VVertex>& vVertexList );
		bool ReadUVs( FbxMesh* pMesh , std::vector<VVertex>& vVertexList );

		int ReadSurfaceMaterial( FbxSurfaceMaterial* pFbxMaterial );

		int ReadTriangleMaterialIndex( FbxMesh* pNode , int iPolygonIndex , int iControIndex , std::map<int , int>& vMaterialMap );

		FbxNode* GetRootSkeleton( FbxNode* pNode );

		void ConvertToSkeleton();

		void RecursiveCreateJoint( VSkeleton* pSkeleton , FbxNode* pNode , int iParentIndex = -1 );

		bool Triangluate( FbxMesh*& pMesh );

		int	 FindBoneIndex( FbxNode* pBoneNode );

	protected:
		FbxManager*			m_pSdkManager;
		FbxScene*			m_pFbxScene;
		VScene*				m_pScene;
		FFbxDataConverter	converter;
	protected:
		std::vector<FbxNode*>	m_vSkeletonNode;
		std::vector<FbxNode*>	m_vSkeletonRootNode;

		std::map<FbxNode* , int>	m_LinkMap;

	public:
		void ReadMorph( std::vector<FbxMesh*>& TriMeshList );

		// --------------------以下为Morph相关--------------------------
	protected:
		//std::vector<MorphInfo> m_vMorph;
		std::map<std::string , MorphInfo>	m_vMorph;
		std::vector<Vector3f>				m_vBaseShape;
		std::vector<int>					m_vVertexOffset;
		std::vector<Matrix4f>				m_vLocalTransform;
	};
}
#endif