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
	为每个Constant Buffer创建一个常量缓存资源
	然后Constant Buffer参数对象记录该资源的ID
	然后为该资源填充信息
*/
void ShaderReflection::InitConstantBufferParameter( IParameterManager* pParameterManager )
{
	for( unsigned int i = 0; i < ConstantBuffersDesc.size(); i++ )
	{
		if( ConstantBuffersDesc[i].Description.Type == D3D_CT_CBUFFER )
		{
			// 不考虑TBuffer
			int index = pParameterManager->GetConstantBufferParameterData( ConstantBuffersDesc[i].pParamRef );

			if( index == -1 )
			{
				// -1表示还未初始化

				// 创建一个ConstantBuffer对象
				BufferConfig CBufferConfig;
				CBufferConfig.SetDefaultConstantBuffer( ConstantBuffersDesc[i].Description.Size , true );

				// 创建Constant Buffer
				ResourceProxyPtr pConstantBuffer = Renderer::Get()->CreateConstantBuffer( &CBufferConfig , nullptr );
				int ResourceID = pConstantBuffer->GetResourceID();

				ConstantBuffersDesc[i].pParamRef->SetParameterData( &ResourceID );


				// 为创建的ConstantBuffer资源添加想要的信息
				for( unsigned int j = 0; j < ConstantBuffersDesc[i].Variables.size(); j++ )
				{

				}
			}
		}
	}
}