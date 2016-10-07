#include "PCH.h"
#include "LuaEffect.h"
#include "RenderEffect.h"
#include "Effect.h"

using namespace Sand;

Renderer* LuaEffect::m_pRenderer = nullptr;

LuaEffect::LuaEffect( Renderer* pRenderer )
{
	if ( !m_pRenderer )
		m_pRenderer = pRenderer;
}

LuaEffect::~LuaEffect()
{

}

void LuaEffect::Register( lua_State* L )
{
	static const luaL_Reg RegFuncList[] =
	{
		{ "new" , LuaEffect::Create } ,
		{ NULL , NULL }
	};

	luaL_newmetatable( L , "luaL_Effect" );

	luaL_setfuncs( L , RegFuncList , 0 );

	lua_pushvalue( L , -1 );

	lua_setfield( L , -2 , "__index" );

	lua_setglobal( L , "Effect" );
}

int LuaEffect::Create( lua_State* L )
{
	RenderEffect** pRenderEffectUserdata = ( RenderEffect** )lua_newuserdata( L , sizeof( RenderEffect* ) );

	*pRenderEffectUserdata = new RenderEffect;
	( *pRenderEffectUserdata )->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
		std::wstring( L"BasicTexture.hlsl" ) ,
		std::wstring( L"VSMain" ) ,
		std::wstring( L"vs_5_0" ) ) );
	( *pRenderEffectUserdata )->SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER ,
		std::wstring( L"BasicTexture.hlsl" ) ,
		std::wstring( L"PSMain" ) ,
		std::wstring( L"ps_5_0" ) ) );

	luaL_getmetatable( L , "luaL_Effect" );

	lua_setmetatable( L , -2 );

	return 1;
}