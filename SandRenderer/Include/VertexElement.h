#ifndef VertexElement_h
#define VertexElement_h

#include "PCH.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace Sand
{
	/*
		封装了字段描述，并且用于保存该类字段的所有数据
	*/
	class VertexElement
	{
	public:
		VertexElement( int tuple , int elementCount );
		~VertexElement();

		// 获取单个元素的大小，以字节表示
		int GetElementSizeInBytes();
		
		// 获取元素的个数
		int GetCount();

		// 元组维数
		int GetTuple();

		void* GetDataPtr( int i );

		float*		Get1fTupleDataPtr( int i );
		Vector2f*	Get2fTupleDataPtr( int i );
		Vector3f*	Get3fTupleDataPtr( int i );
		Vector4f*	Get4fTupleDataPtr( int i );


		float* operator[]( int i );
		const float* operator[]( int i ) const;

	public:
		std::string					m_SemanticName;			// 字段名
		UINT						m_uiSemanticIndex;		// 字段索引
		DXGI_FORMAT					m_Format;				// 格式
		UINT						m_uiInputSlot;			// 输入端口
		UINT						m_uiAlignedByteOffset;	// 字节偏移
		D3D11_INPUT_CLASSIFICATION	m_InputSlotClass;
		UINT						m_uiInstanceDataStepRate;

	protected:
		// 数据
		float* m_pfData;

		// 元素指明是几元组
		int m_iTuple;
		// 元素数
		int m_iCount;

	public:
		// 常用的一些字段名
		static std::string PositionSemantic;
		static std::string NormalSemantic;
		static std::string TexCoordSemantic;
		static std::string TangentSemantic;
	};
}

#endif