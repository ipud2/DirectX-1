#ifndef StructuredBuffer_h
#define StructuredBuffer_h

#include "Buffer.h"

namespace Sand
{
	class StructuredBuffer : public Buffer
	{
	public:
		StructuredBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~StructuredBuffer();

		virtual ResourceType GetType();

	protected:
		friend Renderer;
	};
}

#endif