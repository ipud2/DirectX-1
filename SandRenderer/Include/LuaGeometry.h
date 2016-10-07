#ifndef LUA_GEOMETRY_H
#define LUA_GEOMETRY_H

#include "ScriptManager.h"

namespace Sand
{
	class LuaGeometry
	{
	public:
		LuaGeometry();
		~LuaGeometry();

		void Register( lua_State* L );

		static int Create( lua_State* L );
	};
}
#endif