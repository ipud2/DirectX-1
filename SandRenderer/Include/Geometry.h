#ifndef Geometry_h
#define Geometry_h

#include "PCH.h"

#include "ResourceProxy.h"

namespace Sand
{
	/*
		����ͼԪ���� 
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
		// Qualifier: ���ݶ������ݣ���������������Ӧ�Ķ��㻺�����������
		//************************************
		void LoadToBuffer();

	protected:
		// ��������

		// ��������


		// ���㻺��
		ResourceProxyPtr m_VertexBuffer;
		// ��������
		ResourceProxyPtr m_IndexBuffer;

		int m_iVertexSize;
		int m_iVertexCount;

		// ͼԪ���˽ṹ
		D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
	};

	typedef std::shared_ptr<Geometry> GeometryPtr;
};

#endif