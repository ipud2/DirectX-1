#include "Resource.h"

using namespace Sand;

Resource::Resource()
{
	m_usInnerID = s_usResourceID;
	s_usResourceID++;
}

Resource::~Resource()
{

}

unsigned short Resource::GetInnerID()
{
	return m_usInnerID;
}