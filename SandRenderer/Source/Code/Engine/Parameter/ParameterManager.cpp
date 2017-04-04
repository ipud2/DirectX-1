#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterManager.h"
#include "Engine/Utility/Log.h"

using namespace Sand;

std::map<std::wstring , RenderParameter*> ParameterManager::Parameters;

ParameterManager::ParameterManager()
{
	m_pParent = nullptr;

	m_pWorldMatrix = GetMatrixParameterRef( std::wstring( L"WorldMatrix" ) );
	m_pViewMatrix = GetMatrixParameterRef( std::wstring( L"ViewMatrix" ) );
	m_pProjMatrix = GetMatrixParameterRef( std::wstring( L"ProjMatrix" ) );
	m_pWorldViewMatrix = GetMatrixParameterRef( std::wstring( L"WorldViewMatrix" ) );
	m_pWorldProjMatrix = GetMatrixParameterRef( std::wstring( L"WorldProjMatrix" ) );
	m_pViewProjMatrix = GetMatrixParameterRef( std::wstring( L"ViewProjMatrix" ) );
	m_pWorldViewProjMatrix = GetMatrixParameterRef( std::wstring( L"WorldViewProjMatrix" ) );
	m_pWorldInvTransposeMatrix = GetMatrixParameterRef( std::wstring( L"WorldInvTransposeMatrix" ) );
}

ParameterManager::~ParameterManager()
{
	
}


// ------------------------------------------------Set Paramter Data-------------------------------------------------------------
void ParameterManager::SetBoolParameterData( const std::wstring& name , bool* pBool )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new BoolParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pBool ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if ( Parameters[name]->GetParameterType() == PT_BOOL )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pBool ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Bool值赋给非Bool型参数" );
		}
	}
}

void ParameterManager::SetFloatParameterData( const std::wstring& name , float* pFloat )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new FloatParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pFloat ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if ( Parameters[name]->GetParameterType() == PT_FLOAT )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pFloat ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Float值赋给非Float型参数" );
		}
	}
}

void ParameterManager::SetVector4fParameterData( const std::wstring& name , Vector4f* pVector )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new Vector4fParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_VECTOR_4F )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pVector ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Vector值赋给非Vector型参数" );
		}
	}
}

void ParameterManager::SetVector3fParameterData( const std::wstring& name , Vector3f* pVector )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new Vector3fParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if ( Parameters[name]->GetParameterType() == PT_VECTOR_3F )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pVector ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Vector值赋给非Vector型参数" );
		}
	}
}

void ParameterManager::SetVector2fParameterData( const std::wstring& name , Vector2f* pVector )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new Vector2fParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if ( Parameters[name]->GetParameterType() == PT_VECTOR_2F )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pVector ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Vector值赋给非Vector型参数" );
		}
	}
}

void ParameterManager::SetMatrixParameterData( const std::wstring& name , Matrix4f* pMatrix )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new MatrixParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pMatrix ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_MATRIX )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pMatrix ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Matrix值赋给非Matrix型参数" );
		}
	}
}

void ParameterManager::SetMatrixArrayParameterData( const std::wstring& name , int count , Matrix4f* pMatrices )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new MatrixArrayParameter( name , count );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pMatrices ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_MATRIX_ARRAY )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pMatrices ) );
		}
		else
		{
			Log::Get().Error( L"尝试将MatrixArray值赋给非MatrixArray型参数" );
		}
	}
}

void ParameterManager::SetStructureParameterData( const std::wstring& name , int size , char* pStructure )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new StructureParameter( name , size );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pStructure ) );
	}
	else
	{
		// 参数存在
		if ( pParameter->GetParameterType() == PT_STRUCTURE )
		{
			// 设置值
			pParameter->SetParameterData( reinterpret_cast< void* >( pStructure ) );
		}
		else
		{
			Log::Get().Error( L"trying to set value to non-struct parameter object" );
		}
	}
}

void ParameterManager::SetShaderResourceParameterData( const std::wstring& name , ResourceProxyPtr resource )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new ShaderResourceParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		int data = resource->GetShaderResourceViewID();
		pParameter->SetParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_SHADER_RESOURCE )
		{
			int data = resource->GetShaderResourceViewID();
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( &data ) );
		}
		else
		{
			Log::Get().Error( L"尝试将ShaderResource值赋给非ShaderResource型参数" );
		}
	}
}

