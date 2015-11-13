#ifndef Geometry_h
#define Geometry_h

#include "PCH.h"

#include "ResourceProxy.h"
#include "VertexElement.h"
#include "InputAssemblerStageExecutor.h"

namespace Sand
{
	/*
		管理图元数据 
	*/
	class Geometry : public InputAssemblerStageExecutor
	{
	public:
		Geometry();
		virtual ~Geometry();

		// ---------------------图元拓扑结构-----------------------
		void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology );
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology();

		// ----------------------用于创建顶点数据和索引数据---------------------------
		void AddElement( VertexElement* pElement );

		void AddFace( int index_1 , int index_2 , int index_3 );

		//************************************
		// Method:    LoadToBuffer
		// FullName:  Sand::Geometry::LoadToBuffer
		// Access:    public 
		// Returns:   void
		// Qualifier: 创建Vertex Buffer 和 Index Buffer的ResourceProxy对象
		//************************************
		void LoadToBuffer();

		// 为索引为ShaderID的顶点着色器创建InputLayout对象
		void GenerateInputLayout( int ShaderID );


		// 获取图元数目
		int GetPrimitiveCount();

		// 计算顶点列表中顶点数目
		int CalculateVertexCount();
		// 计算顶点结构大小
		int CalculateVertexStructureSize();

	protected:
		// 顶点数据
		std::vector<VertexElement*> m_vElements;
		// 索引数据
		std::vector<UINT> m_vIndices;

		// 顶点缓存
		ResourceProxyPtr m_VertexBuffer;
		// 索引缓存
		ResourceProxyPtr m_IndexBuffer;

		// 顶点结构大小：各分量大小之和
		int m_iVertexStructureSize;
		// 顶点数目，这里为三角形的个数的三倍
		int m_iVertexCount;

		// 图元拓扑结构
		D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
	};

	typedef std::shared_ptr<Geometry> GeometryPtr;
};

#endif