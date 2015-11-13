#ifndef Geometry_h
#define Geometry_h

#include "PCH.h"

#include "ResourceProxy.h"
#include "VertexElement.h"
#include "InputAssemblerStageExecutor.h"

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

		// ---------------------ͼԪ���˽ṹ-----------------------
		void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology );
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology();

		// ----------------------���ڴ����������ݺ���������---------------------------
		void AddElement( VertexElement* pElement );

		void AddFace( int index_1 , int index_2 , int index_3 );

		//************************************
		// Method:    LoadToBuffer
		// FullName:  Sand::Geometry::LoadToBuffer
		// Access:    public 
		// Returns:   void
		// Qualifier: ����Vertex Buffer �� Index Buffer��ResourceProxy����
		//************************************
		void LoadToBuffer();

		// Ϊ����ΪShaderID�Ķ�����ɫ������InputLayout����
		void GenerateInputLayout( int ShaderID );


		// ��ȡͼԪ��Ŀ
		int GetPrimitiveCount();

		// ���㶥���б��ж�����Ŀ
		int CalculateVertexCount();
		// ���㶥��ṹ��С
		int CalculateVertexStructureSize();

	protected:
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
	};

	typedef std::shared_ptr<Geometry> GeometryPtr;
};

#endif