void ParameterManager::SetUnorderedAccessParameterData( const std::wstring& name , ResourceProxyPtr resource , unsigned int initialize /*= -1 */ )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new UnorderedAccessParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		int data = resource->GetUnorderedAccessViewID();
		pParameter->SetParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_UNORDERED_ACCESS )
		{
			int data = resource->GetUnorderedAccessViewID();
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( &data ) );
		}
		else
		{
			Log::Get().Error( L"尝试将UnorderedAccessView值赋给非UnorderedAccessView型参数" );
		}
	}
}

void ParameterManager::SetConstantBufferParameterData( const std::wstring& name , ResourceProxyPtr resource )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new ConstantBufferParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		int data = resource->GetResourceID();
		pParameter->SetParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_CONSTANT_BUFFER )
		{
			int data = resource->GetResourceID();
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( &data ) );
		}
		else
		{
			Log::Get().Error( L"尝试将ConstantBuffer值赋给非ConstantBuffer型参数" );
		}
	}
}

void ParameterManager::SetSamplerStateParameterData( const std::wstring& name , int* pID )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 不存在该参数，则新建一个
		pParameter = new SamplerParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->SetParameterData( reinterpret_cast< void* >( pID ) );
	}
	else
	{
		// 该参数存在

		// 验证类型是否符合
		if( Parameters[name]->GetParameterType() == PT_SAMPLER )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pID ) );
		}
		else
		{
			Log::Get().Error( L"尝试将Sampler值赋给非Sampler型参数" );
		}
	}
}

void ParameterManager::SetBoolParameterData( RenderParameter* pParameter , bool* pBool )
{
	// 检测类型是否符合
	if ( pParameter->GetParameterType() == PT_BOOL )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pBool ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是Bool类型" );
	}
}

void ParameterManager::SetFloatParameterData( RenderParameter* pParameter , float* pFloat )
{
	// 检测类型是否符合
	if ( pParameter->GetParameterType() == PT_FLOAT )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pFloat ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是Float类型" );
	}
}

void ParameterManager::SetVector4fParameterData( RenderParameter* pParameter , Vector4f* pVector )
{
	// 检测类型是否符合
	if( pParameter->GetParameterType() == PT_VECTOR_4F )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是Vector类型" );
	}
}


void ParameterManager::SetVector3fParameterData( RenderParameter* pParameter , Vector3f* pVector )
{
	// 检测类型是否符合
	if ( pParameter->GetParameterType() == PT_VECTOR_3F )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是Vector类型" );
	}
}

void ParameterManager::SetVector2fParameterData( RenderParameter* pParameter , Vector2f* pVector )
{
	// 检测类型是否符合
	if ( pParameter->GetParameterType() == PT_VECTOR_2F )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是Vector类型" );
	}
}

void ParameterManager::SetMatrixParameterData( RenderParameter* pParameter , Matrix4f* pMatrix )
{
	if( pParameter->GetParameterType() == PT_MATRIX )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pMatrix ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是Matrix类型" );
	}
}

void ParameterManager::SetMatrixArrayParameterData( RenderParameter* pParameter , Matrix4f* pMatrices )
{
	if(pParameter->GetParameterType() == PT_MATRIX_ARRAY )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pMatrices ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是MatrixArray类型" );
	}
}

void ParameterManager::SetStructureParameterData( RenderParameter* pParameter , char* pStructure )
{
	if ( pParameter->GetParameterType() == PT_STRUCTURE )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pStructure ) );
	}
	else
	{
		Log::Get().Error( L"type can't match , isn't structure parameter object" );
	}
}

void ParameterManager::SetShaderResourceParameterData( RenderParameter* pParameter , ResourceProxyPtr resource )
{
	if( pParameter->GetParameterType() == PT_SHADER_RESOURCE )
	{
		int data = resource->GetShaderResourceViewID();
		pParameter->SetParameterData( reinterpret_cast< void* >( &data) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是ShaderResourceView对象的参数" );
	}
}

void ParameterManager::SetConstantBufferParameterData( RenderParameter* pParameter , ResourceProxyPtr resource )
{
	if( pParameter->GetParameterType() == PT_CONSTANT_BUFFER )
	{
		int data = resource->GetResourceID();
		pParameter->SetParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是ConstantBuffer的参数" );
	}
}

void ParameterManager::SetUnorderedAccessParameterData( RenderParameter* pParameter , ResourceProxyPtr resource )
{
	if( pParameter->GetParameterType() == PT_UNORDERED_ACCESS )
	{
		int data = resource->GetUnorderedAccessViewID();
		pParameter->SetParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是UnorderedAccessView的参数" );
	}
}

void ParameterManager::SetSamplerStateParameterData( RenderParameter* pParameter , int* pID )
{
	if( pParameter->GetParameterType() == PT_SAMPLER )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pID ) );
	}
	else
	{
		Log::Get().Error( L"参数类型不符，该参数不是SamplerState的参数" );
	}
}

