#include "PCH.h"
#include "Material.h"
#include "Log.h"
#include "SandString.h"
#include "MaterialLua.h"
#include <string.h>
#include "LuaSampler.h"
#include "SamplerStateConfig.h"

using namespace Sand;

Material::Material( const char* name )
{
	L = luaL_newstate();
	luaL_openlibs( L );

	if ( luaL_loadfile( L , GetMatPath( name ).c_str() ) || lua_pcall( L , 0 , 0 , 0 ) )
	{
		const char* errormessage = lua_tostring( L , -1 );

		Log::Get().Write( SandString::ToUnicode( std::string( errormessage ) ) );

		lua_pop( L , 1 );
	}

	int itop = lua_gettop( L );

	bInit = false;
}

Material::~Material()
{
	lua_close( L );
	L = nullptr;
}

void Material::InitParams()
{
	MaterialLua::Apply( L , ParamList );

	for ( auto iter = ParamList.begin(); iter != ParamList.end(); iter++ )
	{
		switch ( iter->second.eType )
		{
			case ELT_INTEGER:
			{
				FloatParameterWriter* m_pFloatWriter = Parameters.GetFloatParameterWriter( SandString::ToUnicode( iter->first ) );
				m_pFloatWriter->SetValue( ( float )iter->second.v.i );
				break;
			}

			case ELT_NUMBER:
			{
				FloatParameterWriter* m_pFloatWriter = Parameters.GetFloatParameterWriter( SandString::ToUnicode( iter->first ) );
				m_pFloatWriter->SetValue( iter->second.v.f );
				break;
			}

			case ELT_BOOL:
			{
				BoolParameterWriter* m_pBoolWriter = Parameters.GetBoolParameterWriter( SandString::ToUnicode( iter->first ) );
				m_pBoolWriter->SetValue( iter->second.v.b );
				break;
			}

			case ELT_STRING:
			{
				char* str = iter->second.v.str;
				char* pExtension = strstr( str , "." );

				if ( strlen( pExtension ) == 4 && pExtension[1] == 'd' && pExtension[2] == 'd' && pExtension[3] == 's' )
				{
					ResourceProxyPtr pTexture = Renderer::Get()->LoadTexture( SandString::ToUnicode( str ) );
					ShaderResourceParameterWriter* pShaderResourceWriter = Parameters.GetShaderResourceParameterWriter( SandString::ToUnicode( iter->first ) );
					pShaderResourceWriter->SetValue( pTexture );
				}
				break;
			}

			case ELT_ARRAY:
			{
				Vector4fParameterWriter* m_pVector4fParameterWriter = Parameters.GetVector4fParameterWriter( SandString::ToUnicode( iter->first ) );
				m_pVector4fParameterWriter->SetValue( Vector4f( iter->second.v.arr[0] , iter->second.v.arr[1] , iter->second.v.arr[2] , iter->second.v.arr[3] ) );
				break;
			}

			case ELT_SAMPLER:
			{
				SamplerStateConfig config;
				UpdateSamplerStateConfig( config , &iter->second.v.sampler );
				int m_iSampler = Renderer::Get()->CreateSamplerState( &config );

				SamplerParameterWriter* pSamplerWriter = Parameters.GetSamplerParameterWriter( SandString::ToUnicode( iter->first ) );
				pSamplerWriter->SetValue( m_iSampler );

				break;
			}
		}
	}

	bInit = true;
}

void Material::Update( IParameterManager* pParameterManager )
{
	if ( !bInit )	InitParams();

	// Update Material


	Parameters.UpdateRenderParam( pParameterManager );
}