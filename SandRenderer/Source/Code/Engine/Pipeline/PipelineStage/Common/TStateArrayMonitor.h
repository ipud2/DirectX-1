// �������ڼ���shader state
// �磺Contant Buffer , SamplerState , ShaderResourceView , UnorderedAccessView
// ����shaderÿ����Դ���ж��slot���԰�
// ������Է����ȷ������Ҫ����shader�Ķ��slot�ϵ���Դ
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

		// ״̬����������
		unsigned int m_uiStartSlot;
		unsigned int m_uiEndSlot;

		bool m_bUpdateNeeded;

		// ״̬����
		T m_InitialState;
		T m_States[N];

		// Sister state
		TStateArrayMonitor<T , N>* m_pSister;
	};

#include "TStateArrayMonitor.inl"
};
#endif