// ----------------------------------------------------------Get Parameter Reference----------------------------------------

RenderParameter* ParameterManager::GetParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr && m_pParent )
	{
		m_pParent->GetParameterRef( name );
	}

	return pParameter;
}

BoolParameter* ParameterManager::GetBoolParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new BoolParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< BoolParameter* >( pParameter );
}

FloatParameter* ParameterManager::GetFloatParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new FloatParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< FloatParameter* >( pParameter );
}

Vector4fParameter* ParameterManager::GetVector4fParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new Vector4fParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< Vector4fParameter* >( pParameter );
}

Vector3fParameter* ParameterManager::GetVector3fParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new Vector3fParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< Vector3fParameter* >( pParameter );
}

Vector2fParameter* ParameterManager::GetVector2fParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new Vector2fParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< Vector2fParameter* >( pParameter );
}

MatrixParameter* ParameterManager::GetMatrixParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new MatrixParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< MatrixParameter* >( pParameter );
}

MatrixArrayParameter* ParameterManager::GetMatrixArrayParameterRef( const std::wstring& name , int count )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new MatrixArrayParameter( name , count );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< MatrixArrayParameter* >( pParameter );
}

StructureParameter* ParameterManager::GetStructureParameterRef( const std::wstring& name , int size )
{
	RenderParameter* pParameter = Parameters[name];

	if ( pParameter == nullptr )
	{
		pParameter = new StructureParameter( name , size );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< StructureParameter* >( pParameter );
}

ShaderResourceParameter* ParameterManager::GetShaderResourceParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new ShaderResourceParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< ShaderResourceParameter* >( pParameter );
}

UnorderedAccessParameter* ParameterManager::GetUnorderedAccessParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new UnorderedAccessParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< UnorderedAccessParameter* >( pParameter );
}

ConstantBufferParameter* ParameterManager::GetConstantBufferParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new ConstantBufferParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< ConstantBufferParameter* >( pParameter );
}

SamplerParameter* ParameterManager::GetSamplerStateParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new SamplerParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< SamplerParameter* >( pParameter );
}

// --------------------------------------------------获取参数对象的值---------------------------------------
bool ParameterManager::GetBoolParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	bool result = false;

	if ( pParameter == nullptr )
	{
		pParameter = new BoolParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if ( pParameter->GetParameterType() == PT_BOOL )
		{
			result = reinterpret_cast< BoolParameter* >( pParameter )->GetValue();
		}
	}

	return result;
}

float ParameterManager::GetFloatParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	float result = 0.0f;

	if ( pParameter == nullptr )
	{
		pParameter = new FloatParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if ( pParameter->GetParameterType() == PT_FLOAT )
		{
			result = reinterpret_cast< FloatParameter* >( pParameter )->GetValue();
		}
	}

	return result;
}

Vector4f ParameterManager::GetVector4fParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	Vector4f result;
	result.MakeZero();

	if( pParameter == nullptr )
	{
		pParameter = new Vector4fParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_VECTOR_4F )
		{
			result = reinterpret_cast< Vector4fParameter* >( pParameter )->GetVector();
		}
	}

	return result;
}

Vector3f ParameterManager::GetVector3fParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	Vector3f result;
	result.MakeZero();

	if ( pParameter == nullptr )
	{
		pParameter = new Vector3fParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if ( pParameter->GetParameterType() == PT_VECTOR_3F )
		{
			result = reinterpret_cast< Vector3fParameter* >( pParameter )->GetVector();
		}
	}

	return result;
}

Vector2f ParameterManager::GetVector2fParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	Vector2f result;
	result.MakeZero();

	if ( pParameter == nullptr )
	{
		pParameter = new Vector2fParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if ( pParameter->GetParameterType() == PT_VECTOR_2F )
		{
			result = reinterpret_cast< Vector2fParameter* >( pParameter )->GetVector();
		}
	}

	return result;
}

Matrix4f ParameterManager::GetMatrixParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	Matrix4f result;
	result.MakeZero();

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new MatrixParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_MATRIX )
		{
			result = reinterpret_cast< MatrixParameter* >( pParameter )->GetMatrix();
		}
	}

	return result;
}

