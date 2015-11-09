#ifndef VertexElement_h
#define VertexElement_h

#include "PCH.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace Sand
{
	/*
		��װ���ֶ��������������ڱ�������ֶε���������
	*/
	class VertexElement
	{
	public:
		VertexElement( int tuple , int elementCount );
		~VertexElement();

		// ��ȡ����Ԫ�صĴ�С�����ֽڱ�ʾ
		int GetElementSizeInBytes();
		
		// ��ȡԪ�صĸ���
		int GetCount();

		// Ԫ��ά��
		int GetTuple();

		void* GetDataPtr( int i );

		float*		Get1fTupleDataPtr( int i );
		Vector2f*	Get2fTupleDataPtr( int i );
		Vector3f*	Get3fTupleDataPtr( int i );
		Vector4f*	Get4fTupleDataPtr( int i );


		float* operator[]( int i );
		const float* operator[]( int i ) const;

	public:
		std::string					m_SemanticName;			// �ֶ���
		UINT						m_uiSemanticIndex;		// �ֶ�����
		DXGI_FORMAT					m_Format;				// ��ʽ
		UINT						m_uiInputSlot;			// ����˿�
		UINT						m_uiAlignedByteOffset;	// �ֽ�ƫ��
		D3D11_INPUT_CLASSIFICATION	m_InputSlotClass;
		UINT						m_uiInstanceDataStepRate;

	protected:
		// ����
		float* m_pfData;

		// Ԫ��ָ���Ǽ�Ԫ��
		int m_iTuple;
		// Ԫ����
		int m_iCount;

	public:
		// ���õ�һЩ�ֶ���
		static std::string PositionSemantic;
		static std::string NormalSemantic;
		static std::string TexCoordSemantic;
		static std::string TangentSemantic;
	};
}

#endif