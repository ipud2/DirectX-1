#include "PCH.h"

#ifndef DXGIAdapter_h
#define DXGIAdapter_h

namespace Sand
{
	class DXGIOutput;

	class DXGIAdapter
	{
	public:
		DXGIAdapter( Microsoft::WRL::ComPtr<IDXGIAdapter1> pAdapter );
		virtual ~DXGIAdapter();

	protected:
		// ���������󣬶�Ӧ�Կ����������ģ���adapter
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_pAdapter;
		std::vector<DXGIOutput> m_vOutputs;

		friend class Renderer;
	};
}

#endif