Matrix4f* ParameterManager::GetMatrixArrayParameterData( const std::wstring& name , int count )
{
	RenderParameter* pParameter = Parameters[name];

	Matrix4f* result = nullptr;

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new MatrixArrayParameter( name , count );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_MATRIX_ARRAY )
		{
			result = reinterpret_cast< MatrixArrayParameter* >( pParameter )->GetMatrices();
		}
	}

	return result;
}

char* ParameterManager::GetStructureParameterData( const std::wstring& name , int size )
{
	RenderParameter* pParameter = Parameters[name];

	char* result = nullptr;

	if ( pParameter == nullptr )
	{
		// 创建StructureParameter对象
		pParameter = new StructureParameter( name , size );
		Parameters[name] = pParameter;
	}
	else
	{
		if ( pParameter->GetParameterType() == PT_STRUCTURE )
		{
			result = reinterpret_cast< StructureParameter* >( pParameter )->GetStructureData();
		}
	}

	return result;
}

int ParameterManager::GetUnorderedAccessParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	int result = -1;

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new UnorderedAccessParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_UNORDERED_ACCESS )
		{
			result = reinterpret_cast< UnorderedAccessParameter* >( pParameter )->GetResourceViewID();
		}
	}

	return result;
}

int ParameterManager::GetShaderResourceParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	int result = -1;

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new ShaderResourceParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_SHADER_RESOURCE )
		{
			result = reinterpret_cast< ShaderResourceParameter* >( pParameter )->GetResourceViewID();
		}
	}

	return result;
}

int ParameterManager::GetConstantBufferParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	int result = -1;

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new ConstantBufferParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_CONSTANT_BUFFER )
		{
			result = reinterpret_cast< ConstantBufferParameter* >( pParameter )->GetResourceID();
		}
	}

	return result;
}

int ParameterManager::GetSamplerStateParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	int result = -1;

	if( pParameter == nullptr )
	{
		// 创建参数对象
		pParameter = new SamplerParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_SAMPLER )
		{
			result = reinterpret_cast< SamplerParameter* >( pParameter )->GetSamplerResourceID();
		}
	}

	return result;
}

bool ParameterManager::GetBoolParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	bool result = false;

	if ( pParameter->GetParameterType() == PT_BOOL )
	{
		result = reinterpret_cast< BoolParameter* >( pParameter )->GetValue();
	}

	return result;
}

float ParameterManager::GetFloatParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	float result = false;

	if ( pParameter->GetParameterType() == PT_FLOAT )
	{
		result = reinterpret_cast< FloatParameter* >( pParameter )->GetValue();
	}

	return result;
}

Vector4f ParameterManager::GetVector4fParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );
	
	Vector4f result;
	result.MakeZero();

	if( pParameter->GetParameterType() == PT_VECTOR_4F )
	{
		result = reinterpret_cast< Vector4fParameter* >( pParameter )->GetVector();
	}

	return result;
}

Vector3f ParameterManager::GetVector3fParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	Vector3f result;
	result.MakeZero();

	if ( pParameter->GetParameterType() == PT_VECTOR_3F )
	{
		result = reinterpret_cast< Vector3fParameter* >( pParameter )->GetVector();
	}

	return result;
}

Vector2f ParameterManager::GetVector2fParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	Vector2f result;
	result.MakeZero();

	if ( pParameter->GetParameterType() == PT_VECTOR_2F )
	{
		result = reinterpret_cast< Vector2fParameter* >( pParameter )->GetVector();
	}

	return result;
}

Matrix4f ParameterManager::GetMatrixParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	Matrix4f result;
	result.MakeZero();

	if( pParameter->GetParameterType() == PT_MATRIX )
	{
		result = reinterpret_cast< MatrixParameter* >( pParameter )->GetMatrix();
	}

	return result;
}

Matrix4f* ParameterManager::GetMatrixArrayParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	Matrix4f* result = nullptr;

	if( pParameter->GetParameterType() == PT_MATRIX_ARRAY )
	{
		result = reinterpret_cast< MatrixArrayParameter* >( pParameter )->GetMatrices();
	}

	return result;
}

char* ParameterManager::GetStructureParameterData( RenderParameter* pParameter )
{
	assert( pParameter != nullptr );

	char* result = nullptr;

	if ( pParameter->GetParameterType() == PT_STRUCTURE )
	{
		result = reinterpret_cast< StructureParameter* >( pParameter )->GetStructureData();
	}

	return result;
}

int ParameterManager::GetShaderResourceParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	int result = -1;

	if( pParameter->GetParameterType() == PT_SHADER_RESOURCE )
	{
		result = reinterpret_cast< ShaderResourceParameter* >( pParameter )->GetResourceViewID();
	}

	return result;
}

