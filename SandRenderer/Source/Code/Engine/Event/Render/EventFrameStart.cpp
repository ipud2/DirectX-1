#include <Engine/PCH.h>
#include "EventFrameStart.h"

using namespace Sand;

EventFrameStart::EventFrameStart( float dt )
{
	m_fDelta = dt;
}

EventFrameStart::~EventFrameStart()
{

}

std::wstring EventFrameStart::GetEventName()
{
	return std::wstring( L"Frame_start" );
}

EventType EventFrameStart::GetEventType()
{
	return RENDER_FRAME_START;
}

float EventFrameStart::GetElapsed()
{
	return m_fDelta;
}