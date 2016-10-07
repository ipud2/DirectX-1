#include "PCH.h"
#include "LuaMaterial.h"
#include "Material.h"

using namespace Sand;

LuaMaterial::LuaMaterial()
{

}

LuaMaterial::~LuaMaterial()
{

}

void LuaMaterial::Register( lua_State* L )
{
	int ioldtop = lua_gettop( L );

	static const luaL_Reg RegFuncList[] =
	{
		{ "new" , LuaMaterial::Create } ,
		{ nullptr , nullptr }
	};

	luaL_newmetatable( L , "luaL_Material" );
		luaL_setfuncs( L , RegFuncList , 0 );		// register all function into metatable on the top of stack
		lua_pushvalue( L , -1 );					// -1 : metatable	// -2 : metatable
		lua_setfield( L , -2 , "__index" );			// -1 : metatable
	lua_setglobal( L , "Material" );

	assert( lua_gettop( L ) == ioldtop );
}

int LuaMaterial::Create( lua_State* L )
{
	luaL_checktype( L , 1 , LUA_TSTRING );

	const char* name = lua_tostring( L , 1 );

	Material** udata = ( Material** )lua_newuserdata( L , sizeof( Material* ) );
	*udata = new Material( name );
	
	luaL_getmetatable( L , "luaL_Material" );
	lua_setmetatable( L , -2 );

	return 1;
}