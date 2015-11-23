#include "PCH.h"
#include "Renderable.h"
#include "Log.h"

using namespace Sand;

Renderable::Renderable()
	:iPass( GEOMETRY ) ,
	IAStageExecutor( nullptr ) ,
	Mat( nullptr )
{

}

Renderable::~Renderable()
{
	IAStageExecutor = nullptr;
	Mat = nullptr;
}

void Renderable::SetMaterial( MaterialPtr pMaterial )
{
	Mat = pMaterial;

	if( Mat != nullptr && IAStageExecutor != nullptr )
	{
		// 获取所有可用的Vertex Shader ID
		std::vector<int> idList;
		pMaterial->GetAllVertexShaderIDs( idList );

		for( int i = 0; i < idList.size(); i++ )
		{
			IAStageExecutor->GenerateInputLayout( idList[i] );
		}
	}
}

MaterialPtr Renderable::GetMaterial()
{
	return Mat;
}

InputAssemblerStageExecutorPtr Renderable::GetGeometry()
{
	return IAStageExecutor;
}

void Renderable::SetGeometry( InputAssemblerStageExecutorPtr pExecutor )
{
	IAStageExecutor = pExecutor;

	if( Mat != nullptr && IAStageExecutor != nullptr )
	{
		std::vector<int> idList;
		Mat->GetAllVertexShaderIDs( idList );

		for( int i = 0; i < idList.size(); i++ )
		{
			IAStageExecutor->GenerateInputLayout( idList[i] );
		}
	}
}