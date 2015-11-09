#ifndef VertexBuffer_h
#define VertexBuffer_h

#include "Buffer.h"

namespace Sand
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~VertexBuffer();

		virtual ResourceType GetType();

		void SetVertexStructureSize( int size );
		void SetVertexCount( int count );

	protected:
		int m_iVertexStructureSize;
		int m_iVertexCount;

		friend Renderer;
	};
};
#endif