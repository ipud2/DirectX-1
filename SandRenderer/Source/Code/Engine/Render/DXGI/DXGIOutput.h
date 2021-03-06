#include <Engine/PCH.h>

#ifndef DXGIOutput_h
#define DXGIOutput_h

namespace Sand
{
	class DXGIOutput
	{
	public:
		DXGIOutput( Microsoft::WRL::ComPtr<IDXGIOutput> pOutput );
		virtual ~DXGIOutput();

	protected:
		Microsoft::WRL::ComPtr<IDXGIOutput> m_pOutput;

		friend class Renderer;
	};
}

#endif