#include "PCH.h"
#include "InputAssemblerStageExecutor.h"
#include "Renderer.h"

using namespace Sand;

InputAssemblerStageExecutor::InputAssemblerStageExecutor()
{

}

InputAssemblerStageExecutor::~InputAssemblerStageExecutor()
{
	std::map<int , InputLayoutKey*>::iterator it = m_InputLayouts.begin();

	for( ; it != m_InputLayouts.end(); it++ )
	{
		SAFE_DELETE( ( *it ).second );
	}
}

void InputAssemblerStageExecutor::SetInputElementsDesc( int count , D3D11_INPUT_ELEMENT_DESC* pInputElementsDesc )
{
	for( int i = 0; i < count; i++ )
	{
		m_InputElementsDesc.push_back( pInputElementsDesc[i] );
	}
}

void InputAssemblerStageExecutor::GenerateInputLayout( int ShaderID )
{
	Renderer* pRenderer = Renderer::Get();
	if( m_InputLayouts[ShaderID] == nullptr )
	{
		InputLayoutKey* key = new InputLayoutKey;
		key->ShaderID = ShaderID;
		key->InputLayoutID = pRenderer->CreateInputLayout( m_InputElementsDesc , ShaderID );
		m_InputLayouts[ShaderID] = key;
	}
}

int InputAssemblerStageExecutor::GetInputLayout( int ShaderID )
{
	int layout = -1;

	if( m_InputLayouts[ShaderID] == 0 )
	{
		GenerateInputLayout( ShaderID );
	}

	layout = m_InputLayouts[ShaderID]->InputLayoutID;

	return layout;
}