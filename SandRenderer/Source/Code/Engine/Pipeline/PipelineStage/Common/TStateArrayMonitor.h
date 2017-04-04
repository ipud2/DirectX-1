// 该类用于监视shader state
// 如：Contant Buffer , SamplerState , ShaderResourceView , UnorderedAccessView
// 由于shader每种资源都有多个slot可以绑定
// 该类可以方便的确定我们要传入shader的多个slot上的资源
#ifndef TStateArrayMonitor_h
#define TStateArrayMonitor_h

namespace Sand
{
	template< class T , unsigned int N >
	class TStateArrayMonitor
	{
	public:
		TStateArrayMonitor( T InitialState );
		~TStateArrayMonitor();

		void SetSister( TStateArrayMonitor<T , N>* pSister );
		bool SameAsSister( unsigned int slot );

		void SetState( unsigned int slot , T State );

		bool IsUpdateNeed();

		unsigned int GetStartSlot();
		unsigned int GetEndSlot();
		unsigned int GetRange();

		T GetState( unsigned int slot ) const;
		T* GetFirstSlotLocation();
		T* GetSlotLocation( unsigned int slot );

		void InitializeStates();
		void ResetTracking();

	private:
		void SearchFromBelow();
		void SearchFromAbove();

		// 状态监视器变量
		unsigned int m_uiStartSlot;
		unsigned int m_uiEndSlot;

		bool m_bUpdateNeeded;

		// 状态数据
		T m_InitialState;
		T m_States[N];

		// Sister state
		TStateArrayMonitor<T , N>* m_pSister;
	};

#include "TStateArrayMonitor.inl"
};
#endif
