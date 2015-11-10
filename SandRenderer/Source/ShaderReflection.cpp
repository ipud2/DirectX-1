#include "PCH.h"
#include "ShaderReflection.h"
#include "IParameterManager.h"
#include "BufferConfig.h"

using namespace Sand;

ShaderReflection::ShaderReflection()
{

}

ShaderReflection::~ShaderReflection()
{

}

/*
	Ϊÿ��Constant Buffer����һ������������Դ
	Ȼ��Constant Buffer���������¼����Դ��ID
	Ȼ��Ϊ����Դ�����Ϣ
*/
void ShaderReflection::InitConstantBufferParameter( IParameterManager* pParameterManager )
{
	for( unsigned int i = 0; i < ConstantBuffersDesc.size(); i++ )
	{
		if( ConstantBuffersDesc[i].Description.Type == D3D_CT_CBUFFER )
		{
			// ������TBuffer
			int index = pParameterManager->GetConstantBufferParameterData( ConstantBuffersDesc[i].pParamRef );

			if( index == -1 )
			{
				// -1��ʾ��δ��ʼ��

				// ����һ��ConstantBuffer����
				BufferConfig CBufferConfig;
				CBufferConfig.SetDefaultConstantBuffer( ConstantBuffersDesc[i].Description.Size , true );

				// ����Constant Buffer
				ResourceProxyPtr pConstantBuffer = Renderer::Get()->CreateConstantBuffer( &CBufferConfig , nullptr );
				int ResourceID = pConstantBuffer->GetResourceID();

				ConstantBuffersDesc[i].pParamRef->SetParameterData( &ResourceID );


				// Ϊ������ConstantBuffer��Դ�����Ҫ����Ϣ
				for( unsigned int j = 0; j < ConstantBuffersDesc[i].Variables.size(); j++ )
				{

				}
			}
		}
	}
}