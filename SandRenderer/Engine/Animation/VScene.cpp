#include "PCH.h"
#include "VScene.h"
#include "VMesh.h"
#include "VMaterial.h"

using namespace Sand;

int VScene::CreateMesh( EInputMask eInputMask )
{ 
	m_vMesh.push_back( new VMesh( eInputMask ) );

	return ( int )m_vMesh.size() - 1;
}

VMaterial& VScene::CreateMaterial()
{
	m_vMaterial.push_back( new VMaterial() );

	return *m_vMaterial[m_vMaterial.size() - 1];
}

VMesh* VScene::GetMesh( int iMeshIndex )
{
	if ( iMeshIndex >= 0 && iMeshIndex < ( int )m_vMesh.size() )
	{
		return m_vMesh[iMeshIndex];
	}

	return nullptr;
}

VMaterial& VScene::GetMaterial( int iMeshIndex )
{
	return *m_vMaterial[iMeshIndex];
}

int VScene::GetMeshCount()
{
	return ( int )m_vMesh.size();
}

int VScene::GetMaterialCount()
{
	return ( int )m_vMaterial.size();
}