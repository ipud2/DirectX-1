#ifndef IndexBuffer_h
#define IndexBuffer_h

#include "Buffer.h"

namespace Sand
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~IndexBuffer();

		virtual ResourceType GetType();

		void SetIndexSize( int size );
		void SetIndexCount( int count );

	protected:
		int m_iIndexSize;
		int m_iIndexCount;

		friend Renderer;
	};
}

#endif