#include "PCH.h"
#include "ParameterManager.h"
#include "Log.h"

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
}

ParameterManager::~ParameterManager()
{
	
}


// ------------------------------------------------Set Paramter Data-------------------------------------------------------------
void ParameterManager::SetVectorParameterData( const std::wstring& name , Vector4f* pVector )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new VectorParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->InitializeParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_VECTOR )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pVector ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�Vectorֵ������Vector�Ͳ���" );
		}
	}
}

void ParameterManager::SetMatrixParameterData( const std::wstring& name , Matrix4f* pMatrix )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new MatrixParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->InitializeParameterData( reinterpret_cast< void* >( pMatrix ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_MATRIX )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pMatrix ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�Matrixֵ������Matrix�Ͳ���" );
		}
	}
}

void ParameterManager::SetMatrixArrayParameterData( const std::wstring& name , int count , Matrix4f* pMatrices )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new MatrixArrayParameter( name , count );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->InitializeParameterData( reinterpret_cast< void* >( pMatrices ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_MATRIX_ARRAY )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pMatrices ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�MatrixArrayֵ������MatrixArray�Ͳ���" );
		}
	}
}

void ParameterManager::SetShaderResourceParameterData( const std::wstring& name , ResourceProxyPtr resource )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new ShaderResourceParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		int data = resource->GetShaderResourceViewID();
		pParameter->InitializeParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_SHADER_RESOURCE )
		{
			int data = resource->GetShaderResourceViewID();
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( &data ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�ShaderResourceֵ������ShaderResource�Ͳ���" );
		}
	}
}

void ParameterManager::SetUnorderedAccessParameterData( const std::wstring& name , ResourceProxyPtr resource , unsigned int initialize /*= -1 */ )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new UnorderedAccessParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		int data = resource->GetUnorderedAccessViewID();
		pParameter->InitializeParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_UNORDERED_ACCESS )
		{
			int data = resource->GetUnorderedAccessViewID();
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( &data ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�UnorderedAccessViewֵ������UnorderedAccessView�Ͳ���" );
		}
	}
}

void ParameterManager::SetConstantBufferParameterData( const std::wstring& name , ResourceProxyPtr resource )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new ConstantBufferParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		int data = resource->GetResourceID();
		pParameter->InitializeParameterData( reinterpret_cast< void* >( &data ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_CONSTANT_BUFFER )
		{
			int data = resource->GetResourceID();
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( &data ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�ConstantBufferֵ������ConstantBuffer�Ͳ���" );
		}
	}
}

void ParameterManager::SetSamplerStateParameterData( const std::wstring& name , int* pID )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// �����ڸò��������½�һ��
		pParameter = new SamplerParameter( name );
		Parameters[name] = reinterpret_cast< RenderParameter* >( pParameter );

		pParameter->InitializeParameterData( reinterpret_cast< void* >( pID ) );
	}
	else
	{
		// �ò�������

		// ��֤�����Ƿ����
		if( Parameters[name]->GetParameterType() == PT_SAMPLER )
		{
			Parameters[name]->SetParameterData( reinterpret_cast< void* >( pID ) );
		}
		else
		{
			Log::Get().Write( L"���Խ�Samplerֵ������Sampler�Ͳ���" );
		}
	}
}


void ParameterManager::SetVectorParameterData( RenderParameter* pParameter , Vector4f* pVector )
{
	// ��������Ƿ����
	if( pParameter->GetParameterType() == PT_VECTOR )
	{
		pParameter->SetParameterData( reinterpret_cast< void* >( pVector ) );
	}
	else
	{
		Log::Get().Write( L"�������Ͳ������ò�������Vector����" );
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
		Log::Get().Write( L"�������Ͳ������ò�������Matrix����" );
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
		Log::Get().Write( L"�������Ͳ������ò�������MatrixArray����" );
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
		Log::Get().Write( L"�������Ͳ������ò�������ShaderResourceView����Ĳ���" );
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
		Log::Get().Write( L"�������Ͳ������ò�������ConstantBuffer�Ĳ���" );
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
		Log::Get().Write( L"�������Ͳ������ò�������UnorderedAccessView�Ĳ���" );
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
		Log::Get().Write( L"�������Ͳ������ò�������SamplerState�Ĳ���" );
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

VectorParameter* ParameterManager::GetVectorParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// ������������
		pParameter = new VectorParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< VectorParameter* >( pParameter );
}

MatrixParameter* ParameterManager::GetMatrixParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// ������������
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
		// ������������
		pParameter = new MatrixArrayParameter( name , count );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< MatrixArrayParameter* >( pParameter );
}

