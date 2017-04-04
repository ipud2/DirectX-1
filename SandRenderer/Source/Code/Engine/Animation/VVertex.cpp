#include "Engine/PCH.h"
#include "Engine/Animation/VVertex.h"

using namespace Sand;

VVertex::VVertex( EInputMask eInputMask )
{
	m_eInputMask = eInputMask;
	m_iJointNum = 0;

	for ( int i = 0; i < MAX_SKIN_BONE_NUM; i++ )
	{
		m_aJointIndex[i] = -1;
		m_aJointWeight[i] = 0.0f;
	}
}

void VVertex::SetPosition( float x , float y , float z )
{
	if ( m_eInputMask & EIM_POSITION )
	{
		m_aPos[0] = x;	m_aPos[1] = y;	m_aPos[2] = z;
	}
}

void VVertex::SetNormal( float x , float y , float z )
{
	if ( m_eInputMask & EIM_NORMAL )
	{
		m_aNormal[0] = x;	m_aNormal[1] = y;	m_aNormal[2] = z;
	}
}

void VVertex::SetTangent( float x , float y , float z )
{
	if ( m_eInputMask & EIM_TANGENT )
	{
		m_aTangent[0] = x;	m_aTangent[1] = y;	m_aTangent[2] = z;
	}
}

void VVertex::SetTexcoord( int iSet , float u , float v )
{
	// just support set zero
	if ( iSet == 0 && ( m_eInputMask & EIM_TEXCOORD0 << iSet ) )
	{
		m_aTexcoord[0] = u;	m_aTexcoord[1] = v;
	}
}

void VVertex::SetColor( float r , float g , float b )
{
	m_aColor[0] = r;	m_aColor[1] = g;	m_aColor[2] = b;
}

void VVertex::AddWeight( int iJointIndex , float fJointWeight )
{
	if ( m_iJointNum >= MAX_SKIN_BONE_NUM )	return;

	m_aJointIndex[m_iJointNum] = iJointIndex;
	m_aJointWeight[m_iJointNum] = fJointWeight;
	m_iJointNum++;
}

bool VVertex::GetPosition( float& x , float& y , float& z )
{
	if ( m_eInputMask & EIM_TEXCOORD0 )
	{
		x = m_aPos[0];	y = m_aPos[1];	z = m_aPos[2];
		return true;
	}

	return false;
}

bool VVertex::GetNormal( float& x , float& y , float& z )
{
	if ( m_eInputMask & EIM_NORMAL )
	{
		x = m_aNormal[0];	y = m_aNormal[1]; z = m_aNormal[2];
		return true;
	}

	return false;
}

bool VVertex::GetTangent( float& x , float& y , float& z )
{
	if ( m_eInputMask & EIM_TANGENT )
	{
		x = m_aTangent[0];	y = m_aTangent[1];	z = m_aTangent[2];
		return true;
	}

	return false;
}

bool VVertex::GetTexcoord( float& x , float& y )
{
	if ( m_eInputMask & EIM_TEXCOORD0 )
	{
		x = m_aTexcoord[0];	y = m_aTexcoord[1];
		return true;
	}

	return false;
}

void VVertex::GetColor( float& r , float& g , float& b )
{
	r = m_aColor[0];	g = m_aColor[1];	b = m_aColor[2];
}

bool VVertex::GetWeight( int iWeightIndex , int32& iJointIndex , float& fJointWeight )
{
	if ( m_eInputMask & EIM_WEIGHT && iWeightIndex < m_iJointNum && iWeightIndex >= 0 )
	{
		iJointIndex = m_aJointIndex[iWeightIndex];
		fJointWeight = m_aJointWeight[iWeightIndex];

		return true;
	}

	return false;
}

int VVertex::GetWeightCount()
{
	return m_iJointNum;
}