#include "PCH.h"
#include "VKeyFrame.h"

Sand::VKeyFrame::VKeyFrame()
{
	m_fStartTime = 0.0f;
	m_fDuration = 0.0f;
	m_fValue = 0.0f;
}

void Sand::VKeyFrame::SetValue( float start_time , float value )
{
	m_fStartTime = start_time;
	m_fDuration = value;
}

void Sand::VKeyFrame::SetDuration( float duration )
{
	m_fDuration = duration;
}