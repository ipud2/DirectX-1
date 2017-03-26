#include "PCH.h"
#include "VTriangle.h"

using namespace Sand;

VTriangle::VTriangle()
{
	m_iMaterialIndex = -1;
	m_aIndex[0] = -1;	m_aIndex[1] = -1;	m_aIndex[2] = -1;
}

void VTriangle::SetMaterialIndex( int32 iMaterialIndex )
{
	m_iMaterialIndex = iMaterialIndex;
}

int32 VTriangle::GetMatrixIndex()
{
	return m_iMaterialIndex;
}

uint32& VTriangle::operator[]( uint32 index )
{
	return m_aIndex[index];
}

uint32 VTriangle::operator[]( uint32 index ) const
{
	return m_aIndex[index];
}