ShaderResourceParameter* ParameterManager::GetShaderResourceParameterRef( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	if( pParameter == nullptr )
	{
		// ������������
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
		// ������������
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
		// ������������
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
		// ������������
		pParameter = new SamplerParameter( name );
		Parameters[name] = pParameter;
	}

	return reinterpret_cast< SamplerParameter* >( pParameter );
}

// --------------------------------------------------��ȡ���������ֵ---------------------------------------
Vector4f ParameterManager::GetVectorParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	Vector4f result;
	result.MakeZero();

	if( pParameter == nullptr )
	{
		pParameter = new VectorParameter( name );
		Parameters[name] = pParameter;
	}
	else
	{
		if( pParameter->GetParameterType() == PT_VECTOR )
		{
			result = reinterpret_cast< VectorParameter* >( pParameter )->GetVector();
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
		// ������������
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
		// ������������
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

int ParameterManager::GetUnorderedAccessParameterData( const std::wstring& name )
{
	RenderParameter* pParameter = Parameters[name];

	int result = -1;

	if( pParameter == nullptr )
	{
		// ������������
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
		// ������������
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
		// ������������
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
		// ������������
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


Vector4f ParameterManager::GetVectorParameterData( RenderParameter* pParameter )
{
	assert( pParameter != 0 );
	
	Vector4f result;
	result.MakeZero();

	if( pParameter->GetParameterType() == PT_VECTOR )
	{
		result = reinterpret_cast< VectorParameter* >( pParameter )->GetVector();
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
	Matrix4f ViewProjMatrix = ViewMatrix * ProjMatrix;
	Matrix4f WorldViewProjMatrix = WorldMatrix * ViewMatrix * ProjMatrix;

	SetMatrixParameterData( m_pWorldViewMatrix , &WorldViewMatrix );
	SetMatrixParameterData( m_pWorldProjMatrix , &WorldProjMatrix );
	SetMatrixParameterData( m_pViewProjMatrix , &ViewProjMatrix );
	SetMatrixParameterData( m_pWorldViewProjMatrix , &WorldViewProjMatrix );
}

void Sand::ParameterManager::SetViewMatrixParameterData( Matrix4f* pMatrix )
{
	SetMatrixParameterData( m_pViewMatrix , pMatrix );

	Matrix4f WorldMatrix = GetMatrixParameterData( m_pWorldMatrix );
	Matrix4f ViewMatrix = GetMatrixParameterData( m_pViewMatrix );
	Matrix4f ProjMatrix = GetMatrixParameterData( m_pProjMatrix );

	Matrix4f WorldViewMatrix = WorldMatrix * ViewMatrix;
	Matrix4f WorldProjMatrix = WorldMatrix * ProjMatrix;
	Matrix4f ViewProjMatrix = ViewMatrix * ProjMatrix;
	Matrix4f WorldViewProjMatrix = WorldMatrix * ViewMatrix * ProjMatrix;

	SetMatrixParameterData( m_pWorldViewMatrix , &WorldViewMatrix );
	SetMatrixParameterData( m_pWorldProjMatrix , &WorldProjMatrix );
	SetMatrixParameterData( m_pViewProjMatrix , &ViewProjMatrix );
	SetMatrixParameterData( m_pWorldViewProjMatrix , &WorldViewProjMatrix );
}

void Sand::ParameterManager::SetProjMatrixParameterData( Matrix4f* pMatrix )
{
	SetMatrixParameterData( m_pProjMatrix , pMatrix );

	Matrix4f WorldMatrix = GetMatrixParameterData( m_pWorldMatrix );
	Matrix4f ViewMatrix = GetMatrixParameterData( m_pViewMatrix );
	Matrix4f ProjMatrix = GetMatrixParameterData( m_pProjMatrix );

	Matrix4f WorldViewMatrix = WorldMatrix * ViewMatrix;
	Matrix4f WorldProjMatrix = WorldMatrix * ProjMatrix;
	Matrix4f ViewProjMatrix = ViewMatrix * ProjMatrix;
	Matrix4f WorldViewProjMatrix = WorldMatrix * ViewMatrix * ProjMatrix;

	SetMatrixParameterData( m_pWorldViewMatrix , &WorldViewMatrix );
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