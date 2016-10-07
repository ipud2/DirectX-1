#include "PCH.h"
#include "Renderable.h"
#include "Log.h"

using namespace Sand;

Renderable::Renderable()
	:IAStageExecutor( nullptr ) ,
	ShaderEffect( nullptr ) ,
	pMaterial( nullptr )
{

}

Renderable::~Renderable()
{
	IAStageExecutor = nullptr;
	ShaderEffect = nullptr;
	pMaterial = nullptr;
}

void Renderable::SetEffect( EffectPtr pShaderEffect )
{
	ShaderEffect = pShaderEffect;

	if( ShaderEffect != nullptr && IAStageExecutor != nullptr )
	{
		// 获取所有可用的Vertex Shader ID
		std::vector<int> idList;
		pShaderEffect->GetAllVertexShaderIDs( idList );

		for( int i = 0; i < idList.size(); i++ )
		{
			IAStageExecutor->GenerateInputLayout( idList[i] );
		}
	}
}

EffectPtr Renderable::GetEffect()
{
	return ShaderEffect;
}

InputAssemblerStageExecutorPtr Renderable::GetGeometry()
{
	return IAStageExecutor;
}

void Renderable::SetGeometry( InputAssemblerStageExecutorPtr pExecutor )
{
	IAStageExecutor = pExecutor;

	if( ShaderEffect != nullptr && IAStageExecutor != nullptr )
	{
		std::vector<int> idList;
		ShaderEffect->GetAllVertexShaderIDs( idList );

		for( int i = 0; i < idList.size(); i++ )
		{
			IAStageExecutor->GenerateInputLayout( idList[i] );
		}
	}
}

void Renderable::SetMaterial( Material* pMat )
{
	pMaterial = pMat;
}

Material* Renderable::GetMaterial()
{
	return pMaterial;
}