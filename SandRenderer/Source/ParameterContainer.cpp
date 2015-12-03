#include "PCH.h"
#include "ParameterContainer.h"
#include "RenderParameter.h"
#include "IParameterManager.h"
#include "Log.h"

using namespace Sand;

ParameterContainer::ParameterContainer()
{

}

ParameterContainer::~ParameterContainer()
{
	for( auto pParameter : m_RenderParameter )
	{
		delete pParameter;
	}
}

void ParameterContainer::AddRenderParameter( ParameterWriter* pWriter )
{
	if( pWriter )
	{
		ParameterWriter* pCurr = nullptr;

		// 判断是否已存在该ParameterWriter
		for( int i = 0; i < m_RenderParameter.size(); i++ )
		{
			if( pWriter->GetRenderParameterRef()->GetName() == m_RenderParameter[i]->GetRenderParameterRef()->GetName() )
			{
				pCurr = m_RenderParameter[i];
				break;
			}
		}

		if( !pCurr )		// 在Container中未发现该参数对象对应ParameterWriter
		{
			m_RenderParameter.push_back( pWriter );
		}
		else
		{
			Log::Get().Write( L"tried to add a parameter writer to an entity that was already there" );
		}

	}
}

ParameterWriter* ParameterContainer::GetRenderParameterWriter( const std::wstring& name )
{
	ParameterWriter* result = nullptr;

	for( auto pParameterWriter : m_RenderParameter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			if( name.compare( pParameter->GetName() ) == 0 )
			{
				result = pParameterWriter;
				break;
			}
		}
	}

	return result;
}

VectorParameterWriter* ParameterContainer::GetVectorParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	VectorParameterWriter* pVectorParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Vector
			if( pParameter->GetParameterType() == PT_VECTOR )
			{
				pVectorParameterWriter = dynamic_cast< VectorParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a vector in a non-vector parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pVectorParameterWriter;
}

MatrixParameterWriter* ParameterContainer::GetMatrixParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	MatrixParameterWriter* pMatrixParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Matrix
			if( pParameter->GetParameterType() == PT_MATRIX )
			{
				pMatrixParameterWriter = dynamic_cast< MatrixParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a vector in a non-matrix parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pMatrixParameterWriter;
}

MatrixArrayParameterWriter* ParameterContainer::GetMatrixArrayParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	MatrixArrayParameterWriter* pMatrixArrayParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为MatrixArray
			if( pParameter->GetParameterType() == PT_MATRIX_ARRAY )
			{
				pMatrixArrayParameterWriter = dynamic_cast< MatrixArrayParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a matrixarray in a non-matrixarray parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pMatrixArrayParameterWriter;
}

StructureParameterWriter* ParameterContainer::GetStructureParameterWriter( const std::wstring& name )
{
	// 我们要返回的对象
	StructureParameterWriter* pStructureParameterWriter = nullptr;

	// 首先获取该名字对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );

	if ( pParameterWriter )
	{
		// 获取该ParameterWriter中存储的Parameter对象
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if ( pParameter )
		{
			// 判断类型是否相符
			if ( pParameter->GetParameterType() == PT_STRUCTURE )
			{
				pStructureParameterWriter = dynamic_cast< StructureParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a structure Parameter Writer in non-StructureParameterWriter" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a Parameter writer without any reference set" );
		}
	}

	return pStructureParameterWriter;
}

SamplerParameterWriter* ParameterContainer::GetSamplerParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	SamplerParameterWriter* pSamplerParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Vector
			if( pParameter->GetParameterType() == PT_SAMPLER )
			{
				pSamplerParameterWriter = dynamic_cast< SamplerParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a vector in a non-sampler parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pSamplerParameterWriter;
}

ShaderResourceParameterWriter* ParameterContainer::GetShaderResourceParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	ShaderResourceParameterWriter* pShaderResourceParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Vector
			if( pParameter->GetParameterType() == PT_SHADER_RESOURCE )
			{
				pShaderResourceParameterWriter = dynamic_cast< ShaderResourceParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a vector in a non-ShaderResource parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pShaderResourceParameterWriter;
}

UnorderedAccessParameterWriter* ParameterContainer::GetUnorderedAccessParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	UnorderedAccessParameterWriter* pUnorderedAccessParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Vector
			if( pParameter->GetParameterType() == PT_UNORDERED_ACCESS )
			{
				pUnorderedAccessParameterWriter = dynamic_cast< UnorderedAccessParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a vector in a non-ShaderResource parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pUnorderedAccessParameterWriter;
}

