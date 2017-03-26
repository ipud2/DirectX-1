#ifndef Geometry_h
#define Geometry_h

#include "PCH.h"

#include "ResourceProxy.h"
#include "VertexElement.h"
#include "InputAssemblerStageExecutor.h"
#include "IParameterManager.h"
#include "ParameterContainer.h"

namespace Sand
{
	/*
		����ͼԪ���� 
	*/
	class Geometry : public InputAssemblerStageExecutor
	{
	public:
		Geometry();
		virtual ~Geometry();

		virtual void Execute( PipelineManager* pPipelineManager , IParameterManager* pParameterManager , int SubObjectID );

		// ����Vertex Buffer �� Index Buffer��ResourceProxy����
		void LoadToBuffer();

		virtual void UpdateRenderParameters( IParameterManager* pParameterManager , int SubObjectID );

		// ---------------------ͼԪ���˽ṹ-----------------------
		void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology );
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology();

		void AddElement( VertexElement* pElement );

		void AddFace( int index_1 , int index_2 , int index_3 );

		void AddGroupInfo( int iIndexOffset , int iIndexCount , int iVertexIndex = 0 , ResourceProxyPtr DiffuseMap = ResourceProxyPtr( new ResourceProxy ) );
		
		// Ϊ����ΪShaderID�Ķ�����ɫ������InputLayout����
		void GenerateInputLayout( int ShaderID );

		// ��ȡͼԪ��Ŀ
		int GetPrimitiveCount();

		// ���㶥���б��ж�����Ŀ
		int CalculateVertexCount();

		// ���㶥��ṹ��С
		int CalculateVertexStructureSize();

		virtual uint32 GetSubObjectCount() const;

	protected:
		ParameterContainer ParameterWriters;

		ShaderResourceParameterWriter* m_pShaderResourceWriter;

		// ��������
		std::vector<VertexElement*> m_vElements;
		// ��������
		std::vector<UINT> m_vIndices;

		// ���㻺��
		ResourceProxyPtr m_VertexBuffer;
		// ��������
		ResourceProxyPtr m_IndexBuffer;

		// ����ṹ��С����������С֮��
		int m_iVertexStructureSize;
		// ������Ŀ������Ϊ�����εĸ���������
		int m_iVertexCount;

		// ͼԪ���˽ṹ
		D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;

		std::vector<int> m_vIndexOffset;
		std::vector<int> m_vIndexCounts;
		std::vector<int> m_vVertexOffset;
		std::vector<ResourceProxyPtr> m_DiffuseTextures;
	};

	typedef std::shared_ptr<Geometry> GeometryPtr;
};

#endif