#ifndef TStateMonitor_h
#define TStateMonitor_h

namespace Sand
{
	template<class T>
	class TStateMonitor
	{
	public:
		TStateMonitor( T initializeState );
		~TStateMonitor();

		void SetSister( TStateMonitor<T>* pSister );
		bool SameAsSister();

		void SetState( T state );
		T GetState() const;

		bool IsUpdateNeeded();
		void InitializeState();
		void ResetTracking();

	private:
		// monitor variable
		bool m_bUploadNeeded;

		// state data
		T m_InitializeState;
		T m_State;

		// sister state
		TStateMonitor<T>* m_pSister;
	};

#include "TStateMonitor.inl"

};
#endif