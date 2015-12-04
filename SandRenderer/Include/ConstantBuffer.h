#ifndef ConstantBuffer_h
#define ConstantBuffer_h

#include "Buffer.h"
#include "BaseNumericTypeRenderParameter.h"
#include "ParameterManager.h"

namespace Sand
{
	struct ConstantBufferElementDesc
	{
		BaseNumericTypeRenderParameter* pParamRef;

		unsigned int Offset;
		unsigned int Size;
		unsigned int ElementCount;				// 用于数组元素个数
		D3D_SHADER_VARIABLE_TYPE VarType;		// 变量类型：float , bool , int
		D3D_SHADER_VARIABLE_CLASS VarClass;		// 变量类：矢量，标量，矩阵
		unsigned int Columns;					// float4的Columns为4
		// ConstantBuffe中的每个Element必定都是数值型
		// 正如数值型参数对象中所设计的那样，我们保存了一个标识符
		// 每次往参数中写入数据时，该标识符将会自增
		// 因此当我们在外部修改了该参数的值时
		// pParamRef的标识符与Identifier必定不同
		// 我们可以通过这种方式来判断常量缓存中的数据是否有变化，是否需要重新写入，并绑定到shader
		unsigned int Identifier;
	};

	class ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~ConstantBuffer();

		virtual ResourceType GetType();

		/*
			增加该Constant Buffer中的elment
		*/
		void AddElement( ConstantBufferElementDesc element );

		/*
			判断ConstantBuffer的各个Elements的值是否有改变，若有，则更新
			更新是指将数据更新到ID3D11Buffer中，即
			Map()
			...
			UnMap();
		*/
		void EvaluateElements( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

		/*
			检查索引为index的元素是否与element一致
		*/
		bool ConstainElement( int index , const ConstantBufferElementDesc & element );

		/*
			清空Constant Buffer中的元素
		*/
		void EmptyElements();

		/*
			Access Auto Update
		*/
		bool GetAutoUpdate();
		void SetAutoUpdate( bool bAutoUpdate );

	protected:
		std::vector<ConstantBufferElementDesc> m_vElements;
		bool m_bAutoUpdate;

		friend Renderer;
	};
};
#endif