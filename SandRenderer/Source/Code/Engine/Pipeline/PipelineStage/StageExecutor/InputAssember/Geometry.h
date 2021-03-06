#ifndef Geometry_h
#define Geometry_h

#include <Engine/PCH.h>

#include "Engine/Resource/ResourceProxy.h"
#include "Engine/Pipeline/PipelineStage/StageExecutor/Basic/VertexElement.h"
#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/InputAssemblerStageExecutor.h"
#include "Engine/Parameter/IParameterManager.h"
#include "Engine/Parameter/ParameterContainer.h"

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

		virtual void Execute( PipelineManager* pPipelineManager , IParameterManager* pParameterManager , int SubObjectID );

		// 创建Vertex Buffer 和 Index Buffer的ResourceProxy对象
		void LoadToBuffer();

		virtual void UpdateRenderParameters( IParameterManager* pParameterManager , int SubObjectID );

		// ---------------------图元拓扑结构-----------------------
		void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology );
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology();

		void AddElement( VertexElement* pElement );

		void AddFace( int index_1 , int index_2 , int index_3 );

		void AddGroupInfo( int iIndexOffset , int iIndexCount , int iVertexIndex = 0 , ResourceProxyPtr DiffuseMap = ResourceProxyPtr( new ResourceProxy ) );
		
		// 为索引为ShaderID的顶点着色器创建InputLayout对象
		void GenerateInputLayout( int ShaderID );

		// 获取图元数目
		int GetPrimitiveCount();

		// 计算顶点列表中顶点数目
		int CalculateVertexCount();

		// 计算顶点结构大小
		int CalculateVertexStructureSize();

		virtual uint32 GetSubObjectCount() const;

	protected:
		ParameterContainer ParameterWriters;

		ShaderResourceParameterWriter* m_pShaderResourceWriter;

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

		std::vector<int> m_vIndexOffset;
		std::vector<int> m_vIndexCounts;
		std::vector<int> m_vVertexOffset;
		std::vector<ResourceProxyPtr> m_DiffuseTextures;
	};

	typedef std::shared_ptr<Geometry> GeometryPtr;
};

#endif