int ParameterManager::GetUnorderedAccessParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	int result = -1;

	if( pParameter->GetParameterType() == PT_UNORDERED_ACCESS )
	{
		result = reinterpret_cast< UnorderedAccessParameter* >( pParameter )->GetResourceViewID();
	}

	return result;
}

int ParameterManager::GetSamplerStateParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	int result = -1;

	if( pParameter->GetParameterType() == PT_SAMPLER )
	{
		result = reinterpret_cast< SamplerParameter* >( pParameter )->GetSamplerResourceID();
	}

	return result;
}

int ParameterManager::GetConstantBufferParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );

	int result = -1;

	if( pParameter->GetParameterType() == PT_CONSTANT_BUFFER )
	{
		result = reinterpret_cast< ConstantBufferParameter* >( pParameter )->GetResourceID();
	}

	return result;
}

void Sand::ParameterManager::SetWorldMatrixParameterData( Matrix4f* pMatrix )
{
	SetMatrixParameterData( m_pWorldMatrix , pMatrix );

	Matrix4f WorldMatrix = GetMatrixParameterData( m_pWorldMatrix );
	Matrix4f ViewMatrix = GetMatrixParameterData( m_pViewMatrix );
	Matrix4f ProjMatrix = GetMatrixParameterData( m_pProjMatrix );

	Matrix4f WorldViewMatrix = WorldMatrix * ViewMatrix;
	Matrix4f WorldProjMatrix = WorldMatrix * ProjMatrix;
	Matrix4f WorldViewProjMatrix = WorldMatrix * ViewMatrix * ProjMatrix;

	// -----------------逆转置矩阵---------------------------------------
	WorldMatrix.SetTranslate( Vector3f( 0.0f , 0.0f , 0.0f ) );
	Matrix4f WorldInvTranspose = WorldMatrix.Inverse().Transpose();

	SetMatrixParameterData( m_pWorldViewMatrix , &WorldViewMatrix );
	SetMatrixParameterData( m_pWorldProjMatrix , &WorldProjMatrix );
	SetMatrixParameterData( m_pWorldViewProjMatrix , &WorldViewProjMatrix );
	SetMatrixParameterData( m_pWorldInvTransposeMatrix , &WorldInvTranspose );
}

void Sand::ParameterManager::SetViewMatrixParameterData( Matrix4f* pMatrix )
{
	SetMatrixParameterData( m_pViewMatrix , pMatrix );

	Matrix4f WorldMatrix = GetMatrixParameterData( m_pWorldMatrix );
	Matrix4f ViewMatrix = GetMatrixParameterData( m_pViewMatrix );
	Matrix4f ProjMatrix = GetMatrixParameterData( m_pProjMatrix );

	Matrix4f WorldViewMatrix = WorldMatrix * ViewMatrix;
	Matrix4f ViewProjMatrix = ViewMatrix * ProjMatrix;
	Matrix4f WorldViewProjMatrix = WorldMatrix * ViewMatrix * ProjMatrix;

	SetMatrixParameterData( m_pWorldViewMatrix , &WorldViewMatrix );
	SetMatrixParameterData( m_pViewProjMatrix , &ViewProjMatrix );
	SetMatrixParameterData( m_pWorldViewProjMatrix , &WorldViewProjMatrix );
}

void Sand::ParameterManager::SetProjMatrixParameterData( Matrix4f* pMatrix )
{
	SetMatrixParameterData( m_pProjMatrix , pMatrix );

	Matrix4f WorldMatrix = GetMatrixParameterData( m_pWorldMatrix );
	Matrix4f ViewMatrix = GetMatrixParameterData( m_pViewMatrix );
	Matrix4f ProjMatrix = GetMatrixParameterData( m_pProjMatrix );

	Matrix4f WorldProjMatrix = WorldMatrix * ProjMatrix;
	Matrix4f ViewProjMatrix = ViewMatrix * ProjMatrix;
	Matrix4f WorldViewProjMatrix = WorldMatrix * ViewMatrix * ProjMatrix;

	SetMatrixParameterData( m_pWorldProjMatrix , &WorldProjMatrix );
	SetMatrixParameterData( m_pViewProjMatrix , &ViewProjMatrix );
	SetMatrixParameterData( m_pWorldViewProjMatrix , &WorldViewProjMatrix );
}

void ParameterManager::AttachParent( IParameterManager* pParent )
{
	m_pParent = pParent;
}

void ParameterManager::DetachParent()
{
	m_pParent = nullptr;
}