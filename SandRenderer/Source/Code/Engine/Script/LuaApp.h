#ifndef LUA_APP_H
#define LUA_APP_H

#include "ScriptManager.h"
#include "Engine/Object/Scene/Scene.h"

namespace Sand
{
	class LuaApp
	{
	public:
		LuaApp();

		virtual ~LuaApp();

		static int luaopen_App( lua_State* L );

		static int Log( lua_State* L );
		static int Framerate( lua_State* L );
	};
}
#endif