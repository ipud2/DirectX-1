#include "PCH.h"
#include "Effect.h"

using namespace Sand;

Effect::Effect()
{
	// 关闭所有渲染视图类型
	for( int i = 0; i < VT_NUM_VIEW_TYPES; i++ )
	{
		Schemes[i].bRender = false;
		Schemes[i].pEffect = nullptr;
	}
}

Effect::~Effect()
{
	for( int i = 0; i < VT_NUM_VIEW_TYPES; i++ )
	{
		SAFE_DELETE( Schemes[i].pEffect );
	}
}

void Effect::Update( float time )
{

}

void Effect::SetRenderParams( IParameterManager* pParameterManager , VIEW_TYPE Type )
{
	ParameterWriters.UpdateRenderParam( pParameterManager );
}

void Effect::GetAllVertexShaderIDs( std::vector<int>& idList )
{
	for( int i = 0; i < VT_NUM_VIEW_TYPES; i++ )
	{
		if ( nullptr != Schemes[i].pEffect )
		{
			int ID = Schemes[i].pEffect->GetVertexShader();

			if( -1 != ID )
			{
				idList.push_back( ID );
			}
		}
	}
}