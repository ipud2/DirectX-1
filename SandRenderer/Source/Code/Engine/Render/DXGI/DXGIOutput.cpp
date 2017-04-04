#include <Engine/PCH.h>
#include "DXGIOutput.h"

using namespace Sand;

DXGIOutput::DXGIOutput( Microsoft::WRL::ComPtr<IDXGIOutput> pOutput )
{
	m_pOutput = pOutput;
}

DXGIOutput::~DXGIOutput()
{

}