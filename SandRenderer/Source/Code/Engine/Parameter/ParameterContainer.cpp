#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterContainer.h"
#include "Engine/Parameter/Parameters/BaseClass/RenderParameter.h"
#include "Engine/Parameter/IParameterManager.h"
#include "Engine/Utility/Log.h"

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
		for( int i = 0; i < ( int )m_RenderParameter.size(); i++ )
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
			Log::Get().Error( L"tried to add a parameter writer to an entity that was already there" );
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

BoolParameterWriter* ParameterContainer::GetBoolParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	BoolParameterWriter* pBoolParameterWriter = nullptr;

	if ( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if ( pParameter )
		{
			// 检查其类型是否为Vector
			if ( pParameter->GetParameterType() == PT_BOOL )
			{
				pBoolParameterWriter = dynamic_cast< BoolParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Error( L"Error: Trying to access a bool in a non-bool parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}
	}

	/*
	若不存在，则创建
	*/
	if ( pBoolParameterWriter == nullptr )
	{
		pBoolParameterWriter = new BoolParameterWriter;
		pBoolParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetBoolParameterRef( name ) );
		AddRenderParameter( pBoolParameterWriter );
	}

	return pBoolParameterWriter;
}

FloatParameterWriter* ParameterContainer::GetFloatParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	FloatParameterWriter* pFloatParameterWriter = nullptr;

	if ( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if ( pParameter )
		{
			// 检查其类型是否为Vector
			if ( pParameter->GetParameterType() == PT_FLOAT )
			{
				pFloatParameterWriter = dynamic_cast< FloatParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Error( L"Error: Trying to access a float in a non-bool parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}
	}

	/*
		若不存在，则创建
	*/
	if ( pFloatParameterWriter == nullptr )
	{
		pFloatParameterWriter = new FloatParameterWriter;
		pFloatParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetFloatParameterRef( name ) );
		AddRenderParameter( pFloatParameterWriter );
	}

	return pFloatParameterWriter;
}

Vector4fParameterWriter* ParameterContainer::GetVector4fParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	Vector4fParameterWriter* pVectorParameterWriter = nullptr;

	if( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if( pParameter )
		{
			// 检查其类型是否为Vector
			if( pParameter->GetParameterType() == PT_VECTOR_4F )
			{
				pVectorParameterWriter = dynamic_cast< Vector4fParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Error( L"Error: Trying to access a vector in a non-vector parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}
	
	/*
		若不存在，则创建
	*/
	if ( pVectorParameterWriter == nullptr )
	{
		pVectorParameterWriter = new Vector4fParameterWriter;
		pVectorParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetVector4fParameterRef( name ) );
		AddRenderParameter( pVectorParameterWriter );
	}

	return pVectorParameterWriter;
}

Vector3fParameterWriter* ParameterContainer::GetVector3fParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	Vector3fParameterWriter* pVectorParameterWriter = nullptr;

	if ( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if ( pParameter )
		{
			// 检查其类型是否为Vector
			if ( pParameter->GetParameterType() == PT_VECTOR_3F )
			{
				pVectorParameterWriter = dynamic_cast< Vector3fParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Error( L"Error: Trying to access a vector in a non-vector parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	/*
		若不存在，则创建
	*/
	if ( pVectorParameterWriter == nullptr )
	{
		pVectorParameterWriter = new Vector3fParameterWriter;
		pVectorParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetVector3fParameterRef( name ) );
		AddRenderParameter( pVectorParameterWriter );
	}

	return pVectorParameterWriter;
}

Vector2fParameterWriter* ParameterContainer::GetVector2fParameterWriter( const std::wstring& name )
{
	// 获取name对应的ParameterWriter
	ParameterWriter* pParameterWriter = GetRenderParameterWriter( name );
	Vector2fParameterWriter* pVectorParameterWriter = nullptr;

	if ( pParameterWriter )
	{
		RenderParameter* pParameter = pParameterWriter->GetRenderParameterRef();

		if ( pParameter )
		{
			// 检查其类型是否为Vector
			if ( pParameter->GetParameterType() == PT_VECTOR_2F )
			{
				pVectorParameterWriter = dynamic_cast< Vector2fParameterWriter* >( pParameterWriter );
			}
			else
			{
				Log::Get().Error( L"Error: Trying to access a vector in a non-vector parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	/*
	若不存在，则创建
	*/
	if ( pVectorParameterWriter == nullptr )
	{
		pVectorParameterWriter = new Vector2fParameterWriter;
		pVectorParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetVector2fParameterRef( name ) );
		AddRenderParameter( pVectorParameterWriter );
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
				Log::Get().Error( L"Error: Trying to access a vector in a non-matrix parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}


	if ( nullptr == pMatrixParameterWriter )
	{
		pMatrixParameterWriter = new MatrixParameterWriter;
		pMatrixParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetMatrixParameterRef( name ) );
		AddRenderParameter( pMatrixParameterWriter );
	}

	return pMatrixParameterWriter;
}

MatrixArrayParameterWriter* ParameterContainer::GetMatrixArrayParameterWriter( const std::wstring& name , int count )
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
				Log::Get().Error( L"Error: Trying to access a matrixarray in a non-matrixarray parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	if ( nullptr == pMatrixArrayParameterWriter )
	{
		pMatrixArrayParameterWriter = new MatrixArrayParameterWriter;
		pMatrixArrayParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetMatrixArrayParameterRef( name , count ) );
		AddRenderParameter( pMatrixArrayParameterWriter );
	}

	return pMatrixArrayParameterWriter;
}

StructureParameterWriter* ParameterContainer::GetStructureParameterWriter( const std::wstring& name , int Size )
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
				Log::Get().Error( L"Error: Trying to access a structure Parameter Writer in non-StructureParameterWriter" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a Parameter writer without any reference set" );
		}
	}

	if ( nullptr == pStructureParameterWriter )
	{
		pStructureParameterWriter = new StructureParameterWriter;
		// 创建StructureParameterWriter的RenderParameterRef
		pStructureParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetStructureParameterRef( name , Size ) );
		AddRenderParameter( pStructureParameterWriter );
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
				Log::Get().Error( L"Error: Trying to access a vector in a non-sampler parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	if ( nullptr == pSamplerParameterWriter )
	{
		pSamplerParameterWriter = new SamplerParameterWriter;
		pSamplerParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetSamplerStateParameterRef( name ) );
		AddRenderParameter( pSamplerParameterWriter );
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
				Log::Get().Error( L"Error: Trying to access a vector in a non-ShaderResource parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}


	if ( nullptr == pShaderResourceParameterWriter )
	{
		pShaderResourceParameterWriter = new ShaderResourceParameterWriter;
		pShaderResourceParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetShaderResourceParameterRef( name ) );
		AddRenderParameter( pShaderResourceParameterWriter );
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
				Log::Get().Error( L"Error: Trying to access a vector in a non-ShaderResource parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	if ( nullptr == pUnorderedAccessParameterWriter )
	{
		pUnorderedAccessParameterWriter = new UnorderedAccessParameterWriter;
		pUnorderedAccessParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetUnorderedAccessParameterRef( name ) );
		AddRenderParameter( pUnorderedAccessParameterWriter );
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
				Log::Get().Error( L"Error: Trying to access a vector in a non-ShaderResource parameter writers!!" );
			}
		}
		else
		{
			Log::Get().Error( L"Error: Trying to access a parameter writer without any reference set!!" );
		}

	}

	if ( nullptr == pConstantBufferParameterWriter )
	{
		pConstantBufferParameterWriter = new ConstantBufferParameterWriter;
		pConstantBufferParameterWriter->SetRenderParameterRef( Renderer::Get()->GetParameterManagerRef()->GetConstantBufferParameterRef( name ) );
		AddRenderParameter( pConstantBufferParameterWriter );
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