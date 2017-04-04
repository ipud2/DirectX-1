#include <Engine/PCH.h>
#include "Resource.h"

using namespace Sand;

unsigned short Resource::s_usResourceID = 0;

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