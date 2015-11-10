#ifndef ConstantBuffer_h
#define ConstantBuffer_h

#include "Buffer.h"
#include "RenderParameter.h"

namespace Sand
{
	struct ConstantBufferElementDesc
	{
		RenderParameter* pParamRef;

		unsigned int offset;
		unsigned int size;
		D3D_SHADER_VARIABLE_CLASS VarClass;
		unsigned int elments;

		// ConstantBuffe中的每个Element必定都是数值型
		// 正如数值型参数对象中所设计的那样，我们保存了一个标识符
		// 每次往参数中写入数据时，该标识符将会自增
		// 因此当我们在外部修改了该参数的值时
		// pParamRef的标识符与ValueID必定不同
		// 我们可以通过这种方式来判断常量缓存中的数据是否有变化，是否需要重新写入，并绑定到shader
		unsigned int ValueID;
	};

	class ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~ConstantBuffer();

		virtual ResourceType GetType();

		void AddElement( ConstantBufferElementDesc element );

		/*
			判断ConstantBuffer的各个Elements的值是否有改变，若有，则更新
		*/
		void Update( PipelineManager* pPipelineManager );


	protected:
		std::vector<ConstantBufferElementDesc> m_vElements;
		friend Renderer;
	};
}

#endif