#include "PCH.h"
#include "ShaderReflection.h"
#include "IParameterManager.h"
#include "BufferConfig.h"
#include "ConstantBuffer.h"
#include "Log.h"
#include "PipelineManager.h"

using namespace Sand;

ShaderReflection::ShaderReflection()
{

}

ShaderReflection::~ShaderReflection()
{

}

/*
	为每个Constant Buffer创建一个常量缓存资源
	然后Constant Buffer参数对象记录该资源的ID
	然后为该资源填充信息
*/
void ShaderReflection::InitConstantBufferParameter( IParameterManager* pParameterManager )
{
	for( unsigned int i = 0; i < ConstantBuffers.size(); i++ )
	{
		if( ConstantBuffers[i].Description.Type == D3D_CT_CBUFFER )
		{
			// 不考虑TBuffer
			int index = pParameterManager->GetConstantBufferParameterData( ConstantBuffers[i].pParamRef );

			if( index == -1 )
			{
				// -1表示还未初始化

				// 创建一个ConstantBuffer对象
				BufferConfig CBufferConfig;
				CBufferConfig.SetDefaultConstantBuffer( ConstantBuffers[i].Description.Size , true );

				// 创建Constant Buffer
				ResourceProxyPtr pConstantBuffer = Renderer::Get()->CreateConstantBuffer( &CBufferConfig , nullptr );
				int ResourceID = pConstantBuffer->GetResourceID();

				ConstantBuffers[i].pParamRef->SetParameterData( &ResourceID );

				ConstantBuffer* cbuffer = Renderer::Get()->GetConstantBufferByIndex( ResourceID );

				// 为创建的ConstantBuffer资源添加想要的信息
				for( unsigned int j = 0; j < ConstantBuffers[i].Variables.size(); j++ )
				{
					ConstantBufferElementDesc element;

					element.pParamRef = ConstantBuffers[i].Parameters[j];
					element.Offset = ConstantBuffers[i].Variables[j].StartOffset;
					element.Size = ConstantBuffers[i].Variables[j].Size;
					element.ElementCount = ConstantBuffers[i].Types[j].Elements;
					element.VarClass = ConstantBuffers[i].Types[j].Class;
					element.Identifier = -1;

					cbuffer->AddElement( element );
				}
			}
		}
	}
}

void ShaderReflection::UpdateConstantBufferParameter( PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	// 该函数在将shader绑定到管线上时被调用
	// 该函数将会让每个Constant Buffer参数的ID指向的常量缓存对象自动检测是否需要更新，若需要，则进行更新

	for( unsigned int i = 0; i < ConstantBuffers.size(); i++ )
	{
		int index = pParameterManager->GetConstantBufferParameterData( ConstantBuffers[i].pParamRef );

		// 获取ConstantBuffer对象
		ConstantBuffer* pBuffer = Renderer::Get()->GetConstantBufferByIndex( index );

		if( pBuffer )
		{
			if( pBuffer->GetAutoUpdate() )
			{
				pBuffer->EvaluateElements( pPipelineManager , pParameterManager );
			}
		}
		else
		{
			Log::Get().Write( L"Trying to update a constant buffer doesn't exist!" );
		}
	}
}

void ShaderReflection::BindShaderInputResourceToShaderStage( ShaderType type , PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	for( int i = 0; i < ResourceBindDesc.size(); i++ )
	{
		UINT slot = ResourceBindDesc[i].BindPoint;

		switch( ResourceBindDesc[i].Type )
		{
			case D3D_SIT_TEXTURE:
			case D3D_SIT_STRUCTURED:
			case D3D_SIT_BYTEADDRESS:
			{
				// Shader Resource View
				pPipelineManager->BindShaderResourceViewResourceToShaderStage( type , ResourceBindDesc[i].pParamRef , slot , pParameterManager );
				break;
			}

			case D3D_SIT_SAMPLER:
			{
				// Sampler
				pPipelineManager->BindSamplerResourceToShaderStage( type , ResourceBindDesc[i].pParamRef , slot , pParameterManager );
				break;
			}

			case D3D_SIT_CBUFFER:
			case D3D_SIT_TBUFFER:
			{
				pPipelineManager->BindConstantBufferResourceToShaderStage( type , ResourceBindDesc[i].pParamRef , slot , pParameterManager );
				break;
			}

			case D3D_SIT_UAV_RWSTRUCTURED:
			case D3D_SIT_UAV_RWTYPED:
			case D3D_SIT_UAV_RWBYTEADDRESS:
			case D3D_SIT_UAV_APPEND_STRUCTURED:
			case D3D_SIT_UAV_CONSUME_STRUCTURED:
			case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
			{
				pPipelineManager->BindUnorderedAccessViewResourceToShaderStage( type , ResourceBindDesc[i].pParamRef , slot , pParameterManager );
				break;
			}

		}
	}
}
