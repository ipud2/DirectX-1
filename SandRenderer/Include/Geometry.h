#ifndef Geometry_h
#define Geometry_h

#include "PCH.h"

#include "ResourceProxy.h"

namespace Sand
{
	/*
		管理图元数据 
	*/
	class Geometry
	{
	public:
		Geometry();
		virtual ~Geometry();

		//************************************
		// Method:    LoadToBuffer
		// FullName:  Sand::Geometry::LoadToBuffer
		// Access:    public 
		// Returns:   void
		// Qualifier: 根据顶点数据，索引数据生成相应的顶点缓存和索引缓存
		//************************************
		void LoadToBuffer();

	protected:
		// 顶点数据

		// 索引数据


		// 顶点缓存
		ResourceProxyPtr m_VertexBuffer;
		// 索引缓存
		ResourceProxyPtr m_IndexBuffer;

		int m_iVertexSize;
		int m_iVertexCount;

		// 图元拓扑结构
		D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
	};

	typedef std::shared_ptr<Geometry> GeometryPtr;
};

#endif