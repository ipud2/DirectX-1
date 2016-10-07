#include "PCH.h"
#include "LuaApp.h"

using namespace Sand;

LuaApp::LuaApp()
{

}

LuaApp::~LuaApp()
{

}

int LuaApp::Log( lua_State* L )
{
	const char* message = lua_tostring( L , -1 );
	
	return 0;
}

int LuaApp::Framerate( lua_State* L )
{
	lua_pushnumber( L , 60.0f );

	return 1;
}

int LuaApp::luaopen_App( lua_State* L )
{
	luaL_Reg sSceneRegsLua[] = 
	{
		{ "Log" , LuaApp::Log } ,
		{ "Framerate" , LuaApp::Framerate } ,
		{ NULL , NULL }
	};

	luaL_newlib( L , sSceneRegsLua );
	
	return 1;
}