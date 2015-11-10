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

		// ConstantBuffe�е�ÿ��Element�ض�������ֵ��
		// ������ֵ�Ͳ�������������Ƶ����������Ǳ�����һ����ʶ��
		// ÿ����������д������ʱ���ñ�ʶ����������
		// ��˵��������ⲿ�޸��˸ò�����ֵʱ
		// pParamRef�ı�ʶ����ValueID�ض���ͬ
		// ���ǿ���ͨ�����ַ�ʽ���жϳ��������е������Ƿ��б仯���Ƿ���Ҫ����д�룬���󶨵�shader
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
			�ж�ConstantBuffer�ĸ���Elements��ֵ�Ƿ��иı䣬���У������
		*/
		void Update( PipelineManager* pPipelineManager );


	protected:
		std::vector<ConstantBufferElementDesc> m_vElements;
		friend Renderer;
	};
}

#endif