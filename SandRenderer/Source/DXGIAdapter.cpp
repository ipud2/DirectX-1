#include "PCH.h"
#include "DXGIAdapter.h"
#include "DXGIOutput.h"

using namespace Sand;

DXGIAdapter::DXGIAdapter( Microsoft::WRL::ComPtr<IDXGIAdapter1> pAdapter )
{
	// 枚举出所有的输出设备
	m_pAdapter = pAdapter;

	Microsoft::WRL::ComPtr<IDXGIOutput> pOutput;

	while( pAdapter->EnumOutputs( ( UINT )m_vOutputs.size() , pOutput.ReleaseAndGetAddressOf() ) != DXGI_ERROR_NOT_FOUND )
	{
		m_vOutputs.push_back( pOutput );
	}
}

DXGIAdapter::~DXGIAdapter()
{

}