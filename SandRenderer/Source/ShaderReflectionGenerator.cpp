#include "PCH.h"
#include "ShaderReflectionGenerator.h"
#include "Log.h"
#include "ParameterManager.h"

using Microsoft::WRL::ComPtr;
using namespace Sand;

ShaderReflectionGenerator::ShaderReflectionGenerator()
{

}

ShaderReflectionGenerator::~ShaderReflectionGenerator()
{

}

ShaderReflection* ShaderReflectionGenerator::GenerateReflection( ID3DBlob* pCompiledShader )
{
	IParameterManager* pParameterManager = Renderer::Get()->GetParameterManagerRef();

	ShaderReflection* pShaderReflection = new ShaderReflection;

	// 获取反射对象
	ComPtr<ID3D11ShaderReflection> pReflector;
	HRESULT hr = D3DReflect( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , IID_ID3D11ShaderReflection , reinterpret_cast< void** >( pReflector.GetAddressOf() ) );
	if( FAILED( hr ) )
	{
		Log::Get().Write( L"创建shader reflection接口失败！" );
		return nullptr;
	}

	// 一层一层的剥开你的心~~ ^……^
	
	// 从最顶层开始解析
	D3D11_SHADER_DESC ShaderDesc;
	pReflector->GetDesc( &ShaderDesc );
	pShaderReflection->ShaderDesc = ShaderDesc;

	// -----------------------Input Signature Description------------------
	for( UINT i = 0; i < ShaderDesc.InputParameters; i++ )
	{
		// ShaderDesc.InputParameters表示输入字段的个数
		D3D11_SIGNATURE_PARAMETER_DESC InputSignatureDesc;
		pReflector->GetInputParameterDesc( i , &InputSignatureDesc );		// 获取输入字段描述

		// 保存输入字段描述
		pShaderReflection->InputSignatureParameterDesc.push_back( InputSignatureDesc );
	}

	// -------------------Output Signature Description------------------
	for( UINT i = 0; i < ShaderDesc.OutputParameters; i++ )
	{
		// ShaderDesc.OutputParameters表示输出字段的个数
		D3D11_SIGNATURE_PARAMETER_DESC OutputSignatureDesc;
		pReflector->GetOutputParameterDesc( i , &OutputSignatureDesc );		// 获取输出字段描述

		// 保存输出字段描述
		pShaderReflection->OutputSignatureParameterDesc.push_back( OutputSignatureDesc );
	}

	// --------------------Constant Buffer---------------------------
	for( UINT i = 0; i < ShaderDesc.ConstantBuffers; i++ )
	{
		ID3D11ShaderReflectionConstantBuffer* pConstantBuffer = pReflector->GetConstantBufferByIndex( i );

		// 获取Constant Buffer的描述
		D3D11_SHADER_BUFFER_DESC BufferDesc;
		pConstantBuffer->GetDesc( &BufferDesc );

		if( BufferDesc.Type == D3D_CT_CBUFFER || BufferDesc.Type == D3D_CT_TBUFFER )
		{
			ConstantBufferDesc CBufferDesc;
			
			// --------------------------------------------------------接下来是填充ConstantBufferDesc-----------------------------------------------------------

			CBufferDesc.Description = BufferDesc;
			CBufferDesc.pParamRef = pParameterManager->GetConstantBufferParameterRef( SandString::ToUnicode( std::string( BufferDesc.Name ) ) );

			for( UINT j = 0; j < BufferDesc.Variables; j++ )
			{
				// BufferDesc.Variable是Constant Buffer中元素数
				ID3D11ShaderReflectionVariable* pVariable = pConstantBuffer->GetVariableByIndex( j );

				D3D11_SHADER_VARIABLE_DESC VariableDesc;
				pVariable->GetDesc( &VariableDesc );

				CBufferDesc.Variables.push_back( VariableDesc );


				// 获取该变量的类型
				ID3D11ShaderReflectionType* pType = pVariable->GetType();
				D3D11_SHADER_TYPE_DESC TypeDesc;
				pType->GetDesc( &TypeDesc );

				CBufferDesc.Types.push_back( TypeDesc );

				// --------------------为每个variable创建参数对象-----------------------------------------
				BaseNumericTypeRenderParameter* pRenderParameter;

				if( TypeDesc.Class == D3D_SVC_VECTOR )
				{
					pRenderParameter = pParameterManager->GetVectorParameterRef( SandString::ToUnicode( VariableDesc.Name ) );

					// shader中D3D_SVC_VECTOR的变量若存在默认值，则用于初始化
					if ( VariableDesc.DefaultValue != nullptr )
					{
						pRenderParameter->SetParameterData( reinterpret_cast< void* >( VariableDesc.DefaultValue ) );
					}
				}
				else if( TypeDesc.Class == D3D_SVC_MATRIX_ROWS || TypeDesc.Class == D3D_SVC_MATRIX_COLUMNS )
				{
					// 检查是否为矩阵数组
					unsigned int count = TypeDesc.Elements;

					if( count == 0 )
					{
						pRenderParameter = pParameterManager->GetMatrixParameterRef( SandString::ToUnicode( VariableDesc.Name ) );
					}
					else
					{
						pRenderParameter = pParameterManager->GetMatrixArrayParameterRef( SandString::ToUnicode( VariableDesc.Name ) , count );
					}
				}

				CBufferDesc.Parameters.push_back( pRenderParameter );
			}

			pShaderReflection->ConstantBuffers.push_back( CBufferDesc );
		}
	}


	// ---------------------------------Resource Binding----------------------------
	for( UINT i = 0; i < ShaderDesc.BoundResources; i++ )
	{
		D3D11_SHADER_INPUT_BIND_DESC ResourceDesc;
		pReflector->GetResourceBindingDesc( i , &ResourceDesc );

		ShaderInputBindDesc BindDesc( ResourceDesc );

		if( ResourceDesc.Type == D3D_SIT_CBUFFER || ResourceDesc.Type == D3D_SIT_TBUFFER )
		{
			// 资源为常量缓存
			BindDesc.pParamRef = pParameterManager->GetConstantBufferParameterRef( BindDesc.Name );
		}
		else if( ResourceDesc.Type == D3D_SIT_TEXTURE || ResourceDesc.Type == D3D_SIT_STRUCTURED )
		{
			// 资源为纹理对象
			BindDesc.pParamRef = pParameterManager->GetShaderResourceParameterRef( BindDesc.Name );
		}
		else if( ResourceDesc.Type == D3D_SIT_SAMPLER )
		{
			// 资源为采样器
			BindDesc.pParamRef = pParameterManager->GetSamplerStateParameterRef( BindDesc.Name );
		}
		else if( ResourceDesc.Type == D3D_SIT_UAV_RWTYPED || ResourceDesc.Type == D3D_SIT_UAV_RWSTRUCTURED ||
				 ResourceDesc.Type == D3D_SIT_UAV_RWBYTEADDRESS || ResourceDesc.Type == D3D_SIT_UAV_APPEND_STRUCTURED ||
				 ResourceDesc.Type == D3D_SIT_UAV_CONSUME_STRUCTURED || ResourceDesc.Type == D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER )
		{
			// 资源为UnorderedAccessView
			BindDesc.pParamRef = pParameterManager->GetUnorderedAccessParameterRef( BindDesc.Name );
		}

		pShaderReflection->ResourceBindDesc.push_back( BindDesc );
	}

	return pShaderReflection;
}