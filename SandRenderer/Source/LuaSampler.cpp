#include "PCH.h"
#include "LuaSampler.h"
#include "SamplerStateConfig.h"
extern "C"
{
#include "Lua/inc/lua.h"
}

void Sand::ParseLuaSamplerTable( lua_State* L , LuaSampler* sampler )
{
	int ioldtop = lua_gettop( L );
	lua_getfield( L , -1 , "Filter" );
		const char* str = lua_tostring( L , -1 );	strcpy_s( sampler->Filter , str );
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "AddressU" );
		str = lua_tostring( L , -1 );	strcpy_s( sampler->AddressU , str );
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "AddressV" );
		str = lua_tostring( L , -1 );	strcpy_s( sampler->AddressV , str );
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "AddressW" );
		str = lua_tostring( L , -1 );	strcpy_s( sampler->AddressW , str );
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "MipLODBias" );
		sampler->MipLODBias = ( float )lua_tonumber( L , -1 );
	lua_pop( L , 1 );
	
	lua_getfield( L , -1 , "MaxAnisotropy" );
		sampler->MaxAnisotropy = ( float )lua_tonumber( L , -1 );
	lua_pop( L , 1 );
	
	lua_getfield( L , -1 , "ComparisonFunc" );
		str = lua_tostring( L , -1 );	strcpy_s( sampler->ComparisonFunc , str );
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "BorderColor" );
		for ( int i = 0; i < 4; i++ ) { lua_rawgeti( L , -1 , i + 1 ); sampler->BorderColor[i] = ( float )lua_tonumber( L , -1 );	lua_pop( L , 1 ); }
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "MinLOD" );
		sampler->MinLOD = ( float )lua_tonumber( L , -1 );
	lua_pop( L , 1 );

	lua_getfield( L , -1 , "MaxLOD" );
		sampler->MaxLOD = ( float )lua_tonumber( L , -1 );
	lua_pop( L , 1 );

	assert( lua_gettop( L ) == ioldtop );
}

void Sand::UpdateSamplerStateConfig( Sand::SamplerStateConfig& config , LuaSampler* sampler )
{
	if ( !strcmp( sampler->Filter , "MIN_MAG_MIP_LINEAR" ) )
	{
		config.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	}

	if ( !strcmp( sampler->AddressU , "WRAP" ) )
	{
		config.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	}

	if ( !strcmp( sampler->AddressV , "WRAP" ) )
	{
		config.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	}

	if ( !strcmp( sampler->AddressW , "WRAP" ) )
	{
		config.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	}

	config.MipLODBias = sampler->MipLODBias;

	config.MaxAnisotropy = sampler->MaxAnisotropy;

	if ( !strcmp( sampler->ComparisonFunc , "Always" ) )
	{
		config.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	}

	config.BorderColor[0] = sampler->BorderColor[0];
	config.BorderColor[1] = sampler->BorderColor[1];
	config.BorderColor[2] = sampler->BorderColor[2];
	config.BorderColor[3] = sampler->BorderColor[3];

	config.MinLOD = sampler->MinLOD;

	config.MaxLOD = sampler->MaxLOD;
}