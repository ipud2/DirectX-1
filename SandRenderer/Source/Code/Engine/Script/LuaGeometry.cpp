#include <Engine/PCH.h>
#include "LuaGeometry.h"
#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/Geometry.h"
#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/GeometryLoader.h"

using namespace Sand;

GeometryPtr pGeometry = nullptr;

LuaGeometry::LuaGeometry()
{

}

LuaGeometry::~LuaGeometry()
{

}

void LuaGeometry::Register( lua_State* L )
{
	static const luaL_Reg RegFuncList[] = 
	{
		{ "new" , LuaGeometry::Create },
		{ NULL , NULL }
	};

	luaL_newmetatable( L , "luaL_Geometry" );

	luaL_setfuncs( L , RegFuncList , 0 );

	lua_pushvalue( L , -1 );

	lua_setfield( L , -2 , "__index" );

	lua_setglobal( L , "Geometry" );
}

Geometry* CheckType( lua_State* L , int n )
{
	return ( *( Geometry** )luaL_checkudata( L , n , "luaL_Geometry" ) );
}

int LuaGeometry::Create( lua_State* L )
{
	Geometry** udata = ( Geometry** )lua_newuserdata( L , sizeof( Geometry* ) );
	pGeometry = GeometryLoader::LoadOBJWithTexture( std::wstring( L"Skull.obj" ) );
	pGeometry->LoadToBuffer();
	pGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	*udata = ( pGeometry.get() );

	luaL_getmetatable( L , "luaL_Geometry" );

	lua_setmetatable( L , -2 );

	return 1;
}