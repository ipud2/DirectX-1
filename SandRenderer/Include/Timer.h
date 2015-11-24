#ifndef Timer_h
#define Timer_h

namespace Sand
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void Update();
		void Reset();

		float Runtimer();
		float Elapsed();
		int Framerate();
		int MaxFramerate();
		int FrameCount();
		float FrameTime();

		void SetFixedTimeStep( float step );

	private:
		float m_fDelta;
		int m_iFramesPerSecond;
		int m_iMaxFramesPerSecond;
		int m_iFrameCount;

		float m_fFixedDelta;
		bool m_bUsedFixedStep;

		unsigned __int64 m_TicksPerSecond64;
		unsigned __int64 m_StartupTicks64;
		unsigned __int64 m_CurrentTicks64;
		unsigned __int64 m_OneSecTicks64;
		unsigned __int64 m_LastTicks64;
	};
};
#endif