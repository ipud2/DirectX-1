#ifndef BufferConfig_h
#define BufferConfig_h

namespace Sand
{
	class BufferConfig
	{
	public:
		BufferConfig();
		virtual ~BufferConfig();

		void SetDefaults();

		void SetDefaultConstantBuffer( UINT size , bool dynamic );
		void SetDefaultVertexBuffer( UINT size , bool dynamic );
		void SetDefaultIndexBuffer( UINT size , bool dynamic );
		void SetDefaultStructureBuffer( UINT size , UINT structureSize );

		// ----------∏˜ Ù–‘…Ë÷√---------------
		void SetByteWidth( UINT width );
		void SetUsage( D3D11_USAGE usage );
		void SetBindFlags( UINT BindFlags );
		void SetCPUAccessFlags( UINT CpuAccessFlags );
		void SetMiscFlags( UINT MiscFlags );
		void SetStructureByteStride( UINT StructureByteStride );

		D3D11_BUFFER_DESC GetBufferDesc();

	protected:
		D3D11_BUFFER_DESC m_State;

		friend class Renderer;
	};
}

#endif