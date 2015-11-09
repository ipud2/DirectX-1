#ifndef ConstantBuffer_h
#define ConstantBuffer_h

#include "Buffer.h"

namespace Sand
{
	class ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~ConstantBuffer();

		virtual ResourceType GetType();

	protected:
		friend Renderer;
	};
}

#endif