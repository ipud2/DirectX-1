#ifndef Buffer_h
#define Buffer_h

#include "Resource.h"
#include "BufferConfigure.h"

namespace Sand
{
	class Buffer : public Resource
	{
	public:
		Buffer();
		virtual ~Buffer();

		D3D11_BUFFER_DESC GetActualBufferDesc();
		D3D11_BUFFER_DESC GetDesiredBufferDesc();
		void SetDesiredBufferDesc( D3D11_BUFFER_DESC desc );

		UINT GetByteWidth();
		void SetByteWidth( UINT ByteWidth );

		D3D11_USAGE GetUsage();
		void SetUsage( D3D11_USAGE usage );

		UINT GetBindFlags();
		void SetBindFlags( UINT BindFlags );

		UINT GetCPUAccessFlags();
		void SetCPUAccessFlags( UINT CPUAccessFlags );

		UINT GetMiscFlags();
		void SetMiscFlags( UINT MiscFlags );

		UINT GetStructureByteStride();
		void SetStructureByteStride( UINT StructureByteStride );

		virtual ID3D11Resource* GetResource();

	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
		D3D11_BUFFER_DESC m_ActualDesc;
		D3D11_BUFFER_DESC m_DesiredDesc;

		friend class Renderer;
	};
};
#endif