#include "Resource.h"

using namespace Sand;

Resource::Resource()
{
	s_usResourceID++;

	m_usInnerID = s_usResourceID;
}

Resource::~Resource()
{

}

unsigned short Resource::GetInnerID()
{
	return m_usInnerID;
}