ConstantBufferParameterWriter* ParameterContainer::GetConstantBufferParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	ConstantBufferParameterWriter* pConstantBufferParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Vector
			if( pParameter->GetParameterType() == PT_CONSTANT_BUFFER )
			{
				pConstantBufferParameterWriter = dynamic_cast< ConstantBufferParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Write( L"Error: Trying to access a vector in a non-ShaderResource parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Write( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	return pConstantBufferParameterWriter;
}

void ParameterContainer::UpdateRenderParam( IParameterManager* pParamMgr )
{
	for( auto pParamWriter : m_RenderParameter )
	{
		pParamWriter->UpdateValueToParameter( pParamMgr );
	}
}

void ParameterContainer::InitRenderParams()
{
	for( auto pParamWriter : m_RenderParameter )
	{
		pParamWriter->InitializeParameter();
	}
}

ConstantBufferParameterWriter* ParameterContainer::SetValueToConstantBufferParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value )
{
	ConstantBufferParameterWriter* pConstantBufferWriter = GetConstantBufferParameterWriter( name );

	if( nullptr == pConstantBufferWriter )
	{
		pConstantBufferWriter = new ConstantBufferParameterWriter;
		pConstantBufferWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetConstantBufferParameterRef( name ) );
		AddRenderParameter( pConstantBufferWriter );
	}


	pConstantBufferWriter->SetValue( Value );

	return pConstantBufferWriter;
}

ShaderResourceParameterWriter* ParameterContainer::SetValueToShaderResourceParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value )
{
	ShaderResourceParameterWriter* pShaderResourceWriter = GetShaderResourceParameterWriter( name );

	if( nullptr == pShaderResourceWriter )
	{
		pShaderResourceWriter = new ShaderResourceParameterWriter;
		pShaderResourceWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetShaderResourceParameterRef( name ) );
		AddRenderParameter( pShaderResourceWriter );
	}


	pShaderResourceWriter->SetValue( Value );

	return pShaderResourceWriter;
}

UnorderedAccessParameterWriter* ParameterContainer::SetValueToUnorderedAccessParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value )
{
	UnorderedAccessParameterWriter* pUnorderedAccessParameterWriter = GetUnorderedAccessParameterWriter( name );

	if( nullptr == pUnorderedAccessParameterWriter )
	{
		pUnorderedAccessParameterWriter = new UnorderedAccessParameterWriter;
		pUnorderedAccessParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetUnorderedAccessParameterRef( name ) );
		AddRenderParameter( pUnorderedAccessParameterWriter );
	}

	pUnorderedAccessParameterWriter->SetValue( Value );

	return pUnorderedAccessParameterWriter;
}

SamplerParameterWriter* ParameterContainer::SetValueToSamplerParameterWriter( const std::wstring& name , int Value )
{
	SamplerParameterWriter* pSamplerParameterWriter = GetSamplerParameterWriter( name );

	if( nullptr == pSamplerParameterWriter )
	{
		pSamplerParameterWriter = new SamplerParameterWriter;
		pSamplerParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetSamplerStateParameterRef( name ) );
		AddRenderParameter( pSamplerParameterWriter );
	}

	pSamplerParameterWriter->SetValue( Value );

	return pSamplerParameterWriter;
}

VectorParameterWriter* ParameterContainer::SetValueToVectorParameterWriter( const std::wstring& name , const Vector4f& Value )
{
	VectorParameterWriter* pVectorParameterWriter = GetVectorParameterWriter( name );

	if( nullptr == pVectorParameterWriter )
	{
		pVectorParameterWriter = new VectorParameterWriter;
		pVectorParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetVectorParameterRef( name ) );
		AddRenderParameter( pVectorParameterWriter );
	}

	pVectorParameterWriter->SetValue( Value );

	return pVectorParameterWriter;
}

MatrixParameterWriter* ParameterContainer::SetValueToMatrixParameterWriter( const std::wstring& name , const Matrix4f& Value )
{
	MatrixParameterWriter* pMatrixParameterWriter = GetMatrixParameterWriter( name );

	if( nullptr == pMatrixParameterWriter )
	{
		pMatrixParameterWriter = new MatrixParameterWriter;
		pMatrixParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetMatrixParameterRef( name ) );
		AddRenderParameter( pMatrixParameterWriter );
	}

	pMatrixParameterWriter->SetValue( Value );

	return pMatrixParameterWriter;
}

MatrixArrayParameterWriter* ParameterContainer::SetValueToMatrixArrayParameterWriter( const std::wstring& name , Matrix4f* Value , int count )
{
	MatrixArrayParameterWriter* pMatrixArrayParameterWriter = GetMatrixArrayParameterWriter( name );

	if( nullptr == pMatrixArrayParameterWriter )
	{
		pMatrixArrayParameterWriter = new MatrixArrayParameterWriter;
		pMatrixArrayParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetMatrixArrayParameterRef( name , count ) );
		AddRenderParameter( pMatrixArrayParameterWriter );
	}

	pMatrixArrayParameterWriter->SetValue( Value , count );

	return pMatrixArrayParameterWriter;
}

StructureParameterWriter* ParameterContainer::SetValueToStructureParameterWriter( const std::wstring& name , char* Value , int Size )
{
	StructureParameterWriter* pStructureParameterWriter = GetStructureParameterWriter( name );

	if ( nullptr == pStructureParameterWriter )
	{
		pStructureParameterWriter = new StructureParameterWriter;
		// 创建StructureParameterWriter的RenderParameterRef
		pStructureParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetStructureParameterRef( name , Size ) );
		AddRenderParameter( pStructureParameterWriter );
	}

	pStructureParameterWriter->SetValue( Value , Size );

	return pStructureParameterWriter;
}