#include "PCH.h"
#include "Material.h"

using namespace Sand;

Material::Material()
{
	// 关闭所有渲染视图类型
	for( int i = 0; i < VT_NUM_VIEW_TYPES; i++ )
	{
		Params[i].bRender = false;
		Params[i].pEffect = nullptr;
	}
}

Material::~Material()
{
	for( int i = 0; i < VT_NUM_VIEW_TYPES; i++ )
	{
		SAFE_DELETE( Params[i].pEffect );
	}
}

void Material::Update( float time )
{

}

void Material::SetRenderParams( IParameterManager* pParameterManager , VIEW_TYPE Type )
{
	Parameters.UpdateRenderParam( pParameterManager );
}

void Material::GetAllVertexShaderIDs( std::vector<int>& idList )
{
	for( int i = 0; i < VT_NUM_VIEW_TYPES; i++ )
	{
		if( nullptr != Params[i].pEffect )
		{
			int ID = Params[i].pEffect->GetVertexShader();

			if( -1 != ID )
			{
				idList.push_back( ID );
			}
		}
	}
}