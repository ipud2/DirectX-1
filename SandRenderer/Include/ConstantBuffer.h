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
		unsigned int ElementCount;				// ��������Ԫ�ظ���
		D3D_SHADER_VARIABLE_TYPE VarType;		// �������ͣ�float , bool , int
		D3D_SHADER_VARIABLE_CLASS VarClass;		// �����ࣺʸ��������������
		unsigned int Columns;					// float4��ColumnsΪ4
		// ConstantBuffe�е�ÿ��Element�ض�������ֵ��
		// ������ֵ�Ͳ�������������Ƶ����������Ǳ�����һ����ʶ��
		// ÿ����������д������ʱ���ñ�ʶ����������
		// ��˵��������ⲿ�޸��˸ò�����ֵʱ
		// pParamRef�ı�ʶ����Identifier�ض���ͬ
		// ���ǿ���ͨ�����ַ�ʽ���жϳ��������е������Ƿ��б仯���Ƿ���Ҫ����д�룬���󶨵�shader
		unsigned int Identifier;
	};

	class ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer );
		virtual ~ConstantBuffer();

		virtual ResourceType GetType();

		/*
			���Ӹ�Constant Buffer�е�elment
		*/
		void AddElement( ConstantBufferElementDesc element );

		/*
			�ж�ConstantBuffer�ĸ���Elements��ֵ�Ƿ��иı䣬���У������
			������ָ�����ݸ��µ�ID3D11Buffer�У���
			Map()
			...
			UnMap();
		*/
		void EvaluateElements( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

		/*
			�������Ϊindex��Ԫ���Ƿ���elementһ��
		*/
		bool ConstainElement( int index , const ConstantBufferElementDesc & element );

		/*
			���Constant Buffer�е�Ԫ��
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