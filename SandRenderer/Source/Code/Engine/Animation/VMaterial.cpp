#include "Engine/PCH.h"
#include "Engine/Math/Vector3f.h"
#include "VMaterial.h"

using namespace Sand;

VMaterial::VMaterial()
{
	for ( int i = 0; i < EMT_MAPNUM; i++ )
	{
		m_MapName[i] = "";
	}

	m_Ambient = Vector3f::Zero();
	m_Emissive = Vector3f::Zero();
}

void VMaterial::SetMapName( const char* szFilename , EMapType eMapType )
{
	m_MapName[eMapType] = szFilename;
}

void VMaterial::SetAmbient( float r , float g , float b )
{
	m_Ambient[0] = r;	m_Ambient[1] = g;	m_Ambient[2] = b;
}

void VMaterial::SetEmissive( float r , float g , float b )
{
	m_Emissive[0] = r;	m_Emissive[1] = g;	m_Emissive[2] = b;
}

void VMaterial::SetDiffuse( float r , float g , float b )
{
	m_Diffuse[0] = r;	m_Diffuse[1] = g;	m_Diffuse[2] = b;
}

Vector3f& VMaterial::GetAmbient()
{
	return m_Ambient;
}

Vector3f VMaterial::GetAmbient() const
{
	return m_Ambient;
}

Vector3f& VMaterial::GetEmissive()
{
	return m_Emissive;
}

Vector3f VMaterial::GetEmissive() const
{
	return m_Emissive;
}

Vector3f& VMaterial::GetDiffuse()
{
	return m_Diffuse;
}

Vector3f VMaterial::GetDiffuse() const
{
	return m_Diffuse;
}

const char* VMaterial::GetMapName( EMapType eMapType )
{
	return m_MapName[eMapType].c_str();
}