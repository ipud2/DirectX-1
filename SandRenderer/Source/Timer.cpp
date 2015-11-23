#include "PCH.h"
#include "Timer.h"

using namespace Sand;

Timer::Timer()
{
	m_iFramesPerSecond = 0;
	m_iMaxFramesPerSecond = 0;
	m_iFrameCount = 0;

	m_fDelta = 0;
	m_fFixedDelta = 0.0f;
	m_bUsedFixedStep = false;


	QueryPerformanceFrequency( ( LARGE_INTEGER* )&m_TicksPerSecond64 );
	QueryPerformanceCounter( ( LARGE_INTEGER* )&m_CurrentTicks64 );

	m_StartupTicks64 = m_CurrentTicks64;
	m_OneSecTicks64 = m_CurrentTicks64;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	m_iFramesPerSecond = 0;
	m_iFrameCount = 0;
	m_fDelta = 0;
}

void Timer::SetFixedTimeStep( float step )
{
	// if step <= 0.0f , not use fixed step
	if( step <= 0.0f )
	{
		m_bUsedFixedStep = false;
		m_fFixedDelta = 0.0f;
	}
	else
	{
		m_bUsedFixedStep = true;
		m_fFixedDelta = step;
	}
}

void Timer::Update()
{
	m_LastTicks64 = m_CurrentTicks64;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&m_CurrentTicks64 );

	// update the time increment
	if( m_bUsedFixedStep )
	{
		m_fDelta = m_fFixedDelta;
	}
	else
	{
		m_fDelta = ( float )( ( __int64 )m_CurrentTicks64 - ( __int64 )m_LastTicks64 / ( __int64 )m_TicksPerSecond64 );
	}


	// continue counting the frame rate regardless of the time step
	// m_OneSecTicks64是这一秒最开始时的Ticks
	if( ( float )( ( __int64 )m_CurrentTicks64 - ( __int64 )m_OneSecTicks64 ) / ( __int64 )m_TicksPerSecond64 < 1.0f )
	{
		// 如果没经过一秒，则该秒的帧数加1
		m_iFrameCount++;
	}
	else
	{
		// 已经经过了一秒，则记录其的帧数
		m_iFramesPerSecond = m_iFrameCount;

		if( m_iFramesPerSecond > m_iMaxFramesPerSecond )
		{
			m_iMaxFramesPerSecond = m_iFramesPerSecond;
		}

		// 重新记录该秒的帧数，将m_OneSecTicks设置为该秒开始的Ticks
		m_iFrameCount = 0;
		m_OneSecTicks64 = m_CurrentTicks64;
	}
}

float Timer::Elapsed()
{
	return m_fDelta;
}

int Timer::Framerate()
{
	return m_iFramesPerSecond;
}

float Timer::Runtimer()
{
	return ( ( float )( ( __int64 )m_CurrentTicks64 - ( __int64 )m_StartupTicks64 ) / ( __int64 )m_TicksPerSecond64 );
}

int Timer::MaxFramerate()
{
	return m_iMaxFramesPerSecond;
}

int Timer::FrameCount()
{
	return m_iFrameCount;
}